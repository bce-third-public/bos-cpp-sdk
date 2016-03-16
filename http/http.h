#ifndef INF_DS_BOSS_SDK_C_SRC_HTTP_H_
#define INF_DS_BOSS_SDK_C_SRC_HTTP_H_

#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "util/common_def.h"
#include "util/memory_stream.h"

#include "bos/model/request/http_request.h"
#include "bos/model/response/http_response.h"

namespace bce {
namespace bos {
class InputStream;
class OutputStream;
}
}

BEGIN_C_SDK_NAMESPACE
/*
class HttpHeader {
public:
    int ParseFromStream(const bce::bos::InputStream &input);

    int SetHttpHeader(const std::string &key, const std::string &value);
    int GetHttpHeader(const std::string &key, std::string *data) const;

    int SetUserDefineHeader(const std::string &key, const std::string &value);
    int GetUserDefineHeader(const std::string &key, std::string *data) const;

    int GetAllHeaders(std::vector<std::string> *headers) const;
    int GetAllHeaders(std::map<std::string, std::string> *headers) const {
        headers->insert(m_headers.begin(), m_headers.end());
        return 0;
    }
    int GetHttpHeaders(std::vector<std::string> *headers) const;
    int GetUserDefineHeaders(std::vector<std::string > *headers) const;

    int SetHeader(const std::string &key, const std::string &data);
    int GetHeader(const std::string &key, std::string *data) const ;

    void Print() const {
        std::map<std::string, std::string>::const_iterator it =  m_headers.begin();

        for (; it != m_headers.end(); it++) {
            printf("key:%s, data:%s\n", it->first.c_str(), it->second.c_str());
        }
    }

    const std::map<std::string, std::string> &GetHeaders() const {
        return m_headers;
    }

private:
    std::map<std::string, std::string> m_headers;
};
class HttpRequest {
public:
    HttpRequest() {
        m_stream = NULL;
        m_timeout = -1;
    }

    int GetAllHeaders(std::vector<std::string > *headers) const {
        return m_header.GetAllHeaders(headers);
    }

    int SetHeader(const std::string &key, const std::string &data) {
        return m_header.SetHeader(key, data);
    }

    int GetHeader(const std::string &key, std::string *data) const {
        return m_header.GetHeader(key, data);
    }

    const std::map<std::string, std::string> &GetHeaders() const {
        return m_header.GetHeaders();
    }

    void SetTimeout(int timeout) {
        m_timeout = timeout;
    }

    int GetTimeout() const {
        return m_timeout;
    }

    std::string GetRequestUrl() const;

    GENERATE_FIELD_GETTER_AND_SETTER(std::string, HttpMethod, http_method)
    GENERATE_FIELD_GETTER_AND_SETTER(std::string, Uri, uri)
    GENERATE_FIELD_GETTER_AND_SETTER(std::string, QueryString, query_string)
    GENERATE_FIELD_GETTER_AND_SETTER(std::string, HttpHost, http_host);
    GENERATE_PTR_FIELD_GETTER_AND_SETTER(bce::bos::InputStream, InputStream, stream)

private:
    std::string m_http_method;
    std::string m_http_host;
    std::string m_uri;
    std::string m_query_string;

    HttpHeader m_header;
    bce::bos::InputStream *m_stream;
    int m_timeout;
};
*/
class HttpClient {
public:
    static int Init();
    static int UnInit();
    static int Request(const HttpRequest &request, HttpResponse *response);

private:
    static size_t WriteStream(void *ptr, size_t size, size_t nmemb, void *stream);
    static size_t ReadStream(void *ptr, size_t size, size_t nmemb, void *stream);
    static size_t RecvHeaderLine(void *ptr, size_t size, size_t nmemb, void *user_data);
};
END_C_SDK_NAMESPACE

#endif // INF_DS_BOSS_SDK_C_SRC_HTTP_H_
