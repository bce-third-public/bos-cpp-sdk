/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_multipart_uploads_request.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/21 09:48:34
 * @brief 
 *  
 **/




#ifndef  __LIST_MULTIPART_UPLOADS_REQUEST_H_
#define  __LIST_MULTIPART_UPLOADS_REQUEST_H_


#include <sstream>
#include "bos/model/request/bucket_request.h"
namespace bce {
namespace bos {
class ListMultipartUploadsRequest : public BucketRequest {
public:
	ListMultipartUploadsRequest(const std::string &bucket_name) :
		BucketRequest(bucket_name ,kHttpGet) {
			SetQueryString("uploads","");
	}

	virtual ~ListMultipartUploadsRequest();

	int AddDelimiter(const std::string &delimiter) {
		SetQueryString("delimiter",delimiter);
		return 0;
	}

	int AddKeyMarker(const std::string &key_marker) {
		SetQueryString("keyMarker",key_marker);
		return 0;
	}

	int AddMaxUploads(int max_uploads) {
        if(max_uploads < 1 || max_uploads > 1000) {
            Log::PrintLog(ERROR, TRACE, "add max uploads fail!");
            return kBosIllegalArgument;
        }
        std::stringstream ss;
        ss << max_uploads;
		SetQueryString("maxUploads", ss.str());
		return 0;
	}

	int AddPrefix(const std::string &prefix) {
		SetQueryString("prefix", prefix);
		return 0;
	}

};
}
}














#endif  //__LIST_MULTIPART_UPLOADS_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
