/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_multipart_uploads_response.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/21 10:42:07
 * @brief 
 *  
 **/
#include "bos/model/response/list_multipart_uploads_response.h"
#include "json/json.h"
#include "util/exception.h"

namespace bce {
namespace bos {
int ListMultipartUploadsResponse::ParseCommandSpecificResponse() {
    Json::Reader reader;
    Json::Value value;

    Log::PrintLog(DEBUG, TRACE, "response body , " + *m_content); 
    
    if(!reader.parse(*m_content, value)) {
		throw BosServiceException("parse response body  error!");
    }

    if(value.type() != Json::objectValue) {    
		throw BosServiceException("parse response body type error");
    }

    if(GetStringFromJsonValue(value["bucket"], &m_bucket)) {            
		throw BosServiceException("parse bucket error!");
    }
    
    int ret ; 
    ret = GetStringFromJsonValue(value["keyMarker"], &m_key_marker);
    if(ret) {
        Log::PrintLog(INFO, TRACE, "response body does not have keyMarker"); 
    }
    ret = GetStringFromJsonValue(value["nextKeyMarker"], &m_next_key_marker);
    if(ret) {
        Log::PrintLog(INFO, TRACE, "response body does not have nextKeyMarker"); 
    }

    ret = GetStringFromJsonValue(value["maxUploads"], &m_max_uploads);

    if(ret) {
        Log::PrintLog(INFO, TRACE, "response body does not have maxUploads"); 
    }
    ret = GetStringFromJsonValue(value["isTruncated"], &m_is_truncated);

    if(ret) {
        Log::PrintLog(INFO, TRACE, "response body does not have isTruncated"); 
    }
    ret = GetStringFromJsonValue(value["commonPrefixes"], &m_common_prefixes);

    if(ret) {
        Log::PrintLog(INFO, TRACE, "response body does not have commonPrefixes"); 
    }
    ret = GetStringFromJsonValue(value["prefix"], &m_prefix);

    if(ret) {
        Log::PrintLog(INFO, TRACE, "response body does not have prefix"); 
    }
    Json::Value array = value["uploads"];
    if(array.size() == 0) {
        Log::PrintLog(DEBUG, TRACE, "response body does not have uploads"); 
    }
    for(unsigned int i = 0; i < array.size(); i++) {
        Upload tmp;

        if(array[i]["key"].isNull()) { 
		    throw BosServiceException("parse uploads_key error");
        }
        tmp.m_key = array[i]["key"].asString();

        if(array[i]["uploadId"].isNull()) { 
		    throw BosServiceException("parse uploads_upload_id error");
        }
        tmp.m_upload_id = array[i]["uploadId"].asString();

        if(array[i]["owner"]["id"].isNull()) {  
		    throw BosServiceException("parse uploads_owner_id error");
        }
        tmp.m_owner.m_id = array[i]["owner"]["id"].asString();

        if(array[i]["owner"]["displayName"].isNull()) {
		    throw BosServiceException("parse uploads_owner_display_name error");
        }
        tmp.m_owner.m_display_name = array[i]["owner"]["displayName"].asString();

        if(array[i]["initiated"].isNull()) {
		    throw BosServiceException("parse uploads_initiated error");
        }
        tmp.m_initiated = array[i]["initiated"].asString();


        m_uploads.push_back(tmp);
    }
    return 0;

    
}
}
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
