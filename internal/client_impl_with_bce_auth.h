#ifndef INF_DS_BOSS_SDK_C_SRC_CLIENT_IMPL_WITH_BCE_AUTH_H_
#define INF_DS_BOSS_SDK_C_SRC_CLIENT_IMPL_WITH_BCE_AUTH_H_
#include "util/string_util.h"
#include "src/bce_auth.h"
#include "src/client_impl.h"
#include "src/exception.h"
#include "src/http.h"
BEGIN_C_SDK_NAMESPACE
class ClientImplWithBceAuth : public ClientImpl {
public:
    ClientImplWithBceAuth(const std::string &access_key_id, const std::string &access_key_secret,
            const bce::bos::ClientOptions &options)
        : ClientImpl(access_key_id, access_key_secret, options) {
        m_auth = new BceAuth(access_key_id, access_key_secret, 1);
    }

    virtual ~ClientImplWithBceAuth() {
        if (m_auth != NULL) {
            delete m_auth;
            m_auth = NULL;
        }
    }

    virtual int AddAuthInfo(const std::string &bucket_name, const std::string &object_name,
            HttpRequest *http_request) const {
        std::string http_method = http_request->GetHttpMethod();
        std::string query_string = http_request->GetQueryString();
        const std::map<std::string, std::string> &http_headers = http_request->GetHeaders();

        std::stringstream ss;
        ss << "/json-api/v1/" << bucket_name << "/" << object_name;
        std::string uri = ::baidu::inf::ds::boss::StringUtil::UriEncode(ss.str(), false);
        http_request->SetUri(uri);

        std::string authorization_string;
        if (m_auth->GenerateAuthorizationString(http_method, uri,
                    query_string, http_headers, 1800, &authorization_string)) {
            throw BosClientException("generate authorizatuin string fail");
        }

        http_request->SetHeader("Authorization", authorization_string);
        printf("%s\n", authorization_string.c_str());
        return 0;
    }

private:
    BceAuth *m_auth;
};
END_C_SDK_NAMESPACE
#endif // INF_DS_BOSS_SDK_C_SRC_CLIENT_IMPL_WITH_BCE_AUTH_H_
