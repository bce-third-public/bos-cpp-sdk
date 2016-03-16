/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file abort_multipart_upload_request.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/18 13:20:32
 * @brief 
 *  
 **/




#ifndef  __ABORT_MULTIPART_UPLOAD_REQUEST_H_
#define  __ABORT_MULTIPART_UPLOAD_REQUEST_H_

#include <sstream>

#include "bos/model/request/object_request.h"

namespace bce {
namespace bos {
class AbortMultipartUploadRequest : public ObjectRequest {
public:
    AbortMultipartUploadRequest(const std::string &bucket_name, const std::string &object_name, const std::string &upload_id) :
        ObjectRequest(bucket_name, object_name, kHttpDelete) {
        SetQueryString("uploadId", upload_id);
    }

    virtual ~AbortMultipartUploadRequest();
};

}
}












#endif  //__ABORT_MULTIPART_UPLOAD_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
