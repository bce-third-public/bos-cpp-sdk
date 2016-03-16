/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file upload_super_file.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/08/07 16:07:28
 * @brief 
 *  
 **/

#include "internal/upload_super_file.h"
#include "bos/model/request/upload_part_request.h"
#include "bos/model/response/upload_part_response.h"
#include "bos/model/request/init_multi_upload_request.h"
#include "bos/model/response/init_multi_upload_response.h"
#include "bos/model/request/complete_multipart_upload_request.h"
#include "bos/model/response/complete_multipart_upload_response.h"

namespace bce {
namespace bos {

int UploadSuperFile::SaveCache(const std::string &upload_id, 
        const std::vector<std::pair<int, std::string> > &parts) {

    Json::Value value;
    value["bucket"] = Json::Value(m_bucket_name);
    value["object"] = Json::Value(m_object_name);
    value["file"] = Json::Value(m_file_name);
    value["uploadId"] = Json::Value(upload_id);
    for (unsigned int i = 0; i < parts.size(); i++) {
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
    
int UploadSuperFile::LoadCache(std::string *upload_id, 
        std::vector<std::pair<int, std::string> > *parts, 
        bool *uploaded_part) {

    FileInputStream  t_ifs("parts_data");
    std::string buffer;

    Json::Reader reader;
    Json::Value value;
      
    if (t_ifs.GetSize() != -1001 
            && t_ifs.Read(t_ifs.GetSize(), &buffer) != -1001 
            && reader.parse(buffer, value)) {
        std::string t_bucket = value["bucket"].asString();
        std::string t_object = value["object"].asString();
        std::string t_file = value["file"].asString();
        
        if (t_bucket == m_bucket_name && t_object == m_object_name && t_file == m_file_name) {
            upload_id->assign(value["uploadId"].asString());
            Json::Value j_parts;
            j_parts = value["parts"];
            for (unsigned int i = 0; i < j_parts.size(); i++) {
                int t_part_number = j_parts[i]["partNumber"].asInt();
                std::string t_etag = j_parts[i]["eTag"].asString();
                parts->push_back(make_pair(t_part_number, t_etag));
                uploaded_part[t_part_number] = true;
            }

            return 0;
        }
    }
    return -1;
    
}

void* UploadSuperFile::ThreadUpload(void* argv) {
    ThreadData *data = (ThreadData *)argv;
    ClientImpl *client = data->m_client;
    std::string *bucket_name = data->m_bucket;
    std::string *object_name = data->m_object;
    std::string *upload_id = data->m_upload_id;
    std::string *buffer = data->m_buffer;
    int part_number = data->m_part_number;

    UploadPartRequest request(*bucket_name, *object_name, *buffer, part_number, *upload_id);
    UploadPartResponse response;

    int ret = client->UploadPart(request, &response);

  //  ret = client->UploadPart(request, &response);
    data->m_ret = ret;
    if (ret != 0) {
        printf("upload part error %d %s\n", ret, response.GetMessage().c_str());
        pthread_exit(NULL);
    }
    
    std::string etag;
    response.GetETag(&etag);
    data->m_etag->assign(etag);
    pthread_exit(NULL);
}

int UploadSuperFile::Upload() {

    std::string upload_id; 
    std::vector<std::pair<int, std::string> > parts;
    
    bool uploaded_part[10005];
    memset(uploaded_part, false, sizeof(uploaded_part));
    
    FileInputStream *ifs = new FileInputStream(m_file_name);
    
    if (ifs->GetSize() == -1001) {
        delete ifs;
        printf("Upload part : no such file!\n");
        return kBosClientError;
    }

    delete ifs;

    int ret = LoadCache(&upload_id, &parts, uploaded_part);
    
    if (ret != 0) {

        InitMultiUploadRequest init_request(m_bucket_name, m_object_name);
        InitMultiUploadResponse init_response;
    
        int ret = m_client->InitMultiUpload(init_request, &init_response);
        if (ret != 0) {
            printf("ini multi upload %d %s\n",ret,init_response.GetMessage().c_str());
            return ret;
        }

        std::string tmp_bucket_name; 
        std::string tmp_object_name;

        init_response.GetBucket(&tmp_bucket_name);
        init_response.GetKey(&tmp_object_name);

        if (tmp_bucket_name != m_bucket_name || tmp_object_name != m_object_name) {
                printf("LOG : bucket_name or object_name does not match!\n");
            return kBosServiceError;
        }
        init_response.GetUploadId(&upload_id);

    }
    SaveCache(upload_id, parts);
 //   exit(0);

    ifs = new FileInputStream(m_file_name);
    
    pthread_t thread[5];
    ThreadData thread_data[5];
    std::string t_etag[5];
    int pthread_count = 0;
    int pthread_number = 5;
    for (int i = 1; i <= 10000; i++) {

        std::string *data = new std::string;
        int read_number = ifs->Read(5*1024*1024, data);
        if (read_number <= 0) {
            delete data;
            int flag = -2;
            for (int j = 0; j < pthread_count; j++) {
                int tmp = pthread_join(thread[j], NULL); 
                if(tmp != 0) {
                    printf("pthread_join error\n");
                }
                delete thread_data[j].m_buffer;
                if(thread_data[j].m_ret != 0) {
                    flag = thread_data[j].m_ret;
                    continue;
                }
                parts.push_back(make_pair(thread_data[j].m_part_number, *thread_data[j].m_etag));
                uploaded_part[thread_data[j].m_part_number] = true;
            }

            SaveCache(upload_id, parts);
            if(flag != -2) {
                delete ifs;
                return flag;
            }
            break;
        }

        if (uploaded_part[i])
            continue;
        thread_data[pthread_count].m_client = m_client;
        thread_data[pthread_count].m_bucket = &m_bucket_name;
        thread_data[pthread_count].m_object = &m_object_name;
        thread_data[pthread_count].m_upload_id = &upload_id;
        thread_data[pthread_count].m_buffer = data;
        thread_data[pthread_count].m_part_number = i;
        thread_data[pthread_count].m_etag = &t_etag[pthread_count];
        int tmp = pthread_create(&thread[pthread_count], 
                NULL, ThreadUpload, (void *)&thread_data[pthread_count]);
        if (tmp != 0) {
            printf("pthread_create error\n");
        }
        pthread_count++;
        if (pthread_count == pthread_number) {
            pthread_count = 0;
            int flag = -2;
            for (int j = 0; j < pthread_number; j++) {
                int tmp = pthread_join(thread[j], NULL);
                if (tmp != 0) {
                    printf("pthread join error\n");
                }
                delete thread_data[j].m_buffer;
                if (thread_data[j].m_ret != 0) {
                    flag = thread_data[j].m_ret;
                    continue;
                }
                parts.push_back(make_pair(thread_data[j].m_part_number, *thread_data[j].m_etag));
                uploaded_part[thread_data[j].m_part_number] = true;
            }
          //  exit(0);
            SaveCache(upload_id, parts);
            if (flag != -2) {
                delete ifs;
                return flag;
            }
            //exit(0);

        }

    }
    delete ifs;
    
    CompleteMultipartUploadRequest complete_request(m_bucket_name, m_object_name, upload_id);
    CompleteMultipartUploadResponse complete_response;

    for (unsigned int i = 0; i < parts.size(); i++) {
        complete_request.AddPart(parts[i].first, parts[i].second);
    }
    
    std::map<std::string, std::string>::iterator it;
    for (it = m_user_meta_data.begin(); it != m_user_meta_data.end(); it++) {
        complete_request.AddUserMetaData(it->first, it->second);
    }
    
    ret = m_client->CompleteMultipartUpload(complete_request, &complete_response);
    if (ret != 0) {
        printf("complete multipart upload %d %s\n", ret, complete_response.GetMessage().c_str());
        return ret;
    
    }

    complete_response.GetLocation(&m_location);
    complete_response.GetBucket(&m_bucket);
    complete_response.GetKey(&m_key);
    complete_response.GetETag(&m_etag);

    FILE *fp = fopen("parts_data", "w");
    fclose(fp);

    return 0;
    
}

}
}


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
