/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file init_multi_upload.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/18 11:07:55
 * @brief 
 *  
 **/



#ifndef  __INIT_MULTI_UPLOAD_H_
#define  __INIT_MULTI_UPLOAD_H_

#include <sstream>
#include "util/memory_stream.h"
#include "bos/model/request/object_request.h"

namespace bce {
namespace bos {


class InitMultiUploadRequest : public ObjectRequest {

public:
    InitMultiUploadRequest(const std::string &bucket_name,const std::string &object_name) :
        ObjectRequest(bucket_name,object_name,kHttpPost) {
        SetQueryString("uploads","");
        SetRequestHeader("Content-Length","0");
        SetRequestHeader("Content-Type","text/plain");
    }

    virtual ~InitMultiUploadRequest() ;
};

}
}





#endif  //__INIT_MULTI_UPLOAD_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
