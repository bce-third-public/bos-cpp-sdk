/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file head_bucket_request.h
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/17 15:28:49
 * @brief 
 *  
 **/




#ifndef  INF_DS_BOSS_SDK_CPP_REQUEST_HEAD_BUCKET_REQUEST_H_
#define  INF_DS_BOSS_SDK_CPP_REQUEST_HEAD_BUCKET_REQUEST_H_
#include "bos/model/request/bucket_request.h"
namespace bce{
namespace bos{
class HeadBucketRequest : public BucketRequest {
public:
    HeadBucketRequest(const std::string &bucket_name);
    virtual ~HeadBucketRequest(){
    }
};
}
}















#endif  //__HEAD_BUCKET_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
