/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file put_bucket_response.h
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/09 14:35:20
 * @brief 
 *  
 **/

#ifndef  INF_DS_BOSS_SDK_CPP_RESPONSE_PUT_BUCKET_RESPONSE_H_
#define  INF_DS_BOSS_SDK_CPP_RESPONSE_PUT_BUCKET_RESPONSE_H_
#include "bos/model/response/response.h"
#include "util/memory_stream.h"
namespace bce{
namespace bos{
class PutBucketResponse : public BosResponse{
public :
    virtual ~PutBucketResponse(){
    }
    int GetLocation(std::string *location) const {
        return GetResponseHeader("Location", location);
    }
};
}
}

#endif // INF_DS_BOSS_SDK_CPP_RESPONSE_PUT_BUCKET_RESPONSE_H_
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
