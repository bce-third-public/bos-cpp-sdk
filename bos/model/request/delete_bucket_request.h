/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file delete_bucket.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/15 08:43:08
 * @brief 
 *  
 **/




#ifndef  INF_DS_BOSS_SDK_CPP_REQUEST_DELETE_BUCKET_H_
#define  INF_DS_BOSS_SDK_CPP_REQUEST_DELETE_BUCKET_H_

#include <string>
#include "bos/model/request/bucket_request.h"
#include "bos/model/request/http_request.h"
namespace bce {
namespace bos {
class DeleteBucketRequest : public BucketRequest{

public:
    DeleteBucketRequest(const std::string &bucket_name);
    virtual ~DeleteBucketRequest();


};
}
}















#endif  //__DELETE_BUCKET_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
