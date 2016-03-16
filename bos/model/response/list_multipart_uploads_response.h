/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_multipart_uploads_response.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/21 10:04:58
 * @brief 
 *  
 **/




#ifndef  __LIST_MULTIPART_UPLOADS_RESPONSE_H_
#define  __LIST_MULTIPART_UPLOADS_RESPONSE_H_

#include <sstream>
#include <vector>
#include "bos/model/response/response.h"
#include "util/memory_stream.h"
namespace bce {
namespace bos {
struct OwnerInUpload {
    std::string m_id;
    std::string m_display_name;
};

struct Upload {
    std::string  m_key;
    std::string  m_upload_id;
    OwnerInUpload  m_owner;
    std::string m_initiated;
    
};

class ListMultipartUploadsResponse : public BosResponse {
public:
    ListMultipartUploadsResponse() {
        m_content = new std::string;
        m_content_stream = new StringOutputStream(m_content);
        SetOutputStream(m_content_stream);
    }

    virtual ~ListMultipartUploadsResponse() {
        delete m_content_stream;
        delete m_content;
    }

    int GetBucket(std::string *bucket) {
        bucket->assign(m_bucket);
        return 0;
    }

    int GetKeyMarker(std::string *key_marker) {
        key_marker->assign(m_key_marker);
        return 0;
    }

    int GetNextKeyMarker(std::string *next_key_marker) {
        next_key_marker->assign(m_next_key_marker);
        return 0;
    }

    int GetMaxUploads(int *max_uploads) {
        std::stringstream ss;
        ss << m_max_uploads;
        ss >> (*max_uploads);
        return 0;
    }

    int GetIsTruncated(bool *is_truncated) {
        std::stringstream ss;
        ss << m_is_truncated;
        ss >> (*is_truncated);
        return 0;
    }

    int GetUploads(std::vector<Upload> *uploads) {
        *uploads = m_uploads;
        return 0;
    
    }
    
    int GetCommonPrefixes(std::string *common_prefixes) {
        common_prefixes->assign(m_common_prefixes);
        return 0;
    }

    int GetPrefix(std::string *prefix) {
        prefix->assign(m_prefix);
        return 0;
    }

protected:
    int ParseCommandSpecificResponse();

private:
    std::string m_bucket;
    std::string m_key_marker;
    std::string m_next_key_marker;
    std::string m_max_uploads;
    std::string  m_is_truncated;
    std::vector<Upload> m_uploads;
    std::string m_common_prefixes;
    std::string m_prefix;
    std::string *m_content;
    OutputStream *m_content_stream;

};
}
}














#endif  //__LIST_MULTIPART_UPLOADS_RESPONSE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
