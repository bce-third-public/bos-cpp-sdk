#include "auth/auth.h"

#include <sstream>
#include <string>

#include "util/encrypt_util.h"
#include "util/exception.h"
#include "bos/model/request/request.h"

BEGIN_C_SDK_NAMESPACE
Auth::Auth(const std::string &access_key_id, const std::string &access_key_secret) {
    m_access_key_id = access_key_id;
    m_access_key_secret = access_key_secret;
    m_auth = new BceAuth(access_key_id, access_key_secret, 1);//
}

int Auth::GenerateAuthorizationString(const BosRequest &request,
            std::string *authorization_string) const {
    std::string http_method = request.GetStringHttpMethod();
    std::string uri = request.GetUri();
    const std::map<std::string, std::string> &query_string = request.GetQueryStringMap();
    //const std::string query_string = request.GetQueryString();
    const std::map<std::string, std::string> &http_headers = request.GetRequestHeader();

    if (m_auth->GenerateAuthorizationString(http_method, uri,
                query_string, http_headers, 1800, authorization_string)) {
        throw BosClientException("generate authorizatuin string fail");
    }
    return 0;
}

END_C_SDK_NAMESPACE
