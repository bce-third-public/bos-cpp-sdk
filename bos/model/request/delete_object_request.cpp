/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file delete_object_request.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/16 11:21:34
 * @brief 
 *  
 **/


#include "bos/model/request/delete_object_request.h"
#include <sstream>

namespace bce {
namespace bos {

DeleteObjectRequest::DeleteObjectRequest(const std::string &bucket_name, const std::string &object_name) :
    ObjectRequest(bucket_name, object_name, kHttpDelete) {
}

}
}






















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
