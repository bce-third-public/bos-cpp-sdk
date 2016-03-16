/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file upload_part_request.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/18 12:43:30
 * @brief 
 *  
 **/




#ifndef  __UPLOAD_PART_REQUEST_H_
#define  __UPLOAD_PART_REQUEST_H_

#include <sstream>
#include "bos/model/request/object_request.h"
#include "util/memory_stream.h"
namespace bce {
namespace bos {
class UploadPartRequest : public ObjectRequest {
public:
    UploadPartRequest(const std::string &bucket_name, const std::string &object_name, const std::string &data, int part_number, const std::string &upload_id) :
        ObjectRequest(bucket_name,object_name,kHttpPut) {
        m_owner = true;
        m_content_stream = new MemoryInputStream(data.data(), data.size());
        SetInputStream(m_content_stream);
        std::stringstream ss;
        m_part_number = part_number;
        ss << part_number;
        SetQueryString("partNumber", ss.str());
        SetQueryString("uploadId", upload_id);    
    }

    UploadPartRequest(const std::string &bucket_name, const std::string &object_name, 
            InputStream *stream, int part_number, const std::string &upload_id) :
        ObjectRequest(bucket_name,object_name,kHttpPut) {
        m_owner = false;
        m_content_stream = stream;
        SetInputStream(m_content_stream);
        std::stringstream ss;
        m_part_number = part_number;
        ss << part_number;
        SetQueryString("partNumber", ss.str());
        SetQueryString("uploadId", upload_id);    
    }

    virtual ~UploadPartRequest() {
        if(m_owner && m_content_stream) {
            delete m_content_stream;
            m_content_stream = NULL;
        }
    }
    
    virtual int CalculateObjectFinger(bce::bos::InputStream *stream, std::string *md5, std::string *sha256) const ;

    virtual bool CheckParameter() {
        ObjectRequest::CheckParameter();
        if(m_part_number < 1 || m_part_number > 10000) {
            throw BosIllegalArgumentException("illegal part number");
        }
        return true;
    }

protected:
    int BuildCommandSpecific(HttpRequest *http_request);

private:
    InputStream *m_content_stream;
    bool  m_owner;
    int m_part_number;


};
}
}














#endif  //__UPLOAD_PART_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
