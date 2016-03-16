#include "internal/client_impl.h"

#include <sstream>
#include <utility>
#include "json/json.h"
#include "openssl/md5.h"
#include "openssl/sha.h"
#include "zlib.h"

#include "util/string_util.h"
#include "util/time_util.h"
#include "bos/api.h"
#include "bos/model/request/request.h"
#include "bos/model/response/response.h"
#include "auth/auth.h"
#include "util/encrypt_util.h"
#include "util/exception.h"
#include "util/memory_stream.h"
#include "http/http.h"
#include "util/string_util.h"
#include "util/bos_log.h"

BEGIN_C_SDK_NAMESPACE
int ClientImpl::GlobalInit() {
    return HttpClient::Init();
}
int ClientImpl::GlobalUnInit() {
    return HttpClient::UnInit();
}

ClientImpl::ClientImpl(const std::string &access_key_id, const std::string &access_key_secret,
        const bce::bos::ClientOptions &options) : m_options(options){
    m_auth = new Auth(access_key_id, access_key_secret);
    m_access_key_id = access_key_id;
    m_access_key_secret = access_key_secret;

}

ClientImpl::~ClientImpl() {
   if (m_auth != NULL) {
       delete m_auth;
       m_auth = NULL;
   }
}

int ClientImpl::SendRequest(BosRequest &request, BosResponse *response) {
    int ret = bce::bos::kBosOk;
    try {
        
        HttpRequest http_request;

        request.BuildHttpRequest(m_options, *m_auth, &http_request);
	
        HttpResponse *http_response = response->GetHttpResponse();
        HttpClient::Request(http_request, http_response);
   
   	    response->ParseResponse();
   
    } catch (const BosServiceException &e) {
        ret = bce::bos::kBosServiceError;
        Log::PrintLog(FATAL, TRACE, e.GetMessage());
    } catch (const BosBaseException &e) {
	    response->SetMessage(e.GetMessage());
        ret = e.GetErrorCode();
        Log::PrintLog(FATAL, TRACE, e.GetMessage());
    } catch (...) {
        ret = bce::bos::kBosUnknownError;
        Log::PrintLog(FATAL, TRACE, "catch unknow exception");
    }

    return ret;
}

int ClientImpl::GetUrl(GetUrlRequest &request, std::string *result) const {
    request.SetHost(m_options.boss_host);
    return request.BuildUrl(m_access_key_id, m_access_key_secret, result);
}


