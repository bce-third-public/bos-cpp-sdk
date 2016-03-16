#ifndef INF_DS_BOSS_SDK_C_SRC_BCE_AUTH_H_
#define INF_DS_BOSS_SDK_C_SRC_BCE_AUTH_H_
#include "util/authorization_util.h"
#include "util/common_def.h"
namespace bce {
namespace bos {
class BaseRequest;
}
}
BEGIN_C_SDK_NAMESPACE
class BceAuth {
public:
    BceAuth(const std::string &access_key_id, const std::string &access_key_secret, int version);
    virtual ~BceAuth() {
    }

    int GenerateAuthorizationString(const std::string &http_method, const std::string &uri,
            const std::map<std::string, std::string> &query_string, const std::map<std::string, std::string> &headers,
            int expiration_period_in_seconds, std::string *authorization_string);

protected:
    AuthorizationGenerator m_authorization_generator;
};
END_C_SDK_NAMESPACE

#endif // INF_DS_BOSS_SDK_C_SRC_BCE_AUTH_H_
