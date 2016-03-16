/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file put_bucket_acl_request.cpp
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/18 14:05:06
 * @brief 
 *  
 */
#include "bos/model/request/put_bucket_acl_request.h"
namespace bce{
namespace bos{

PutBucketAclRequest::PutBucketAclRequest(const std::string &bucket_name, const std::string &aclString) : 
    BucketRequest(bucket_name, kHttpPut){
    m_acl = aclString;
}

int PutBucketAclRequest::BuildCommandSpecific(HttpRequest *request){
    SetQueryString("acl", "");
    SetRequestHeader("x-bce-acl", m_acl);    
    SetRequestHeader("Content-Length", "0");
    return 0;
}
}
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
