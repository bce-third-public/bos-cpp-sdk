/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file head_object_response.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/17 11:22:06
 * @brief 
 *  
 **/




#ifndef  __HEAD_OBJECT_RESPONSE_H_
#define  __HEAD_OBJECT_RESPONSE_H_

#include "bos/model/response/response.h"
#include "util/memory_stream.h"

namespace bce {
namespace bos {
class HeadObjectResponse : public BosResponse {
public:

    HeadObjectResponse() {
    }

    virtual ~HeadObjectResponse() {
    }

    int GetETag(std::string *etag) const {
        return GetResponseHeader("ETag", etag);
    }

    int GetLength(uint64_t *length) const {
        std::string tmp_len;
        if(GetResponseHeader("Content-Length", &tmp_len)) {
            return -1;
        }
        std::stringstream ss;
        ss << tmp_len;
        ss >> (*length);
        return 0;
    }

    int GetObjectMetaData(std::map<std::string, std::string> *object_meta_data) const ;
};
}
}






#endif  //__HEAD_OBJECT_RESPONSE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
