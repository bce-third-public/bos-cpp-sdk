/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file response/copy_object_response.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/17 13:40:38
 * @brief 
 *  
 **/




#ifndef  __COPY_OBJECT_RESPONSE_H_
#define  __COPY_OBJECT_RESPONSE_H_

#include <sstream>
#include "bos/model/response/response.h"
#include "util/memory_stream.h"

namespace bce {
namespace bos {

class CopyObjectResponse : public BosResponse {

public:
    CopyObjectResponse() {
          m_content = new std::string;
          m_content_stream = new StringOutputStream(m_content);
          SetOutputStream(m_content_stream);
    }

    virtual ~CopyObjectResponse() {
        delete m_content_stream;
        delete m_content;
    }

    int GetLastModified(std::string *last_modified) const {
        last_modified->assign(m_last_modified);
        return 0;
    }

    int  GetETag(std::string *etag) const {
        etag->assign(m_etag);
        return 0;
    }

protected:
    int ParseCommandSpecificResponse() ;

private:
    std::string m_last_modified;
    std::string m_etag;
    std::string *m_content;
    OutputStream *m_content_stream;

};

}
}












#endif  //__RESPONSE/COPY_OBJECT_RESPONSE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
