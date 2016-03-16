#ifndef INF_BCE_BOS_SDK_CPP_INTERNAL_CLIENT_IMPL_V25_H
#define INF_BCE_BOS_SDK_CPP_INTERNAL_CLIENT_IMPL_V25_H

#include "src/auth_v25.h"
#include "src/client_impl.h"
BEGIN_C_SDK_NAMESPACE
class ClientImplV25 : public ClientImpl {
public:
    ClientImplV25(const std::string &access_key_id, const std::string &access_key_secret,
            const ClientOptions &options) : ClientImpl(access_key_id, access_key_secret, options) {
        m_auth = new AuthV25(access_key_id, access_key_secret);
    }

    virtual ~ClientImplV25() {
        if (m_auth != NULL) {
            delete m_auth;
            m_auth = NULL;
        }
    }

    virtual int AddAuthInfo(const std::string &bucket_name, const std::string &object_name,
            HttpRequest *http_request) const {
        std::string http_method = request->GetHttpMethod();
        return 0;
    }

private:
    AuthV25 *m_auth;
};
END_C_SDK_NAMESPACE

#endif // INF_BCE_BOS_SDK_CPP_INTERNAL_CLIENT_IMPL_V25_H
