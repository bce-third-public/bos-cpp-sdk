#include "bos/model/request/put_bucket_request.h"
#include "openssl/md5.h"
#include "openssl/sha.h"
#include "zlib.h"

#include "util/memory_stream.h"
#include "util/encrypt_util.h"
#include "json/json.h"
namespace bce {
namespace bos {
PutBucketRequest::PutBucketRequest(const std::string &bucket_name) : 
    BucketRequest(bucket_name, kHttpPut) {
}

PutBucketRequest::~PutBucketRequest() {
}

int PutBucketRequest::BuildCommandSpecific(HttpRequest *request) {
    SetRequestHeader("Content-Length", "0");
    return 0;
}


}
}

