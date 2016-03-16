/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file complete_multipart_upload_response.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/21 09:53:54
 * @brief 
 *  
 **/




#ifndef  __COMPLETE_MULTIPART_UPLOAD_RESPONSE_H_
#define  __COMPLETE_MULTIPART_UPLOAD_RESPONSE_H_


#include <sstream>
#include "bos/model/response/response.h"
#include "util/memory_stream.h"

namespace bce {
namespace bos {
class CompleteMultipartUploadResponse : public BosResponse {
public:
	CompleteMultipartUploadResponse() {
        m_content = new std::string;
		m_content_stream = new StringOutputStream(m_content);
		SetOutputStream(m_content_stream);
	}

	virtual ~CompleteMultipartUploadResponse() {
		delete m_content_stream;
        delete m_content;
	}

	int GetLocation(std::string *location) {
		location->assign(m_location);
		return 0;
	}

	int GetBucket(std::string *bucket_name) {
		bucket_name->assign(m_bucket);
		return 0;
	}

	int GetKey(std::string *key) {
		key->assign(m_key);
		return 0;
	}

    int GetETag(std::string *etag) {
		etag->assign(m_etag);
		return 0;
	}

protected:
	int ParseCommandSpecificResponse();

private:
	std::string *m_content;
	OutputStream *m_content_stream;
	std::string m_location;
	std::string m_bucket;
	std::string m_key;
	std::string m_etag;
};
}
}














#endif  //__COMPLETE_MULTIPART_UPLOAD_RESPONSE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
