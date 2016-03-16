#include "bos/model/request/request.h"

#include <uuid/uuid.h>
#include <sstream>
#include <algorithm>

#include "bos/api.h"
#include "util/memory_stream.h"

#include "util/time_util.h"
#include "util/string_util.h"
#include "auth/auth.h"

namespace bce {
namespace bos {

inline std::string num_to_string(int num) {
    std::ostringstream sstream;
    sstream << num;
    return sstream.str();
}

BosRequest::BosRequest(HttpMethod http_method) {
    m_http_method = http_method;
    m_input_stream = NULL;
    m_timeout = -1;
    std::string t_method = GetStringHttpMethod();
    Log::PrintLog(DEBUG, TRACE, "Http method : " + t_method); 
    SetRequestHeader("Expect", "");
}

void BosRequest::SetRequestHeader(const std::string &key, const std::string &val) {
    m_headers[key] = val;
   
    Log::PrintLog(DEBUG, TRACE, "add request header , " + key +" : " + val); 
}
void BosRequest::SetQueryString(const std::string &key, const std::string &val){
    m_query_string_map[key] = val;
    
    Log::PrintLog(DEBUG, TRACE, "add query string , " + key +" : " + val); 
}

int BosRequest::BuildHttpRequest(const ClientOptions &client_options, const Auth &auth,
        HttpRequest *request) {
	
    CheckParameter();

    if (m_request_id.size() == 0) {
        uuid_t out;
        uuid_generate(out);
        m_request_id.resize(36);
        uuid_unparse(out, const_cast<char *>(m_request_id.data()));
        std::transform(m_request_id.begin(), m_request_id.end(), m_request_id.begin(), ::tolower);
    }
    SetRequestHeader("x-bce-request-id", m_request_id);

    std::string host = client_options.boss_host;
    SetRequestHeader("Host", host);

    const std::string now_time= TimeUtil::NowUtcTime();
    SetRequestHeader("x-bce-date", now_time);

    BuildCommandSpecific(request);
    std::string authorization_string;

    if (auth.GenerateAuthorizationString(*this, &authorization_string)) {
        return kBosClientError;
    }

    SetRequestHeader("Authorization", authorization_string);


    std::map<std::string, std::string>::const_iterator it = m_headers.begin();
    for (; it != m_headers.end(); it++) {
        if (NeedIncludeInHttpRequest(StringUtil::ToLower(it->first))) {
            request->AddHttpHeader(it->first, it->second);
        }
    }

    request->SetUrl(GetRequestUrl(client_options.boss_host));

    Log::PrintLog(DEBUG, TRACE, "url , " + GetRequestUrl(client_options.boss_host));
     
    request->SetHttpMethod(m_http_method);
 
    request->SetInputStream(GetInputStream());

    if (m_timeout < 0) {
        m_timeout = client_options.timeout;
    }
    request->SetTimeout(m_timeout);
    Log::PrintLog(DEBUG, TRACE, "timeout , " + num_to_string(m_timeout));

    return 0;
}

std::string BosRequest::GetRequestUrl(const std::string &host) const {
    std::stringstream ss;
    ss << "http://" << host << StringUtil::UriEncode(GetUri(), false);
    if (m_query_string_map.size() == 0) {
        return ss.str();
    }

    ss << "?";
    std::map<std::string, std::string>::const_iterator it = m_query_string_map.begin();
    ss << it->first << "=" << StringUtil::UriEncode(it->second);
    it++;

    for (; it != m_query_string_map.end(); it++) {
        ss << "&" << it->first << "=" << StringUtil::UriEncode(it->second);
    }

    return ss.str();
}

std::string BosRequest::GetStringHttpMethod() const {
    switch (m_http_method) {
    case kHttpGet:
        return "GET";
    case kHttpPut:
        return "PUT";
    case kHttpPost:
        return "POST";
    case kHttpHead:
        return "HEAD";
    case kHttpDelete:
        return "DELETE";
    default:
        return "";
    }
}

std::string BosRequest::GetQueryString() const {
    std::stringstream ss;
    std::map<std::string, std::string>::const_iterator it = m_query_string_map.begin();
    if( !m_query_string_map.empty() ){
        ss << it->first << "=" << StringUtil::UriEncode(it->second);
        it++;

        for (; it != m_query_string_map.end(); it++) {
            ss << "&" << it->first << "=" << StringUtil::UriEncode(it->second);
        }

        return ss.str();
    }
    return "";
}
}
}
