#ifndef INF_DS_BOSS_SDK_CPP_RESPONSE_GET_OBJECT_RESPONSE_H_
#define INF_DS_BOSS_SDK_CPP_RESPONSE_GET_OBJECT_RESPONSE_H_
#include "bos/model/response/response.h"
#include "util/memory_stream.h"
namespace bce {
namespace bos {
class GetObjectResponse : public BosResponse {
public:
    GetObjectResponse(std::string *buffer);

    GetObjectResponse(OutputStream *object_stream);

    virtual ~GetObjectResponse();

    int GetObjectMetaData(std::map<std::string, std::string> *object_meta_data) const;

    int GetETag(std::string *etag) const {
        return GetResponseHeader("ETag", etag);
    }

    int GetVersion(std::string *version) const {
        return GetResponseHeader("x-bce-version", version);
    }

    int GetLength(uint64_t *length) const {
    	std::string tmp_len;
	    if(GetResponseHeader("Content-Length", &tmp_len))
	        return -1;
	    std::stringstream ss;
	    ss << tmp_len;
	    ss >> (*length);
	    return 0;

    }

    int GetRange(std::string *range) const {
    	return GetResponseHeader("Content-Range", range);
    }

private:
    OutputStream *m_out;
    bool m_owner_of_out;

};
}
}
#endif // INF_DS_BOSS_SDK_CPP_RESPONSE_GET_OBJECT_RESPONSE_H_
