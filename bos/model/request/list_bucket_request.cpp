/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_bucket_request.cpp
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/09 19:20:43
 * @brief 
 *  
 **/
#include "bos/model/request/list_bucket_request.h"
#include "openssl/md5.h"
#include "openssl/sha.h"
#include "zlib.h"
#include "util/memory_stream.h"
#include "util/encrypt_util.h"
namespace bce {
namespace bos {
ListBucketRequest::ListBucketRequest() :  BosRequest(kHttpGet){      
}

ListBucketRequest::~ListBucketRequest(){
}
}
}



















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
