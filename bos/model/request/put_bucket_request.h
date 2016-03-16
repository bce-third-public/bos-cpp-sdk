#ifndef INF_DS_BOSS_SDK_C_REQUEST_PUT_BUCKET_REQUEST_H_
#define INF_DS_BOSS_SDK_C_REQUEST_PUT_BUCKET_REQUEST_H_
#include <sstream>

#include "bos/model/request/bucket_request.h"
#include "bos/model/request/bos_constraint.h"

namespace bce {
namespace bos {
class PutBucketRequest : public BucketRequest {
public:
    PutBucketRequest(const std::string &bucket_name);

    virtual ~PutBucketRequest();

protected:
    int BuildCommandSpecific(HttpRequest *request);

};
}
}
#endif // INF_DS_BOSS_SDK_C_REQUEST_PUT_BUCKET_REQUEST_H_
