/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file head_object_request.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/16 13:03:53
 * @brief 
 *  
 **/

#include "bos/model/request/head_object_request.h"

#include <sstream>

namespace bce {
namespace bos {
HeadObjectRequest::HeadObjectRequest(const std::string &bucket_name,const std::string &object_name) :
    ObjectRequest(bucket_name, object_name, kHttpHead) {
}

}
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
