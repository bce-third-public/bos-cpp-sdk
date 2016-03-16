/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file complete_multipart_upload_request.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/21 09:41:18
 * @brief 
 *  
 **/




#ifndef  __COMPLETE_MULTIPART_UPLOAD_REQUEST_H_
#define  __COMPLETE_MULTIPART_UPLOAD_REQUEST_H_


#include <sstream>
#include <vector>
#include "bos/model/request/object_request.h"
#include "util/memory_stream.h"
#include "util/string_util.h"
#include "util/encrypt_util.h"
#include "zlib.h"

namespace bce {
namespace bos {

struct Part {
    int m_part_number;
    std::string m_etag;
};

class CompleteMultipartUploadRequest : public ObjectRequest {
public:
	CompleteMultipartUploadRequest(const std::string &bucket_name, const std::string &object_name, const std::string &upload_id) :
		ObjectRequest(bucket_name, object_name, kHttpPost) {
			SetQueryString("uploadId", upload_id);
            m_content_stream = NULL;
            m_content = NULL;
	}

	virtual ~CompleteMultipartUploadRequest() {
        if(m_content_stream) {
		    delete m_content_stream;
	   	    m_content_stream = NULL;
        }

        if(m_content) {
            delete  m_content;
            m_content = NULL;
        }
	}

	int AddPart(int number, const std::string &etag) {
        if(number < 1 || number > 10000) {

            Log::PrintLog(ERROR, TRACE, "add part fail!\n");
            return kBosIllegalArgument;
        }
		Part m_part;
        //std::stringstream ss;
        //ss << number;
        //ss >> m_part.m_part_number;
        m_part.m_part_number = number;
		m_part.m_etag = etag;
		m_parts.push_back(m_part);
        return 0;
	}

    int AddUserMetaData(const std::string &key, const std::string &value) {
        if(IsVaildObjectMetaKey(key)) {
            SetRequestHeader(key, value);
            return 0;
        }
        Log::PrintLog(ERROR, TRACE, "add user meta data fail!\n");
        return kBosIllegalArgument;
    }

protected:
	int BuildCommandSpecific(HttpRequest *request);

private:
	std::vector<Part> m_parts;
	std::string *m_content;
    InputStream *m_content_stream;

};
}
}














#endif  //__COMPLETE_MULTIPART_UPLOAD_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
