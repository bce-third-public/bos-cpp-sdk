/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_objects_response.cpp
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/22 11:18:23
 * @brief 
 *  
 **/
#include "bos/model/response/list_objects_response.h"
#include "json/json.h"
#include "util/exception.h"
#include <vector>
#include <string>
namespace bce {
namespace bos {
ListObjectsResponse::~ListObjectsResponse(){
    if(m_str_outputStream) {
        delete m_str_outputStream;
        m_str_outputStream = NULL;
    }

    if(m_buffer) {
        delete m_buffer;
        m_buffer = NULL;
    }
}
    
int ListObjectsResponse::ParseCommandSpecificResponse(){
    Json::Reader reader;
    Json::Value value;
        
    Log::PrintLog(DEBUG, TRACE, "response body , " + *m_buffer); 
    if(!reader.parse(*m_buffer, value)) {
		throw BosServiceException("Parse Response Fail");
    }
    if(value.type() != Json::objectValue) {
		throw BosServiceException("Parse Response type Fail");
    }
    
    if(!value["name"].isNull()){
        m_name = value["name"].asString();
    } else {
        Log::PrintLog(INFO, TRACE, "response body does not have name!"); 
    }
    
    if(!value["prefix"].isNull()){
        m_prefix = value["prefix"].asString();
        
    } else {
        Log::PrintLog(INFO, TRACE, "response body does not have prefix!"); 
    }
        
    if(!value["delimiter"].isNull()){
        m_delimiter = value["delimiter"].asString();
    } else {
        Log::PrintLog(INFO, TRACE, "response body does not have delimiter!"); 
    }
        
    if(!value["marker"].isNull()){
        m_marker = value["marker"].asString();
    } else {
        Log::PrintLog(INFO, TRACE, "response body does not have marker!"); 
    }

    if(!value["maxKeys"].isNull()){
        m_maxKeys = value["maxKeys"].asInt();
    } else {
        Log::PrintLog(INFO, TRACE, "response body does not have maxKeys!"); 
    }

    if(!value["isTruncated"].isNull()){
        m_isTruncated = value["isTruncated"].asBool();
    } else {
        Log::PrintLog(INFO, TRACE, "response body does not have isTruncated!"); 
    }

    if (m_isTruncated && !value["nextMarker"].isNull()) {
        m_nextMarker = value["nextMarker"].asString();
    }

    /*
    if(!value["commonPrefixes"].isNull()){
        Json::Value prefixes = value["commonPrefixes"];
        for(unsigned int i = 0; i < prefixes.size(); i++){
            m_commonPrefixes.push_back( prefixes[i].asString() );
        }
    } else {
        Log::PrintLog(INFO, TRACE, "response body does not have commonPrefixes!"); 
    }
    */

    if(!value["contents"].isNull()){
        Json::Value content = value["contents"];
        for(unsigned int i = 0; i < content.size(); i++){
            Content objectContent;
            Json::Value temp = content[i];
            objectContent.key = temp["key"].asString();
            objectContent.lastModified = temp["lastModified"].asString();
            objectContent.eTag = temp["eTag"].asString();
            objectContent.size = temp["Size"].asString();
            Json::Value owner = temp["owner"];
            objectContent.ownerId = owner["id"].asString();
            objectContent.ownerDisplayName = owner["displayName"].asString();
            m_contents.push_back(objectContent);
        }
    } else {
        Log::PrintLog(INFO, TRACE, "response body does not have contents"); 
    }
    return 0;
}


}
}

















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
