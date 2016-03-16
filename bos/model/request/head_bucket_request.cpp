/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file head_bucket_request.cpp
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/17 15:32:23
 * @brief 
 *  
 **/

#include "bos/model/request/head_bucket_request.h"

#include <sstream>
namespace bce{
namespace bos{

HeadBucketRequest::HeadBucketRequest(const std::string &bucket_name) :
    BucketRequest(bucket_name, kHttpHead) {
}
}
}




















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
