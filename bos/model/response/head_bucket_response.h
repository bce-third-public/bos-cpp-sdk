/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file head_bucket_response.h
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/17 15:38:04
 * @brief 
 *  
 **/




#ifndef  INF_DS_BOSS_SDK_CPP_RESPONSE_HEAD_BUCKET_RESPONSE_H_
#define  INF_DS_BOSS_SDK_CPP_RESPONSE_HEAD_BUCKET_RESPONSE_H_

#include "bos/model/response/response.h"
#include "util/memory_stream.h"

namespace bce{
namespace bos{
class HeadBucketResponse : public BosResponse {
public:
    HeadBucketResponse();

    virtual ~HeadBucketResponse();

};
}
}















#endif  //__HEAD_BUCKET_RESPONSE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
