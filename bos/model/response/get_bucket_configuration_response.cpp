/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file get_bucket_configuration.cpp
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/16 14:11:41
 * @brief 
 *  
 **/
#include "bos/model/response/get_bucket_configuration_response.h"
#include "json/json.h"
#include "util/exception.h"
#include <string>
namespace bce {
namespace bos {
GetBucketConfigurationResponse::~GetBucketConfigurationResponse(){
    if(m_str_outputStream){
        delete m_str_outputStream;
        m_str_outputStream = NULL;
    }

   if(m_buffer) {
       delete m_buffer;
       m_buffer = NULL;
   } 
}

int GetBucketConfigurationResponse::ParseCommandSpecificResponse(){
    Json::Reader reader;
    Json::Value value;

    Log::PrintLog(DEBUG, TRACE, "response body , " + *m_buffer); 
    if(!reader.parse(*m_buffer, value)){
		throw BosServiceException("Parse Response Fail");
    }
    if( value.type() != Json::objectValue ){
		throw BosServiceException("Parse Response type Fail");
    }
    if(value["locationConstraint"].isNull()){
		throw BosServiceException("Parse Response locationConstraint Fail");
    }
    m_locationConstraint = value["locationConstraint"].asString();
    
    return 0;
}
}
}



















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
