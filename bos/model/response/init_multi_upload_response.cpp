/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file init_multi_upload_response.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/18 12:07:12
 * @brief 
 *  
 **/

#include "bos/model/response/init_multi_upload_response.h"
#include "util/exception.h"
#include "json/json.h"
#include <iostream>
namespace bce {
namespace bos {
int InitMultiUploadResponse::ParseCommandSpecificResponse() {

    Json::Reader reader;
    Json::Value value;
    
    Log::PrintLog(DEBUG, TRACE, "response body , " + *m_content); 
    if(!reader.parse(*m_content, value)) {
        throw BosServiceException("parse body error");
    }
    if(value.type() != Json::objectValue) { 
        throw BosServiceException("parse body type error");
    }

    if(GetStringFromJsonValue(value["bucket"], &m_bucket)) {
        throw BosServiceException("parse bucket error");
    }
    if(GetStringFromJsonValue(value["key"], &m_key)) {
        
        throw BosServiceException("parse key error");
    }
    if(GetStringFromJsonValue(value["uploadId"], &m_upload_id)) { 
        throw BosServiceException("parse uploadId error");
    }
    return 0;
}
}
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
