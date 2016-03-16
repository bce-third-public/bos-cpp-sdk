#include "bos/model/response/get_object_response.h"
namespace bce {
namespace bos {
GetObjectResponse::GetObjectResponse(std::string *buffer) {
    m_owner_of_out = true;
    m_out = new StringOutputStream(buffer);
    SetOutputStream(m_out);
}

GetObjectResponse::GetObjectResponse(OutputStream *object_stream) {
    m_owner_of_out = false;
    m_out = object_stream;

    SetOutputStream(m_out);
}

int GetObjectResponse::GetObjectMetaData(std::map<std::string, std::string> *object_meta_data) const {
    for (std::map<std::string, std::string>::const_iterator it = GetResponseHeader().begin();
            it != GetResponseHeader().end(); it++) {
        if (IsVaildObjectMetaKey(it->first)) {
            object_meta_data->insert(std::pair<std::string, std::string>(it->first, it->second));
        }
    }

    return 0;
}

GetObjectResponse::~GetObjectResponse() {
    if (m_owner_of_out && m_out) {
        delete m_out;
        m_out = NULL;
    }
}

}
}
