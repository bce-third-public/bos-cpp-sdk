/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file complete_multipart_upload_response.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/21 09:54:50
 * @brief 
 *  
 **/


#include "bos/model/response/complete_multipart_upload_response.h"
#include "json/json.h"
#include "util/exception.h"
namespace bce {
namespace bos {
int CompleteMultipartUploadResponse::ParseCommandSpecificResponse() {
	Json::Reader reader;
	Json::Value value;
    
    Log::PrintLog(DEBUG, TRACE, "response body : " + *m_content); 
	if(!reader.parse(*m_content, value)) {
        throw BosServiceException("response parse body error!");
	}
	if(value.type() != Json::objectValue) {
        throw BosServiceException("response parse body type error!");
	}
	
	if(GetStringFromJsonValue(value["location"], &m_location)) {	
		throw BosServiceException("response parse location error!");
	}
	
	if(GetStringFromJsonValue(value["bucket"], &m_bucket)) {	
		throw BosServiceException("response parse bucket error!");
	}
	

	if(GetStringFromJsonValue(value["key"], &m_key)) {
		throw BosServiceException("response parse key error!");
	}


	if(GetStringFromJsonValue(value["eTag"], &m_etag)) {
		throw BosServiceException("response parse eTag error!");
	}

	return 0;
}
}
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
