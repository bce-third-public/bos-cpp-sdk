#ifndef INF_DS_BOSS_SDK_C_SRC_AUTH_H_
#define INF_DS_BOSS_SDK_C_SRC_AUTH_H_
#include <string>

#include "util/common_def.h"
#include "auth/bce_auth.h"

BEGIN_C_SDK_NAMESPACE
class BosRequest; //
class Auth {
public:
    Auth(const std::string &access_key_id, const std::string &access_key_secret);
    virtual ~Auth() {
        if (m_auth != NULL) {
            delete m_auth;
        }
    }

    virtual int GenerateAuthorizationString(const BosRequest &request,
            std::string *authorization_string) const;

protected:
    std::string m_access_key_id;
    std::string m_access_key_secret;

    BceAuth *m_auth;
};
END_C_SDK_NAMESPACE

#endif // INF_DS_BOSS_SDK_C_SRC_AUTH_H_
