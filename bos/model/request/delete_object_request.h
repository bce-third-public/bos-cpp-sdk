/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file delete_object_request.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/16 11:14:31
 * @brief 
 *  
 **/

#ifndef  __DELETE_OBJECT_REQUEST_H_
#define  __DELETE_OBJECT_REQUEST_H_

#include <sstream>

#include "bos/model/request/object_request.h"
#include "bos/model/request/bos_constraint.h"

namespace bce {
namespace bos {
class DeleteObjectRequest : public ObjectRequest {
public:
    DeleteObjectRequest(const std::string &bucket_name, const std::string &object_name);

    virtual ~DeleteObjectRequest() {
    }
};
}
}



















#endif  //__DELETE_OBJECT_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
