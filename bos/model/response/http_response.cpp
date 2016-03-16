#include "bos/model/response/http_response.h"
#include "util/exception.h"
#include "util/memory_stream.h"
#include "util/util.h"

namespace bce {
namespace bos {
int HttpResponse::ParseStatusLine(const std::string &status_line) {
    std::vector<std::string> items;
    Util::SpiltString(status_line, std::string(" "), 3, &items);
    if (items.size() != 3u) {
        std::stringstream ss;
        ss << "status_line format error, status_line:" << status_line;
        throw BosServiceException(ss.str());
    }

    m_http_version = items[0];
    m_http_code = atoi(items[1].c_str());
    m_reason_phrase = items[2];
    
    Log::PrintLog(DEBUG, TRACE, "Http version : " + m_http_version); 
    Log::PrintLog(DEBUG, TRACE, "Http code : " + items[1]); 
    Log::PrintLog(DEBUG, TRACE, "Reason phrase : " + m_reason_phrase); 
    return 0;
}

int HttpResponse::ParseHeaderLine(const std::string &header_line, std::string *key, std::string *value) {
    std::vector<std::string> items;
    Util::SpiltString(header_line, std::string(":"), 2, &items);
    if (items.size() != 2u) {
        std::stringstream ss;
        //ss << "parse_header_line error, header_line:" << header_line;
        //throw BosServiceException(ss.str());
        return 0;
    
    }

    key->assign(Util::Trim(items[0]));
    value->assign(Util::Trim(items[1]));

    return 0;
}

int HttpResponse::AddResponseLine(const std::string &line) {
    printf("http_response: header:%s", line.c_str());
    if (m_has_recv_status_line) {
        std::string key;
        std::string value;

        int ret = ParseHeaderLine(line, &key, &value);
        if (ret != 0) {
            return ret;
        }

        if (strncmp("Content-Length", key.c_str(), key.size()) == 0 && m_body_stream != NULL) {
            long long content_length = strtoll(value.c_str(), NULL, 10);
            ret = m_body_stream->Reserve(content_length);
            if (ret != 0) {
                throw BosClientException(m_body_stream->GetErrorDescription(ret));
            }
        }

        m_response_headers[key] = value;

        Log::PrintLog(DEBUG, TRACE, "add response header , " + key + " : " + value); 
        return 0;
    } else {
        m_has_recv_status_line = true;
        return ParseStatusLine(line);
    }
}

int HttpResponse::WriteBody(void *ptr, size_t size) {
    if (m_http_code < 200 || m_http_code >= 300) {
        m_error_stream << std::string(reinterpret_cast<char *>(ptr), size);
        return size;
    }

    return m_body_stream->Write(reinterpret_cast<char *>(ptr), size);
}

int HttpResponse::GetResponseHeader(const std::string &key, std::string *data) const {
    std::map<std::string, std::string>::const_iterator it = m_response_headers.find(key);
    if (it == m_response_headers.end()) {
        Log::PrintLog(ERROR, TRACE, (std::string("get response header fail ! : ") + key).c_str()); 
        return -1;
    }

    data->assign(it->second);

    return 0;
}
}
}
