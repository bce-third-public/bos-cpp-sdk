/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_bucket_response.cpp
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/10 13:55:18
 * @brief 
 *  
 **/
#include "bos/model/response/list_bucket_response.h"
#include "json/json.h"
#include "util/exception.h"
namespace bce{
namespace bos{
ListBucketResponse::~ListBucketResponse(){
    if(m_str_outputStream){
        delete m_str_outputStream;
        m_str_outputStream = NULL;
    }

    if(m_buffer) {
        delete m_buffer;
        m_buffer = NULL;
    }
}
int ListBucketResponse::ParseCommandSpecificResponse(){
    Json::Reader reader;
    Json::Value value;

    Log::PrintLog(DEBUG, TRACE, "response body , " + *m_buffer); 
    if(!reader.parse(*m_buffer, value)) {
        throw BosServiceException("Parse Response Fail");
    }
    if(value.type() != Json::objectValue) {
		throw BosServiceException("Parse Response type Fail");
    }
    if(value["owner"].isNull()){
		throw BosServiceException("Parse Response owner Fail");
    }
    Json::Value owner = value["owner"];
    if(owner["id"].isNull()){
		throw BosServiceException("Parse Response id Fail");
    }
    m_owner_id = owner["id"].asString();
    if(owner["displayName"].isNull()){
	    throw BosServiceException("Parse Response display name Fail");
    }
    m_owner_displayName = owner["displayName"].asString();
        
    if(!value["buckets"].isNull()){
        Json::Value arr = value["buckets"];
        for(unsigned int i = 0; i < arr.size(); i++){
            Json::Value bucket = arr[i];
            BucketInfo bucket_info;
            
            bucket_info.bucket_name = bucket["name"].asString();
            bucket_info.creationDate = bucket["creationDate"].asString();
            m_buckets.push_back(bucket_info);
        }
    } else {
        Log::PrintLog(INFO, TRACE, "no bucket ! " ); 
    }
    return 0;
}
    

}
}




















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
