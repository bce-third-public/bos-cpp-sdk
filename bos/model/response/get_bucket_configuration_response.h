/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file get_bucket_configuration.h
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/16 13:56:14
 * @brief 
 *  
 **/




#ifndef  INF_DS_BOSS_SDK_CPP_RESPONSE_GET_BUCKET_CONFIGURATION_RESPONSE_H_
#define  INF_DS_BOSS_SDK_CPP_RESPONSE_GET_BUCKET_CONFIGURATION_RESPONSE_H_
#include "bos/model/response/response.h"
#include "util/memory_stream.h"
#include <string>
namespace bce {
namespace bos {

class GetBucketConfigurationResponse : public BosResponse {

public:
     GetBucketConfigurationResponse(){
        m_buffer = new std::string;
        m_str_outputStream = new StringOutputStream( m_buffer );
        SetOutputStream(m_str_outputStream);
    }

    virtual ~GetBucketConfigurationResponse();
    
    int GetLocationConstraint(std::string *location){
        location->assign(m_locationConstraint);
        return 0;
    }

protected:
    int ParseCommandSpecificResponse();

private:
    std::string m_locationConstraint;
    std::string *m_buffer;
    StringOutputStream *m_str_outputStream;

};
}
}















#endif  //INF_DS_BOSS_SDK_CPP_RESPONSE_GET_BUCKET_CONFIGURATION_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
