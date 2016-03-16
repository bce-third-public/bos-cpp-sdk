/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file get_bucket_acl_request.h
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/18 15:26:15
 * @brief 
 *  
 **/


#ifndef  INF_DS_BOSS_SDK_CPP_REQUEST_GET_BUCKET_ACL_REQUEST_H_
#define  INF_DS_BOSS_SDK_CPP_REQUEST_GET_BUCKET_ACL_REQUEST_H_
#include <sstream>

#include "bos/model/request/bucket_request.h"
#include "bos/model/request/bos_constraint.h"
namespace bce{
namespace bos{
class GetBucketAclRequest : public  BucketRequest {
public:
    GetBucketAclRequest(const std::string &bucket_name);

    virtual ~GetBucketAclRequest(){
    }
    
protected:
    int BuildCommandSpecific(HttpRequest *request);

};
}
}















#endif  //__GET_BUCKET_ACL_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
