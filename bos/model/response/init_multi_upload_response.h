/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file init_multi_upload_response.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/18 11:33:25
 * @brief 
 *  
 **/




#ifndef  __INIT_MULTI_UPLOAD_RESPONSE_H_
#define  __INIT_MULTI_UPLOAD_RESPONSE_H_

#include "util/memory_stream.h"
#include "bos/model/response/response.h"

namespace bce {
namespace bos {
class OutputStream;
class InitMultiUploadResponse : public BosResponse {
public:
    InitMultiUploadResponse() {
        m_content = new std::string;
        m_content_stream = new StringOutputStream(m_content);
        SetOutputStream(m_content_stream);
    }

    virtual ~InitMultiUploadResponse() {
        delete m_content_stream;
        delete m_content;
    }

    int GetUploadId(std::string *upload_id) {
        upload_id->assign( m_upload_id);
        return 0;
    }

    int GetKey(std::string *key) {
        key->assign(m_key);
        return 0;
    }

    int GetBucket(std::string *bucket) {
        bucket->assign(m_bucket);
        return 0;
    }

protected:
    virtual int ParseCommandSpecificResponse();

private:
    std::string m_bucket;
    std::string m_key;
    std::string m_upload_id;
    OutputStream *m_content_stream;
    std::string *m_content;
    
 
};
}
}














#endif  //__INIT_MULTI_UPLOAD_RESPONSE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
