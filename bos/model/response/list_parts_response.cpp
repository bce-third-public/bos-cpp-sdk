/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_parts_response.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/21 12:44:46
 * @brief 
 *  
 **/

#include "bos/model/response/list_parts_response.h"
#include "json/json.h"
#include "util/exception.h"
#include <iostream>
namespace bce {
namespace bos {

int ListPartsResponse::ParseCommandSpecificResponse() {
    Json::Reader reader;
    Json::Value value;

    Log::PrintLog(DEBUG, TRACE, "response body ," + *m_content); 
    if(!reader.parse(*m_content, value)) {
		throw BosServiceException("parse response body fail!");
    }
    if(value.type() != Json::objectValue) {
		throw BosServiceException("parse response type error");
    }
    if(value["bucket"].isNull()) {
		throw BosServiceException("no bucket in response body");
    }
    m_bucket = value["bucket"].asString();
    
    if(value["key"].isNull()) { 
		throw BosServiceException("no key in response body");
    }
    m_key = value["key"].asString();

    if(value["uploadId"].isNull()) { 
		throw BosServiceException("no upload id in response body");
    }
    m_upload_id = value["uploadId"].asString();

    if(value["initiated"].isNull()) {
		throw BosServiceException("no initiated in response body");
    }
    m_initiated = value["initiated"].asString();
    
    if(value["owner"].isNull()) { 
		throw BosServiceException("no owner in response body");
    }

    if(value["owner"]["id"].isNull()) {
		throw BosServiceException("no owner id in response body");
    }
    m_owner.m_id = value["owner"]["id"].asString();

    if(value["owner"]["displayName"].isNull()) { 
		throw BosServiceException("no owner display name in response body");
    }
    m_owner.m_display_name = value["owner"]["displayName"].asString();

    if(!value["partNumberMarker"].isNull()) {
        Log::PrintLog(INFO, TRACE, "response body does not have partNumberMarker"); 
        m_part_number_marker = value["partNumberMarker"].asInt();
    }

    if(!value["nextPartNumberMarker"].isNull()) {
        Log::PrintLog(INFO, TRACE, "response body does not have nextPartNumberMarker"); 
        m_next_part_number_marker = value["nextPartNumberMarker"].asInt();
    }

    if(!value["maxParts"].isNull()) {
        Log::PrintLog(INFO, TRACE, "response body does not have maxParts"); 
        m_max_parts = value["maxParts"].asInt();
    }
    
    if(!value["isTruncated"].isNull()) {
        Log::PrintLog(INFO, TRACE, "response body does not have isTruncated!"); 
        m_is_truncated = value["isTruncated"].asString();
    }

    Json::Value array = value["parts"];
    if(array.size() == 0) {
        Log::PrintLog(INFO, TRACE, "response body does not have parts!"); 
    }
    for(unsigned int i = 0; i < array.size(); i++) {
        PartInList part;

        if(array[i]["partNumber"].isNull()) {
		    throw BosServiceException("no partNumber in response body");
        }
        part.m_part_number = array[i]["partNumber"].asInt();

        if(array[i]["lastModified"].isNull()) {
		    throw BosServiceException("no lastModified in response body");
        }
        part.m_last_modified = array[i]["lastModified"].asString();

        if(array[i]["eTag"].isNull()) { 
		    throw BosServiceException("no eTag in response body");
        }
        part.m_etag = array[i]["eTag"].asString();

        if(array[i]["size"].isNull()) {    
		    throw BosServiceException("no size in response body");
        }
        part.m_size = array[i]["size"].asString();

        m_parts.push_back(part);    
    }
    return 0;
}


}
}


















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
