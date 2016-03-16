#ifndef INF_DS_BOSS_SDK_C_API_RESPONSE_H_
#define INF_DS_BOSS_SDK_C_API_RESPONSE_H_

#include <stdint.h>

#include <map>
#include <string>
#include <vector>
#include "bos/model/response/http_response.h"


namespace Json {
class Value;
}
namespace bce {
namespace bos {
class StringOutputStream;
class OutputStream;
class BosError {
public:
    void SetMessage(const std::string &message) {
        m_message = message;
    }

    const std::string &GetMessage() const {
        return m_message;
    }

    const std::string &GetServiceErrorCode() const {
        return m_service_error_code;
    }

    void SetServiceErrorCode(const std::string &service_error_code) {
        m_service_error_code = service_error_code;
    }

    void SetRequestId(const std::string &request_id) {
        m_request_id = request_id;
    }

    std::string GetRequestId() const {
        return m_request_id;
    }

private:
    std::string m_message;
    std::string m_service_error_code;
    std::string m_request_id;
};

class BosResponse {
public:
    BosResponse() {
       //  m_result_out_stream = NULL;
    }

    virtual ~BosResponse() {
    }

    void SetRequestId(const std::string &request_id) {
        m_request_id = request_id;
    }

    std::string GetRequestId() const {
        if (m_request_id != "") {
            return m_request_id;
        }

        return m_error.GetRequestId();
    }

    int GetResponseHeader(const std::string &key, std::string *data) const {
        return m_http_response.GetResponseHeader(key, data);
    }

    void SetMessage(const std::string &message) {
        m_error.SetMessage(message);
    }

    std::string GetMessage() const {
        return m_error.GetMessage();
    }

    std::string GetErrorCode() const {
        return m_error.GetServiceErrorCode();
    }

    /*
    void AddResponseHeader(const std::string &key, const std::string &value) {
        m_response_headers[key] = value;
    }

    int GetResponseHeader(const std::string &key, std::string *value) const {
        std::map<std::string, std::string>::const_iterator it = m_response_headers.find(key);
        if (it == m_response_headers.end()) {
            return -1;
        }

        value->assign(it->second);
        return 0;
    }
    */

    /*
    OutputStream *GetOutputStream() {
        return m_result_out_stream;
    }

    void SetOutputStream(OutputStream *out) {
        m_result_out_stream = out;
    }
    */

    void SetOutputStream(OutputStream *output_stream) {
        m_http_response.SetOutputStream(output_stream);
    }

    int ParseResponse();

    HttpResponse *GetHttpResponse() {
        return &m_http_response;
    }

protected:
    virtual int ParseCommandSpecificResponse() {
        return 0;
    }

    const std::map<std::string, std::string> &GetResponseHeader() const {
        return m_http_response.GetResponseHeader();
    }
        
    int GetStringFromJsonValue(const Json::Value &val, std::string *str) const ;



private:
    std::string m_request_id;
    BosError m_error;

    // OutputStream *m_result_out_stream;
    HttpResponse m_http_response;

    int SetError(const std::string &error_msg) ;

};
}
}
#endif // INF_DS_BOSS_SDK_C_API_RESPONSE_H_
