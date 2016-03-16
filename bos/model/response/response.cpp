#include "bos/model/response/response.h"

#include "json/json.h"
#include "util/exception.h"
#include "util/memory_stream.h"

namespace bce {
namespace bos {
int BosResponse::ParseResponse() {
    int http_code = m_http_response.GetHttpCode();

    if (http_code < 200 || http_code >= 300) {
        return SetError(m_http_response.GetErrorMessage());
    }

    return ParseCommandSpecificResponse();
}


int BosResponse::SetError(const std::string &error_msg) {
    Json::Reader reader;
    Json::Value value;

    if (!reader.parse(error_msg, value)) {
        m_error.SetMessage(error_msg + " should be a json");
        return 0;
    }

    if (value.type() != Json::objectValue) {
        m_error.SetMessage(error_msg + " format error");
        return 0;
    }

    std::string code_str;
    if (GetStringFromJsonValue(value["code"], &code_str)) {
        m_error.SetMessage(error_msg + " no code statement");
        return 0;
    }

    m_error.SetServiceErrorCode(code_str);
    std::string message = "";
    if (GetStringFromJsonValue(value["message"], &message)) {
        m_error.SetMessage(error_msg + " no message statement");
        return 0;
    }

    m_error.SetMessage(message);

    std::string request_id;;
    if (GetStringFromJsonValue(value["requestId"], &request_id)) {
        m_error.SetMessage(error_msg + " no requestId statement");
        return 0;
    }

    m_error.SetRequestId(request_id);
    throw BosServiceException("");

    return 0;
}

int BosResponse::GetStringFromJsonValue(const Json::Value &val, std::string *str) const {
    if(val.isNull()) {
    	return -1;
    }
    if (val.type() != Json::stringValue) {
        return -1;
    }

    str->assign(val.asString());
    return 0;
}

}
}
