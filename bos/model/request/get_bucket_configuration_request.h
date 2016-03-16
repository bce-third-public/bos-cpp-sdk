/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file get_bucket_configuration_request.h
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/11 14:45:53
 * @brief 
 *  
 **/




#ifndef  INF_DS_BOSS_SDK_CPP_REQUEST_GET_BUCKET_CONFIGURATION_REQUEST_H_
#define  INF_DS_BOSS_SDK_CPP_REQUEST_GET_BUCKET_CONFIGURATION_REQUEST_H_

#include "bos/model/request/bucket_request.h"
#include "bos/model/request/bos_constraint.h"

namespace bce{
namespace bos{
class GetBucketConfigurationRequest : public BucketRequest{

public:
    GetBucketConfigurationRequest( const std::string &bucket_name );
    
    virtual ~GetBucketConfigurationRequest(){
    }


protected:
    int BuildCommandSpecific(HttpRequest *request);
        

};
}
}

#endif  //__GET_BUCKET_CONFIGURATION_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
