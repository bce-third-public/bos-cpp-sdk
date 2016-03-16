#ifndef INF_DS_BOSS_SDK_C_REQUEST_BUCKET_REQUEST_H_
#define INF_DS_BOSS_SDK_C_REQUEST_BUCKET_REQUEST_H_
#include <sstream>
#include "bos/model/request/bos_constraint.h"
#include "bos/model/request/request.h"
namespace bce {
namespace bos {
class BucketRequest : public BosRequest {
public:
    BucketRequest(const std::string &bucket_name, HttpMethod http_method) : BosRequest(http_method) {
        m_bucket_name = bucket_name;

        Log::PrintLog(DEBUG, TRACE, "bucket , " + bucket_name);
    }
    BucketRequest(HttpMethod http_method) : BosRequest(http_method) {
    }

protected:
    virtual std::string GetUri() const {
        std::stringstream ss;
        ss << "/v1/" << m_bucket_name;
	
        return ss.str();
    }

    virtual bool CheckParameter() {
        BosRequest :: CheckParameter();

	    BosConstraint::CheckBucketName(m_bucket_name);

	    return true;
    }
/*	
    virtual bool NeedIncludeInHttpRequest(const std::string &lower_header_key) {
        return BosRequest::NeedIncludeInHttpRequest(lower_header_key);
    }
*/
private:
    std::string m_bucket_name;
};
}
}
#endif // INF_DS_BOSS_SDK_C_REQUEST_BUCKET_REQUEST_H_
