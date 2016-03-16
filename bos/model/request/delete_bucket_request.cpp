/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file delete_bucket_request.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/15 10:10:57
 * @brief 
 *  
 **/

#include "bos/model/request/delete_bucket_request.h"
#include <string>
#include "bos/model/request/http_request.h"
namespace bce {
namespace bos {
DeleteBucketRequest::DeleteBucketRequest(const std::string &bucket_name) :
    BucketRequest(bucket_name,kHttpDelete) {
}

DeleteBucketRequest::~DeleteBucketRequest() {}

}
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
