#include "auth/bce_auth.h"

#include "bos/model/request/request.h"
BEGIN_C_SDK_NAMESPACE
BceAuth::BceAuth(const std::string &access_key_id,
        const std::string &access_key_secret, int version)
    : m_authorization_generator(access_key_id, access_key_secret, version) {}

int BceAuth::GenerateAuthorizationString(const std::string &http_method, const std::string &uri,
            const std::map<std::string, std::string> &query_string, const std::map<std::string, std::string> &headers,
            int expiration_period_in_seconds, std::string *authorization_string) {

    return m_authorization_generator.GenerateAuthorizationString(http_method, uri, query_string,
            std::set<std::string>(), headers, "GBK",
            expiration_period_in_seconds, authorization_string);
}
END_C_SDK_NAMESPACE
