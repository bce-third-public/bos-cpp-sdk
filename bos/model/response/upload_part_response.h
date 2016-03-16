/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file upload_part_response.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/18 13:07:04
 * @brief 
 *  
 **/




#ifndef  __UPLOAD_PART_RESPONSE_H_
#define  __UPLOAD_PART_RESPONSE_H_

#include "bos/model/response/response.h"

namespace bce {
namespace bos {
class UploadPartResponse : public BosResponse {
public:
    UploadPartResponse() {
    }

    virtual ~UploadPartResponse() {
    }

    int GetETag(std::string *etag) const ;
};
}
}














#endif  //__UPLOAD_PART_RESPONSE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
