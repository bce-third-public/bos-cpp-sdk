/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file get_bucket_acl_response.cpp
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/21 14:22:11
 * @brief 
 *  
 **/
#include "bos/model/response/get_bucket_acl_response.h"
#include "json/json.h"
#include "util/exception.h"
#include <vector>
#include <string>
namespace bce {
namespace bos {
GetBucketAclResponse::~GetBucketAclResponse(){
    if(m_str_outputStream){
        delete m_str_outputStream;
        m_str_outputStream = NULL;
    }

    if(m_buffer) {
        delete m_buffer;
        m_buffer = NULL;
    }
}
int GetBucketAclResponse::ParseCommandSpecificResponse(){
    
    Json::Reader reader;
    Json::Value value;

    Log::PrintLog(DEBUG, TRACE, "response body : " + *m_buffer); 
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
		throw BosServiceException("Parse Response owner id Fail");
    }
    if(owner["displayName"].isNull()){
		throw BosServiceException("Parse Response owner displayName Fail");
    }
    m_id = owner["id"].asString();
    m_displayName = owner["displayName"].asString();
    
    if(!value["accessControlList"].isNull()){
        Json::Value arr = value["accessControlList"];
        for(unsigned int i = 0; i < arr.size(); i++){
            Json::Value accessControl = arr[i];
            Json::Value grantee = accessControl["grantee"];
            AccessControl ac;
            ac.displayName = grantee["displayName"].asString();
        //  ac.id = grantee["id"].asString();
            std::string str = "";
            GetStringFromJsonValue(grantee["id"], &str);
            ac.id = str;
            ac.permission = accessControl["permission"].asString();
            m_accessControlList.push_back(ac);
        }
    } else {
        Log::PrintLog(INFO, TRACE, "response body does not have accessControlList!"); 
    }
       
    return 0;
}

}
}



















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
