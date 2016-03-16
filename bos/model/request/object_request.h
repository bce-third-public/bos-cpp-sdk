#ifndef INF_DS_BOSS_SDK_C_REQUEST_OBJECT_REQUEST_H_
#define INF_DS_BOSS_SDK_C_REQUEST_OBJECT_REQUEST_H_
#include <sstream>

#include "bos/model/request/request.h"
#include "bos/model/request/bos_constraint.h"

namespace bce {
namespace bos {
class ObjectRequest : public BosRequest {
public:
    ObjectRequest(const std::string &bucket_name, const std::string &object_name,
            HttpMethod http_method) : BosRequest(http_method) {

        m_bucket_name = bucket_name;
        m_object_name = object_name;

        Log::PrintLog(DEBUG, TRACE, "bucket , " + bucket_name);
        Log::PrintLog(DEBUG, TRACE, "object , " + object_name);
    }

protected:
    virtual std::string GetUri() const {
        std::stringstream ss;
        ss << "/v1/" << m_bucket_name << "/" << m_object_name;

        return ss.str();
    }

    virtual bool CheckParameter() {
        BosRequest::CheckParameter();

        BosConstraint::CheckBucketName(m_bucket_name);
        BosConstraint::CheckObjectName(m_object_name);

        return true;
    }

    virtual bool NeedIncludeInHttpRequest(const std::string &lower_header_key) {
        return BosRequest::NeedIncludeInHttpRequest(lower_header_key);
    }

private:
    std::string m_bucket_name;
    std::string m_object_name;
};
}
}
#endif // INF_DS_BOSS_SDK_C_REQUEST_OBJECT_REQUEST_H_
