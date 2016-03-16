/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_bucket_response.h
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/09 19:35:34
 * @brief 
 *  
 **/

#ifndef  INF_DS_BOSS_SDK_CPP_RESPONSE_LIST_BUCKET_RESPONSE_H_
#define  INF_DS_BOSS_SDK_CPP_RESPONSE_LIST_BUCKET_RESPONSE_H_
#include "bos/model/response/response.h"
#include "util/memory_stream.h"
#include <vector>
#include <string>
namespace bce {
namespace bos {
struct BucketInfo {
   std::string bucket_name;
   std::string creationDate;
};

class ListBucketResponse : public BosResponse {
public:
    ListBucketResponse(){
        m_buffer = new std::string;
        m_str_outputStream = new StringOutputStream(m_buffer );
        SetOutputStream(m_str_outputStream);
    }
    virtual  ~ListBucketResponse();
    
    int GetOwnerID(std::string *id) const {
        id->assign(m_owner_id);
        return 0;
    } 
    
    int GetOwnerDisplayName(std::string *display_name) {
        display_name->assign(m_owner_displayName);
        return 0;
    }
    
    int GetBuckets(std::vector<BucketInfo> *buckets){
        *buckets = m_buckets;
        return 0;
    }
    
protected:
    int ParseCommandSpecificResponse();
    
private:
    std::string m_owner_id;
    std::string m_owner_displayName;
    std::vector<BucketInfo> m_buckets;
    std::string *m_buffer ;
    StringOutputStream *m_str_outputStream;

};
}
}

#endif // INF_DS_BOSS_SDK_CPP_RESPONSE_LIST_BUCKET_RESPONSE_H_

