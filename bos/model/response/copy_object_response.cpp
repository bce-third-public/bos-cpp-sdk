/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file response/copy_object_response.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/17 14:24:55
 * @brief 
 *  
 **/

#include "bos/model/response/copy_object_response.h"
#include "json/json.h"
#include "util/exception.h"
namespace bce {
namespace bos {

int CopyObjectResponse::ParseCommandSpecificResponse() {
    Json::Reader reader;
    Json::Value value;

    Log::PrintLog(DEBUG, TRACE, "response body " + *m_content); 
    if(!reader.parse(*m_content, value)) {
		throw BosServiceException("response parse body error!");
    }
    if(value.type() != Json::objectValue) {
		throw BosServiceException("response parse body type error!");
    }
    
    if(GetStringFromJsonValue(value["eTag"],&m_etag)) {
		throw BosServiceException("response parse eTag error");
    }
    
    if(GetStringFromJsonValue(value["lastModified"],&m_last_modified)) {
		throw BosServiceException("response parse lastModified error!");
    }
    
    return 0;
    

}
}
}



















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
