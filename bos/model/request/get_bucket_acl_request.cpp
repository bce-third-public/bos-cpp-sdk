/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file get_bucket_acl_request.cpp
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/18 15:30:43
 * @brief 
 *  
 **/
#include "bos/model/request/get_bucket_acl_request.h"
namespace bce{
namespace bos{

GetBucketAclRequest::GetBucketAclRequest(const std::string &bucket_name) :  
    BucketRequest(bucket_name, kHttpGet){
}

int GetBucketAclRequest::BuildCommandSpecific(HttpRequest *request){
    SetQueryString("acl", "");
    return 0;
}

}
}

















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
