/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_parts_request.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/21 09:52:07
 * @brief 
 *  
 **/




#ifndef  __LIST_PARTS_REQUEST_H_
#define  __LIST_PARTS_REQUEST_H_




#include <sstream>
#include "bos/model/request/object_request.h"

namespace bce {
namespace bos {
class ListPartsRequest : public ObjectRequest {
public:
	ListPartsRequest(const std::string &bucket_name, const std::string &object_name, const std::string &upload_id) :
		ObjectRequest(bucket_name, object_name, kHttpGet) {
			SetQueryString("uploadId",upload_id);
	}

    virtual ~ListPartsRequest();

	int AddMaxParts(int max_parts) {
        if(max_parts < 1 || max_parts > 1000) {
            Log::PrintLog(ERROR, TRACE, "add max parts fail!");
            return kBosIllegalArgument;
        }
        std::stringstream ss;
        ss << max_parts;
		SetQueryString("maxParts",ss.str());
		return 0;
	}

	int AddPartNumberMarker(const std::string &part_number_marker) {
        std::stringstream ss;
        ss << part_number_marker;
        int tmp;
        ss >> tmp; 
        if(tmp >= 10000 || tmp < 0 ) {
            Log::PrintLog(ERROR, TRACE, "add part number marker fail!");
            return kBosIllegalArgument;
        } 
		SetQueryString("partNumberMarker", part_number_marker);
		return 0;
	}

};
}
}












#endif  //__LIST_PARTS_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
