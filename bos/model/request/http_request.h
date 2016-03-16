#ifndef INF_DS_BOSS_SDK_C_REQUEST_HTTP_REQUEST_H_
#define INF_DS_BOSS_SDK_C_REQUEST_HTTP_REQUEST_H_
#include <string>
#include <vector>
namespace bce {
namespace bos {
class InputStream;
enum HttpMethod {
    kInvalidHttpMethod,
    kHttpPut,
    kHttpGet,
    kHttpPost,
    kHttpHead,
    kHttpDelete
};
class InputStream;

class HttpRequest {
public:
    HttpRequest() {
        m_method = kInvalidHttpMethod;
        m_in_stream = NULL;
    }

    void SetInputStream(InputStream *in_stream) {
        m_in_stream = in_stream;
    }

    const InputStream *GetInputStream() const {
        return m_in_stream;
    }

    void SetHttpMethod(HttpMethod method) {
        m_method = method;
    }

    HttpMethod GetHttpMethod() const {
        return m_method;
    }

    void AddHttpHeader(const std::string &key, const std::string &val) {
        m_headers[key] = val;
    }

    const std::map<std::string, std::string> &GetHttpHeader() const {
        return m_headers;
    }

    void SetUrl(const std::string &url) {
        m_url = url;
    }

    std::string GetUrl() const {
        return m_url;
    }

    int GetAllHeaders(std::vector<std::string> *header) const {
        std::map<std::string, std::string>::const_iterator it = m_headers.begin();
        for (; it != m_headers.end(); it++) {
            header->push_back(it->first + ":" + it->second);
        }

        return 0;
    }

    int GetTimeout() const {
        return m_timeout;
    }

    void SetTimeout(int timeout) {
        m_timeout = timeout;
    }

private:
    InputStream *m_in_stream;
    std::string m_url;
    std::map<std::string, std::string> m_headers;
    HttpMethod m_method;
    int m_timeout;
};
}
}
#endif // INF_DS_BOSS_SDK_C_REQUEST_HTTP_REQUEST_H_
