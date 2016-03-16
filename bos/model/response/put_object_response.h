#ifndef INF_DS_BOSS_SDK_CPP_RESPONSE_PUT_OBJECT_RESPONSE_H_
#define INF_DS_BOSS_SDK_CPP_RESPONSE_PUT_OBJECT_RESPONSE_H_

#include "bos/model/response/response.h"
namespace bce {
namespace bos {

class PutObjectResponse : public BosResponse {
public:
    virtual ~PutObjectResponse() {
    }

    int GetETag(std::string *etag) const {
        return GetResponseHeader("ETag", etag);
    }

    int GetVersion(std::string *version) const {
        return GetResponseHeader("x-bce-version", version);
    }
};
}
}
#endif // INF_DS_BOSS_SDK_CPP_RESPONSE_PUT_OBJECT_RESPONSE_H_
