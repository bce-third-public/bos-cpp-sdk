/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_objects_request.cpp
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/22 15:47:18
 * @brief 
 *  
 **/


#include "bos/model/request/list_objects_request.h"
#include <sstream>
namespace bce {
namespace bos {
ListObjectsRequest::ListObjectsRequest(const std::string &bucket_name) :
        BucketRequest(bucket_name, kHttpGet){
}
}
}


















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
