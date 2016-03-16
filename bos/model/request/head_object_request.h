/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file head_object_request.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/16 12:59:06
 * @brief 
 *  
 **/




#ifndef  __HEAD_OBJECT_REQUEST_H_
#define  __HEAD_OBJECT_REQUEST_H_

#include <sstream>
#include "bos/model/request/object_request.h"
namespace bce {
namespace bos {
class HeadObjectRequest : public ObjectRequest {

public:
    HeadObjectRequest(const std::string &bucket_name, const std::string &object_name);

    virtual ~HeadObjectRequest() {
    }
};
}
}














#endif  //__HEAD_OBJECT_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
