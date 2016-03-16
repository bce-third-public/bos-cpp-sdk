/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file delete_object_response.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/16 12:50:30
 * @brief 
 *  
 **/

#include "bos/model/response/delete_object_response.h"

namespace bce {
namespace bos {
int DeleteObjectResponse::GetVersion(std::string *version) const {
    return GetResponseHeader("x-bce-version",version);
}

}
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
