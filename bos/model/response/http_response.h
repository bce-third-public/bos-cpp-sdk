#ifndef INF_DS_BOSS_SDK_CPP_RESPONSE_HTTP_RESPONSE_H_
#define INF_DS_BOSS_SDK_CPP_RESPONSE_HTTP_RESPONSE_H_
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "util/common_def.h"
#include "bos/api.h"
#include "util/bos_log.h"

namespace bce {
namespace bos {
class OutputStream;
class HttpResponse {
public:
    HttpResponse() {
        m_body_stream = NULL;
        m_has_recv_status_line = false;
    }

    GENERATE_PTR_FIELD_GETTER_AND_SETTER(bce::bos::OutputStream, BodyOutputStream, body_stream)
    GENERATE_FIELD_GETTER_AND_SETTER(std::string, HttpVersion, http_version)
    GENERATE_FIELD_GETTER_AND_SETTER(int, HttpCode, http_code)
    GENERATE_FIELD_GETTER_AND_SETTER(std::string, ReasonPhrase, reason_phrase);

    int AddResponseLine(const std::string &line);

    int WriteBody(void *ptr, size_t size);

    std::string GetErrorMessage() const {
        return m_error_stream.str();
    }

    int GetResponseHeader(const std::string &key, std::string *data) const;
    void SetOutputStream(OutputStream *output_stream) {
        m_body_stream = output_stream;
    }

    const std::map<std::string, std::string> &GetResponseHeader() const {
        return m_response_headers;
    }

private:
    bce::bos::OutputStream *m_body_stream;
    std::stringstream m_error_stream;

    int ParseStatusLine(const std::string &status_line);
    int ParseHeaderLine(const std::string &header_line, std::string *key, std::string *value);

    std::string m_http_version;
    int m_http_code;
    std::string m_reason_phrase;
    std::map<std::string, std::string> m_response_headers;
    bool m_has_recv_status_line;
};
}
}

#endif // INF_DS_BOSS_SDK_CPP_RESPONSE_HTTP_RESPONSE_H_
