/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file copy_object_request.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/16 13:22:27
 * @brief 
 *  
 **/
#include "bos/model/request/copy_object_request.h"
#include "util/memory_stream.h"
namespace bce {
namespace bos {


CopyObjectRequest::CopyObjectRequest(const std::string &bucket_name, const std::string &object_name, const std::string &source_bucket_name, const std::string &source_object_name) :
    ObjectRequest(bucket_name, object_name, kHttpPut) {
    m_source_bucket_name = source_bucket_name;
    m_source_object_name = source_object_name;

    Log::PrintLog(DEBUG, TRACE, "add source bucket name , " + source_bucket_name);
    Log::PrintLog(DEBUG, TRACE, "add source object name , " + source_object_name);

    std::stringstream ss;
    ss<<"/"<<source_bucket_name<<"/"<<source_object_name;
    SetRequestHeader("x-bce-copy-source",ss.str());
    SetRequestHeader("Content-Length","0");
    SetRequestHeader("Content-Type","text/plain"); 
}


int CopyObjectRequest::AddCopySourceIfMatch(const std::string &etag) {
    SetRequestHeader("x-bce-copy-source-if-match", etag);
    return 0;
}

int CopyObjectRequest::AddCopyMetaDataDirective(const std::string &directive) {
    if(directive == "replace" || directive == "copy") {
        SetRequestHeader("x-bce-copy-metadata-directive", directive);
        return 0;
    }

    Log::PrintLog(ERROR, TRACE, "add copy meta data directive fail!");
    return kBosIllegalArgument;

}
}
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
