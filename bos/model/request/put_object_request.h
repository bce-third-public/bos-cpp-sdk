#ifndef INF_DS_BOSS_SDK_C_REQUEST_PUT_OBJECT_REQUEST_H_
#define INF_DS_BOSS_SDK_C_REQUEST_PUT_OBJECT_REQUEST_H_
#include <sstream>

#include "bos/model/request/object_request.h"
#include "bos/model/request/bos_constraint.h"

namespace bce {
namespace bos {
class InputStream;

class PutObjectRequest : public ObjectRequest {
public:
    PutObjectRequest(const std::string &bucket_name, const std::string &object_name,
            const std::string &data);

    PutObjectRequest(const std::string &bucket_name, const std::string &object_name,
            InputStream *stream);

    virtual ~PutObjectRequest();

    virtual int CalculateObjectFinger(InputStream *stream, std::string *md5, std::string *sha256) const ;

    int AddUserMetaData(const std::string &key, const std::string &value);

protected:
    int BuildCommandSpecific(HttpRequest *request);

private:
    InputStream *m_object_content_stream;
    bool m_owner_of_input;

};
}
}
#endif // INF_DS_BOSS_SDK_C_REQUEST_PUT_OBJECT_REQUEST_H_
