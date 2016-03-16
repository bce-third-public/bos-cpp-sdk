/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_objects_request.h
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/21 15:33:14
 * @brief 
 *  
 **/



#ifndef INF_DS_BOSS_SDK_CPP_REQUEST_LIST_OBJECT_REQUEST_H_
#define INF_DS_BOSS_SDK_CPP_REQUEST_LIST_OBJECT_REQUEST_H_
#include <sstream>
#include <string>
#include "bos/model/request/bucket_request.h"
#include "bos/model/request/bos_constraint.h"
#include "util/exception.h"
namespace bce {
namespace bos {
class ListObjectsRequest : public BucketRequest {
public:
    ListObjectsRequest(const std::string &bucket_name);
    virtual ~ListObjectsRequest(){
    }
    
    int SetDelimiter(std::string delimiter){
        SetQueryString("delimiter", delimiter);
        return 0;
    }
    
    int SetMarker(std::string marker){
        SetQueryString("marker", marker);
        return 0;
    }
    
    int SetMaxKeys(int maxKeys){
        std::stringstream ss;
        
        if(maxKeys < 0){
            Log::PrintLog(ERROR, TRACE, "set max keys fail!");
            return -1;
        } else if(maxKeys > 1000){
            SetQueryString("maxKeys", "1000");
        } else{
            ss << maxKeys;
            SetQueryString("maxKeys", ss.str());
        }
        return 0;
    }
    
    int SetPrefix(std::string prefix){
        SetQueryString("prefix", prefix);
        return 0;
    }
};
}
}
















#endif  //__LIST_OBJECTS_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
