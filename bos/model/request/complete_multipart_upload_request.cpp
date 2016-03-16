/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file complete_multipart_upload_request.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/21 09:45:37
 * @brief 
 *  
 **/
#include<iostream>
#include <sstream>
#include "bos/model/request/complete_multipart_upload_request.h"
#include "json/json.h"

namespace bce {
namespace bos {
int CompleteMultipartUploadRequest::BuildCommandSpecific(HttpRequest *request) {
    Json::Value value;
    std::vector<Part>::iterator it;
    for(it = m_parts.begin(); it != m_parts.end(); it++) {
        Json::Value tmp;
        tmp["partNumber"] = Json::Value(it->m_part_number);
        tmp["eTag"] = Json::Value(it->m_etag); 
        value["parts"].append(tmp);
    }
    Json::FastWriter fast_writer;
    m_content = new std::string;
    m_content->assign(fast_writer.write(value));

    m_content->erase(m_content->end()-1, m_content->end());   //erase the end of \n for mock

    m_content_stream = new MemoryInputStream(m_content->data(), m_content->size());

    
    Log::PrintLog(DEBUG, TRACE, "request body , " + (*m_content));
    
    SetInputStream(m_content_stream);

    std::stringstream ss;
    ss << (m_content_stream->GetSize() - m_content_stream->GetPos());
    SetRequestHeader("Content-Type","text/plain"); 
    SetRequestHeader("Content-Length",ss.str());
    return 0;
}
}
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
