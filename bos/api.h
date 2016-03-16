#ifndef INF_DS_BOSS_SDK_C_API_API_H_
#define INF_DS_BOSS_SDK_C_API_API_H_

#include <map>
#include <string>
#include <stdint.h>
#include <time.h>
#include <vector>

namespace bce {
namespace bos {
class FileTool;
class ClientImpl;
class ObjectMetaDataImpl;
class PutObjectRequest;
class GetObjectRequest;
class PutObjectResponse;
class GetObjectResponse;
class DeleteObjectRequest;
class DeleteObjectResponse;
class HeadObjectRequest;
class HeadObjectResponse;
class CopyObjectRequest;
class CopyObjectResponse;
class InitMultiUploadRequest;
class InitMultiUploadResponse;
class UploadPartRequest;
class UploadPartResponse;
class AbortMultipartUploadRequest;
class AbortMultipartUploadResponse;
class CompleteMultipartUploadRequest;
class CompleteMultipartUploadResponse;
class ListPartsRequest;
class ListPartsResponse;
class PutBucketRequest;
class PutBucketResponse;
class ListMultipartUploadsRequest;
class ListMultipartUploadsResponse;
class ListBucketRequest;
class ListBucketResponse;
class GetBucketConfigurationRequest;
class GetBucketConfigurationResponse;
class ListObjectsRequest;
class ListObjectsResponse;
class HeadBucketRequest;
class HeadBucketResponse;
class DeleteBucketRequest;
class DeleteBucketResponse;
class PutBucketAclRequest;
class PutBucketAclResponse;
class GetBucketAclRequest;
class GetBucketAclResponse;
class GetUrlRequest;
class InputStream;
class OutputStream;
const int kBosOk = 0;
const int kBosIllegalArgument = -1000;
const int kBosNetError = -1001;
const int kBosClientError = -1002;
const int kBosServiceError = -1003;
const int kBosUnknownError = -1005;
struct ClientOptions {
    ClientOptions();
    std::string boss_host;
    int32_t timeout;
    enum AuthVersion {
        kBosCompatibleAuth,
        kBceAuth
    };
    AuthVersion auth_version;
};

class Client {
public:
    static int GlobalInit();
    static int GlobalUnInit();
    Client(const std::string &access_key_id, const std::string &access_key_secret);
    Client(const std::string &access_key_id, const std::string &access_key_secret,
            const ClientOptions &options);
    ~Client();

    int PutObject(const std::string &bucket_name, const std::string &object_name, const std::string &data) const ;
    int GetObject(const std::string &bucket_name, const std::string &object_name, std::string *data) const ;
    int DeleteObject(const std::string &bucket_name, const std::string &object_name) const ;
    int InitMultiUpload(const std::string &bucket_name, const std::string &object_name, std::string *upload_id) const ;

    int GetUrl(GetUrlRequest &request, std::string *result) const ;
    


    int PutObject(PutObjectRequest &request, PutObjectResponse *result) const ;
    int GetObject(GetObjectRequest &get_object_request, GetObjectResponse *result) const;
    int DeleteObject(DeleteObjectRequest &delete_object_request, DeleteObjectResponse *result) const;
    int HeadObject(HeadObjectRequest &head_object_request, HeadObjectResponse *result) const ;
    int CopyObject(CopyObjectRequest &copy_object_request, CopyObjectResponse *result) const ;
    int InitMultiUpload(InitMultiUploadRequest &init_multi_upload_request, InitMultiUploadResponse *result) const ;
    int UploadPart(UploadPartRequest &upload_part_request, UploadPartResponse *result) const ;
    int AbortMultipartUpload(AbortMultipartUploadRequest &abort_multipart_upload_request, AbortMultipartUploadResponse *result) const ;
    int CompleteMultipartUpload(CompleteMultipartUploadRequest &complete_multipart_upload_request, CompleteMultipartUploadResponse *result) const ;
    int ListParts(ListPartsRequest &list_parts_request, ListPartsResponse *result) const ;
    int ListMultipartUploads(ListMultipartUploadsRequest &list_multipart_uploads_request, ListMultipartUploadsResponse *result) const ;
    int PutBucket(PutBucketRequest &request, PutBucketResponse *result) const ;
    int ListBucket(ListBucketRequest &request, ListBucketResponse *result) const ;
    int GetBucketConfiguration(GetBucketConfigurationRequest &request, GetBucketConfigurationResponse *result) const;   
    int ListObjects(ListObjectsRequest &request, ListObjectsResponse *result) const ;
    int HeadBucket(HeadBucketRequest &request, HeadBucketResponse *result) const ;
    int DeleteBucket(DeleteBucketRequest &request, DeleteBucketResponse *result) const;
    int PutBucketAcl(PutBucketAclRequest &request, PutBucketAclResponse *result) const ;
    int GetBucketAcl(GetBucketAclRequest &request, GetBucketAclResponse *result) const ;
    
    int UploadFileRequest(const std::string &bucket_name, const std::string &object_name, 
        const std::string &file_name, 
        std::map<std::string, std::string> *user_meta_data = NULL, 
        std::string *etag = NULL);

    
    int DownloadFileRequest(const std::string &bucket_name, 
        const std::string &object_name,
        const std::string &file_name, 
        int64_t start = -1,
        int64_t length = -1, 
        std::map<std::string, std::string> *object_meta_data = NULL,
        std::string *etag = NULL,
        uint64_t *content_length = NULL,
        std::string *range = NULL) ;

    
    int UploadSuperFileRequest(const std::string &bucket_name, const std::string &object_name, 
        const std::string &file_name, 
        std::map<std::string, std::string> *user_meta_data = NULL, 
        std::string *etag = NULL );

private:
    ClientImpl *m_impl;
    FileTool *m_file_tool;
};
}
}

#endif // INF_DS_BOSS_SDK_C_API_API_H_
