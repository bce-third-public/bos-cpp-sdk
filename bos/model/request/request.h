#ifndef INF_DS_BOSS_SDK_C_API_REQUEST_H_
#define INF_DS_BOSS_SDK_C_API_REQUEST_H_
#include <stdint.h>
#include <map>
#include <string>
#include <sstream>

#include "bos/model/request/http_request.h"
#include "bos/api.h"
#include "util/bos_log.h"

namespace bce {
namespace bos {
class OutputStream;
class InputStream;
class Auth;
class ClientOptions;

class BosRequest {
public:
    BosRequest(HttpMethod http_method);
    virtual ~BosRequest() {
    }

    void SetRequestHeader(const std::string &key, const std::string &val);
    void SetQueryString(const std::string &key, const std::string &val);
    const std::map<std::string, std::string> &GetRequestHeader() const {
        return m_headers;
    }

    const std::map<std::string, std::string> &GetQueryStringMap() const {
        return m_query_string_map;
    }

    int BuildHttpRequest(const ClientOptions &client_options, const Auth &auth, HttpRequest *request);

    std::string GetRequestUrl(const std::string &host) const;
    std::string GetStringHttpMethod() const;

    std::string GetQueryString() const;
    virtual std::string GetUri() const {
        std::stringstream ss;
        ss << "/v1/";
	
        return ss.str();
    }

protected:
    virtual bool CheckParameter() {
        return true;
    }

    virtual InputStream *GetInputStream() {
        return m_input_stream;
    }

    void SetInputStream(InputStream * input_stream) {
        m_input_stream = input_stream;
    }

    virtual bool NeedIncludeInHttpRequest(const std::string &lower_header_key) {
        return true;
    }

    virtual int BuildCommandSpecific(HttpRequest *request) {
        return 0;
    }
    virtual int CalculateObjectFinger(bce::bos::InputStream *stream, std::string *md5, std::string *sha256) const {
    	return 0;
    }
    

private:
    HttpMethod m_http_method;
    std::string m_host;
    std::map<std::string, std::string> m_headers;
    std::map<std::string, std::string> m_query_string_map;

    int m_timeout;

    std::string m_request_id;
    InputStream *m_input_stream;
};

/*
class GetObjectRequest : public BosRequest {
public:
    GetObjectRequest(const std::string &bucket_name, const std::string &object_name);
    virtual ~GetObjectRequest() {
    }
    int SetRange(int64_t start, int64_t length);
    int SetVersion(const std::string &version);

private:
};

class PutObjectRequest : public BosRequest {
public:
    PutObjectRequest(const std::string &bucket_name, const std::string &object_name,
            const std::string &data);
    PutObjectRequest(const std::string &bucket_name, const std::string &object_name,
            InputStream *stream);
    virtual ~PutObjectRequest();
    int AddUserMetaData(const std::string &key, const std::string &value);

    InputStream *GetInputStream() const {
        return m_input;
    }

private:
    InputStream *m_input;
    bool m_owner_of_input;
};
*/
}
}

#endif // INF_DS_BOSS_SDK_C_API_REQUEST_H_
