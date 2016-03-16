/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file get_bucket_configuration_request.cpp
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/11 17:10:20
 * @brief 
 *  
 **/

#include "bos/model/request/get_bucket_configuration_request.h"
namespace bce{
namespace bos{
GetBucketConfigurationRequest::GetBucketConfigurationRequest( const std::string &bucket_name) :
    BucketRequest(bucket_name, kHttpGet){

}

int GetBucketConfigurationRequest::BuildCommandSpecific(HttpRequest *request){
    BosRequest:: SetQueryString("configuration","");
    return 0;
}
}
}


















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
