#ifndef INF_DS_BOSS_SDK_C_REQUEST_GET_OBJECT_REQUEST_H_
#define INF_DS_BOSS_SDK_C_REQUEST_GET_OBJECT_REQUEST_H_
#include <sstream>

#include "bos/model/request/object_request.h"
#include "bos/model/request/bos_constraint.h"

namespace bce {
namespace bos {
class GetObjectRequest : public ObjectRequest {
public:
    GetObjectRequest(const std::string &bucket_name, const std::string &object_name);

    virtual ~GetObjectRequest() {
    }

    int SetRange(int64_t start, int64_t length);

    int SetVersion(const std::string &version);
};
}
}
#endif // INF_DS_BOSS_SDK_C_REQUEST_GET_OBJECT_REQUEST_H_
