/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file abort_multipart_upload_response.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/18 13:30:56
 * @brief 
 *  
 **/




#ifndef  __ABORT_MULTIPART_UPLOAD_RESPONSE_H_
#define  __ABORT_MULTIPART_UPLOAD_RESPONSE_H_

#include "bos/model/response/response.h"
//
namespace bce {
namespace bos {
class AbortMultipartUploadResponse : public BosResponse {
public:
    AbortMultipartUploadResponse();

    virtual ~AbortMultipartUploadResponse() {
    }
};
}
}














#endif  //__ABORT_MULTIPART_UPLOAD_RESPONSE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
