/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file delete_object_response.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/16 12:45:42
 * @brief 
 *  
 **/



#ifndef  __DELETE_OBJECT_RESPONSE_H_
#define  __DELETE_OBJECT_RESPONSE_H_



#include <string>
#include "bos/model/response/response.h"
#include "util/memory_stream.h"

namespace bce {
namespace bos {
class DeleteObjectResponse : public BosResponse {
public:
    DeleteObjectResponse() {
    }

    virtual ~DeleteObjectResponse() {
    }

    int GetVersion(std::string *version) const ;
    
};
}
}












#endif  //__DELETE_OBJECT_RESPONSE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
