/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file get_bucket_acl_response.h
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/18 16:09:28
 * @brief 
 *  
 **/




#ifndef  INF_DS_BOSS_SDK_CPP_RESPONSE_GET_BUCKET_ACL_RESPONSE_H_
#define  INF_DS_BOSS_SDK_CPP_RESPONSE_GET_BUCKET_ACL_RESPONSE_H_
#include "bos/model/response/response.h"
#include "util/memory_stream.h"
#include <vector>
#include <string>
#include <sstream>
namespace bce {
namespace bos {
struct AccessControl{
    std::string displayName;
    std::string id;
    std::string permission;
};
class GetBucketAclResponse : public BosResponse {
    
public:
    GetBucketAclResponse() {
        m_buffer = new std::string;
        m_str_outputStream = new StringOutputStream(m_buffer);
        SetOutputStream(m_str_outputStream);
    }
    
    virtual ~GetBucketAclResponse();
    
    int GetAcl(std::string *acl) const {
        return GetResponseHeader("x-bce-acl", acl);
    }
    
    int GetDisplayName(std::string *display_name) {
        if(m_displayName=="") {
            return -1;
        } else {
            display_name->assign(m_displayName);
        }

        return 0;
    }
    
    int GetId(std::string *id) {
        if(m_id == "") {
            return -1;
        } else {
            id->assign(m_id);
        }
        return 0;
    }
        
    int GetAccessControlList(std::vector<AccessControl> *access_control_list) {
        *access_control_list = m_accessControlList;
        return 0;
    }

protected:
    int ParseCommandSpecificResponse();

private:
    std::string m_displayName;
    std::string m_id;
    std::vector<AccessControl> m_accessControlList;
    std::string *m_buffer;
    OutputStream *m_str_outputStream;
}; 
}
}














#endif  //__GET_BUCKET_ACL_RESPONSE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