/*
int ClientImpl::UploadSuperFile_SaveFile(const std::string &bucket_name, const std::string &object_name, const std::string &file_name, const std::string &upload_id, int64_t finish_size, const std::vector<std::pair<int, std::string> > &parts) const {
    Json::Value value;
    value["bucket"] = Json::Value(bucket_name);
    value["object"] = Json::Value(object_name);
    value["file"] = Json::Value(file_name);
    value["uploadId"] = Json::Value(upload_id);
    value["finishSize"] = Json::Value(Json::Int64(finish_size));
    for(unsigned int i = 0; i < parts.size(); i++) {
        Json::Value tmp;
        tmp["partNumber"] = Json::Value(parts[i].first);
        tmp["eTag"] = Json::Value(parts[i].second);
        value["parts"].append(tmp);
    }

    Json::FastWriter fast_writer;
    std::string buffer = fast_writer.write(value);
    FileOutputStream *ofs = new FileOutputStream("parts_data");
    ofs->Write(buffer);
    delete ofs;
    return 0;
}

int ClientImpl::UploadSuperFile(UploadSuperFileRequest &request, UploadSuperFileResponse *result) const {
    
    FileInputStream  t_ifs("parts_data");
    std::string buffer;

    Json::Reader reader;
    Json::Value value;
     
    std::string bucket_name = request.GetBucket();
    std::string object_name = request.GetObject();
    std::string file_name = request.GetFile();
    std::map<std::string, std::string> user_meta_data = request.GetUserMeta_data();
    
    std::string upload_id; 
    std::vector<std::pair<int, std::string> > parts;
    
    int part_marker = 0;
    int64_t finish_size = 0;

    FileInputStream *ifs = new FileInputStream(file_name);
    
    if(ifs->GetSize() == -1001) {
        delete ifs;
        printf("Upload part : no such file!\n");
        return kBosClientError;
    }

    if(t_ifs.GetSize() != -1001 && t_ifs.Read(t_ifs.GetSize(), &buffer) != -1001 && reader.parse(buffer, value)) {
        std::string t_bucket = value["bucket"].asString();
        std::string t_object = value["object"].asString();
        std::string t_file = value["file"].asString();
        
        if(t_bucket == bucket_name && t_object == object_name && t_file == file_name) {
            upload_id = value["uploadId"].asString();
            finish_size = value["finishSize"].asInt();
            Json::Value j_parts;
            j_parts = value["parts"];
            part_marker = j_parts.size();
            for(unsigned int i = 0; i < j_parts.size(); i++) {
                int t_part_number = j_parts[i]["partNumber"].asInt();
                std::string t_etag = j_parts[i]["eTag"].asString();
                parts.push_back(make_pair(t_part_number, t_etag));
            }
            ifs->Seek(finish_size);
        }
    }
    
    if(upload_id == "") {

        InitMultiUploadRequest init_request(bucket_name, object_name);
        InitMultiUploadResponse init_response;
    
        int ret = InitMultiUpload(init_request, &init_response);
        if(ret != 0 ) {
            printf("ini multi upload %d %s\n",ret,init_response.GetMessage().c_str());
            return ret;
        }

        std::string tmp_bucket_name; 
        std::string tmp_object_name;

        init_response.GetBucket(&tmp_bucket_name);
        init_response.GetKey(&tmp_object_name);

        if(tmp_bucket_name != bucket_name || tmp_object_name != object_name) {
            if(Log::need_log) {
                Log::PrintLog("LOG : bucket_name or object_name does not match!\n");
            }
            return kBosServiceError;
        }
        init_response.GetUploadId(&upload_id);

    }


    for(int i = part_marker + 1;i <= 10000; i++) {
        std::string *data = new std::string;
        int read_number = ifs->Read(5*1024*1024, data);
        if(read_number  <= 0) {
            delete data;
            break;
        }
        
        UploadPartRequest upload_request(bucket_name, object_name, *data, i, upload_id);
        UploadPartResponse upload_response;
        int ret = UploadPart(upload_request, &upload_response);

        delete data;
        sleep(1);
        if(ret != 0) {
            printf("upload part %d ,%s\n",ret ,upload_response.GetMessage().c_str());
            UploadSuperFile_SaveFile(bucket_name, object_name, file_name, upload_id, finish_size, parts);
            delete ifs;
            return ret;
        }
        finish_size += read_number;
        std::string tmp_etag;
        upload_response.GetETag(&tmp_etag);
        parts.push_back(std::make_pair(i, tmp_etag));

        UploadSuperFile_SaveFile(bucket_name, object_name, file_name, upload_id, finish_size, parts);
    }
    delete ifs;

    
    CompleteMultipartUploadRequest complete_request(bucket_name, object_name, upload_id);
    CompleteMultipartUploadResponse complete_response;

    for(unsigned int i = 0; i < parts.size(); i++) {
        complete_request.AddPart(parts[i].first, parts[i].second);
    }
    
    std::map<std::string, std::string>::iterator it;
    for(it = user_meta_data.begin(); it != user_meta_data.end(); it++) {
        complete_request.AddUserMetaData(it->first, it->second);
    }
    
    int ret = CompleteMultipartUpload(complete_request, &complete_response);
    if(ret != 0) {
        printf("complete multipart upload %d %s\n",ret, complete_response.GetMessage().c_str());
        UploadSuperFile_SaveFile(bucket_name, object_name, file_name, upload_id, finish_size, parts);
        return ret;
    }


    std::string tmp;
    complete_response.GetLocation(&tmp);
    result->SetLocation(tmp);
    
    complete_response.GetBucket(&tmp);
    result->SetBucket(tmp);

    complete_response.GetKey(&tmp);
    result->SetObject(tmp);

    complete_response.GetEtag(&tmp);
    result->SetEtag(tmp);
    
    return 0;
}*/





END_C_SDK_NAMESPACE

