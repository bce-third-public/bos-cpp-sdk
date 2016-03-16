/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file put_bucket_acl_request.h
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/18 10:56:00
 * @brief 
 *  
 **/


#ifndef  INF_DS_BOSS_SDK_CPP_REQUEST_PUT_BUCKET_ACL_REQUEST_H_
#define  INF_DS_BOSS_SDK_CPP_REQUEST_PUT_BUCKET_ACL_REQUEST_H_

#include <sstream>
#include "bos/model/request/bucket_request.h"
#include "bos/model/request/bos_constraint.h"

namespace bce {
namespace bos {
class PutBucketAclRequest : public BucketRequest {

public:
    PutBucketAclRequest(const std::string &bucket_name, const std::string &acl);
    virtual ~PutBucketAclRequest(){
    }

protected:
    int BuildCommandSpecific(HttpRequest *request);
    
private:
    std::string m_acl;
        
};
}
}















#endif  //__PUT_BUCKET_ACL_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
