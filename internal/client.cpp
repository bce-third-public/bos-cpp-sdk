#include "bos/api.h"
#include "bos/model/request/request.h"
#include "bos/model/response/response.h"
#include "internal/client_impl.h"
#include "internal/file_tool.h"
#include "util/bos_log.h"
// #include "op/oped/noah/webfoot/naming-lib/include/naming.pb.h"
// #include "op/oped/noah/webfoot/naming-lib/include/webfoot_naming.h"
#include <sstream>
// #include "inf/ds/boss/sdk/cpp/src/client_impl_with_bce_auth.h"
namespace bce {
namespace bos {
int Client::GlobalInit() {
    return ClientImpl::GlobalInit();
}

int Client::GlobalUnInit() {
    return ClientImpl::GlobalUnInit();
}

Client::Client(const std::string &access_key_id, const std::string &access_key_secret) {
    m_impl = new ClientImpl(access_key_id, access_key_secret, ClientOptions());
    m_file_tool = new FileTool(m_impl);
}

Client::Client(const std::string &access_key_id, const std::string &access_key_secret,
        const ClientOptions &options) {
    m_impl = new ClientImpl(access_key_id, access_key_secret, options);
    m_file_tool = new FileTool(m_impl);
}

Client::~Client() {
    delete m_impl;
    delete m_file_tool;
}

int Client::GetUrl(GetUrlRequest &request, std::string *result) const {
    return m_impl->GetUrl(request, result);
}

int Client::PutBucket(PutBucketRequest &request, PutBucketResponse *result) const {
    return m_impl->PutBucket(request, result);
}

int Client::ListBucket(ListBucketRequest &request, ListBucketResponse *result) const {
    return m_impl->ListBucket(request, result);
}

int Client::GetBucketConfiguration(GetBucketConfigurationRequest &request, GetBucketConfigurationResponse *result) const {
    return m_impl->GetBucketConfiguration(request, result);
}

int Client::ListObjects(ListObjectsRequest &request, ListObjectsResponse *result) const {
    return m_impl->ListObjects(request, result);
}

int Client::HeadBucket(HeadBucketRequest &request, HeadBucketResponse *result) const {
    return m_impl->HeadBucket(request, result);
}

int Client::DeleteBucket(DeleteBucketRequest &request, DeleteBucketResponse *result) const {
    return m_impl->DeleteBucket(request, result);
}

int Client::PutBucketAcl(PutBucketAclRequest &request, PutBucketAclResponse *result) const {
    return m_impl->PutBucketAcl(request, result);
}

int Client::GetBucketAcl(GetBucketAclRequest &request, GetBucketAclResponse *result) const {
    return m_impl->GetBucketAcl(request, result);
}

int Client::PutObject(const std::string &bucket_name, const std::string &object_name,
            const std::string &data) const {
    PutObjectRequest request(bucket_name, object_name, data);
    PutObjectResponse result;
    return PutObject(request, &result);
}

int Client::PutObject(PutObjectRequest &request, PutObjectResponse *result) const {
    return m_impl->PutObject(request, result);
}

int Client::GetObject(const std::string &bucket_name, const std::string &object_name,
            std::string *data) const {
    GetObjectRequest get_object_request(bucket_name, object_name);
    GetObjectResponse result(data);

    return GetObject(get_object_request, &result);
}

int Client::GetObject(GetObjectRequest &get_object_request, GetObjectResponse *result) const {
    return m_impl->GetObject(get_object_request, result);
}

int Client::DeleteObject(const std::string &bucket_name, const std::string &object_name) const {
    DeleteObjectRequest delete_object_request(bucket_name, object_name);
    DeleteObjectResponse result;

    return DeleteObject(delete_object_request, &result);
}	
int Client::DeleteObject(DeleteObjectRequest &delete_object_request, DeleteObjectResponse *result) const {
    return m_impl->DeleteObject(delete_object_request, result);
}

int Client::HeadObject(HeadObjectRequest &head_object_request, HeadObjectResponse *result) const {
    return m_impl->HeadObject(head_object_request, result);
}
int Client::CopyObject(CopyObjectRequest &copy_object_request, CopyObjectResponse *result) const {
    return m_impl->CopyObject(copy_object_request, result);
}

int Client::InitMultiUpload(InitMultiUploadRequest &init_multi_upload_request, InitMultiUploadResponse *result) const {
    return m_impl->InitMultiUpload(init_multi_upload_request, result);
}
int Client::UploadPart(UploadPartRequest &upload_part_request, UploadPartResponse *result) const {
    return m_impl->UploadPart(upload_part_request, result);
}
int Client::AbortMultipartUpload(AbortMultipartUploadRequest &abort_multipart_upload_request, AbortMultipartUploadResponse *result) const {
    return m_impl->AbortMultipartUpload(abort_multipart_upload_request, result);
}
int Client::CompleteMultipartUpload(CompleteMultipartUploadRequest &complete_multipart_upload_request, CompleteMultipartUploadResponse *result) const {
    return m_impl->CompleteMultipartUpload(complete_multipart_upload_request, result);
}
int Client::ListParts(ListPartsRequest &list_parts_request, ListPartsResponse *result) const {
    return m_impl->ListParts(list_parts_request, result);
}
int Client::ListMultipartUploads(ListMultipartUploadsRequest &list_multipart_uploads_request, ListMultipartUploadsResponse *result) const {
    return m_impl->ListMultipartUploads(list_multipart_uploads_request, result);
}

int Client::UploadFileRequest(const std::string &bucket_name, const std::string &object_name, 
        const std::string &file_name, 
        std::map<std::string, std::string> *user_meta_data, 
        std::string *etag) {
    return m_file_tool->UploadFileRequest(bucket_name, object_name, file_name, user_meta_data, etag);
}

    
int Client::DownloadFileRequest(const std::string &bucket_name, 
        const std::string &object_name,
        const std::string &file_name, 
        int64_t start ,
        int64_t length, 
        std::map<std::string, std::string> *object_meta_data,
        std::string *etag ,
        uint64_t *content_length ,
        std::string *range) {
    return m_file_tool->DownloadFileRequest(bucket_name, object_name, file_name, 
            start, length, object_meta_data, etag, content_length, range);
}

    
int Client::UploadSuperFileRequest(const std::string &bucket_name, 
        const std::string &object_name, 
        const std::string &file_name, 
        std::map<std::string, std::string> *user_meta_data , 
        std::string *etag ) {
    return m_file_tool->UploadSuperFileRequest(bucket_name, object_name, 
            file_name, user_meta_data, etag);       
}

const int DEFUALT_MAX_RETRY_TIMES = 3;

// 默认使用vip的方式
ClientOptions::ClientOptions() {
    boss_host = "bcs.duapp.com";
    timeout = -1;
    auth_version = kBosCompatibleAuth;
}

}
}


