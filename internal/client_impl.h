#ifndef INF_DS_BOSS_SDK_C_SRC_CLIENT_IMPL_H_
#define INF_DS_BOSS_SDK_C_SRC_CLIENT_IMPL_H_

#include <sys/types.h>
#include <regex.h>

#include <map>
#include <string>
#include "bos/api.h"
#include "util/common_def.h"

#include "bos/model/request/request.h"
#include "bos/model/request/put_object_request.h"
#include "bos/model/request/get_object_request.h"
#include "bos/model/request/delete_object_request.h"
#include "bos/model/request/copy_object_request.h"
#include "bos/model/request/init_multi_upload_request.h"
#include "bos/model/request/upload_part_request.h"
#include "bos/model/request/abort_multipart_upload_request.h"
#include "bos/model/request/complete_multipart_upload_request.h"
#include "bos/model/request/list_parts_request.h"
#include "bos/model/request/list_multipart_uploads_request.h"
#include "bos/model/request/list_objects_request.h"
#include "bos/model/request/head_bucket_request.h"
#include "bos/model/request/delete_bucket_request.h"
#include "bos/model/request/put_bucket_acl_request.h"
#include "bos/model/request/get_bucket_acl_request.h"
#include "bos/model/request/get_bucket_configuration_request.h"
#include "bos/model/request/get_url.h"
#include "bos/model/request/list_bucket_request.h"
#include "bos/model/response/response.h"
#include "bos/model/response/put_object_response.h"
#include "bos/model/response/get_object_response.h"
#include "bos/model/response/delete_object_response.h"
#include "bos/model/request/head_object_request.h"
#include "bos/model/response/head_object_response.h"
#include "bos/model/response/copy_object_response.h"
#include "bos/model/response/init_multi_upload_response.h"
#include "bos/model/response/upload_part_response.h"
#include "bos/model/response/abort_multipart_upload_response.h"
#include "bos/model/response/complete_multipart_upload_response.h"
#include "bos/model/response/list_parts_response.h"
#include "bos/model/response/list_multipart_uploads_response.h"
#include "bos/model/response/put_bucket_response.h"
#include "bos/model/request/put_bucket_request.h"
#include "bos/model/response/get_bucket_configuration_response.h"
#include "bos/model/response/list_objects_response.h"
#include "bos/model/response/head_bucket_response.h"
#include "bos/model/response/delete_bucket_response.h"
#include "bos/model/response/put_bucket_acl_response.h"
#include "bos/model/response/get_bucket_acl_response.h"
#include "bos/model/response/list_bucket_response.h"


namespace bce {
namespace bos {
class ObjectMetaData;
class InputStream;
class OutputStream;
class PutObjectResponse;
class PutObjectRequest;
class GetObjectResponse;
class GetObjectRequest;
class DeleteObjectResponse;
class DeleteObjectRequest;
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
class BaseResult;
class BaseRequest;
class ClientOptions;
class ListMultipartUploadsRequest;
class ListMultipartUploadsResponse;
class GetUrlRequest;
}
}

BEGIN_C_SDK_NAMESPACE
#define IMPLEMENT_BOS_API(cmd) int cmd(cmd##Request &request, cmd##Response *response) {\
    return SendRequest(request, response);\
}

class Auth;
class HttpClient;
class HttpRequest;
class HttpResponse;

class ClientImpl {
public:
    static int GlobalInit();
    static int GlobalUnInit();
    ClientImpl(const std::string &access_key_id, const std::string &access_key_secret,
                const bce::bos::ClientOptions &options);
    virtual ~ClientImpl();

    IMPLEMENT_BOS_API(PutObject)
    IMPLEMENT_BOS_API(GetObject)
    IMPLEMENT_BOS_API(GetBucketConfiguration)
    IMPLEMENT_BOS_API(ListObjects)
    IMPLEMENT_BOS_API(HeadBucket)
    IMPLEMENT_BOS_API(DeleteBucket)
    IMPLEMENT_BOS_API(PutBucketAcl)
    IMPLEMENT_BOS_API(GetBucketAcl)
    IMPLEMENT_BOS_API(ListBucket)
    IMPLEMENT_BOS_API(DeleteObject)
    IMPLEMENT_BOS_API(HeadObject)
    IMPLEMENT_BOS_API(CopyObject)

    IMPLEMENT_BOS_API(InitMultiUpload)
    IMPLEMENT_BOS_API(UploadPart)
    IMPLEMENT_BOS_API(AbortMultipartUpload);
    IMPLEMENT_BOS_API(CompleteMultipartUpload);
    IMPLEMENT_BOS_API(ListParts);
    IMPLEMENT_BOS_API(ListMultipartUploads);
    IMPLEMENT_BOS_API(PutBucket);

    int GetUrl(GetUrlRequest &request, std::string *result) const ;


private:

    int SetHttpHeaders(const std::map<std::string, std::string> &headers, HttpRequest *request) const ;

    int SendRequest(BosRequest &request, BosResponse *response) ;


    Auth *m_auth;
    bce::bos::ClientOptions m_options;


    std::string m_access_key_id;
    std::string m_access_key_secret;
};
END_C_SDK_NAMESPACE

#endif // INF_DS_BOSS_SDK_C_SRC_CLIENT_IMPL_H_
