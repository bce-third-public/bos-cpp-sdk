/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_parts_response.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/21 11:20:27
 * @brief 
 *  
 **/




#ifndef  __LIST_PARTS_RESPONSE_H_
#define  __LIST_PARTS_RESPONSE_H_

#include <sstream>
#include <vector>
#include "bos/model/response/response.h"
#include "util/memory_stream.h"

namespace bce {
namespace bos {
struct Owner {
    std::string m_id;
    std::string m_display_name;
};

struct PartInList {
    int m_part_number;
    std::string m_last_modified;
    std::string m_etag;
    std::string m_size;
};

class ListPartsResponse : public BosResponse {
public :
    ListPartsResponse() {
        m_content = new std::string;
        m_content_stream = new StringOutputStream(m_content);
        SetOutputStream(m_content_stream);
        m_next_part_number_marker = -1;
        m_part_number_marker = -1;
        m_max_parts = -1;
    }

    virtual ~ListPartsResponse() {
        delete m_content_stream;
        delete m_content;
    }

    int GetBucket(std::string *bucket) {
        bucket->assign(m_bucket);
        return 0;
    }

    int GetKey(std::string *key) {
        key->assign(m_key);
        return 0;
    }

    int GetUploadId(std::string *upload_id) {
        upload_id->assign(m_upload_id);
        return 0;
    }

    int GetInitiated(std::string *initiated) {
        initiated->assign(m_initiated);
        return 0;
    }

    int GetOwner(Owner *owner) {
        *owner = m_owner;
        return 0;
    }

    int GetPartNumberMarker(int *part_number_marker) {
        if(m_part_number_marker == -1) {
            return -1;
        }
        *part_number_marker = m_part_number_marker;
        return 0;
    }

    int GetNextPartNumberMarker(int *next_part_number_marker) {
        if(m_next_part_number_marker == -1) {
            return -1;
        }
        *next_part_number_marker = m_next_part_number_marker;
        return 0;
    }

    int GetMaxParts(int *max_parts) {
        if(m_max_parts == -1) {
            return -1;
        }
        *max_parts = m_max_parts;
        return 0;
    }

    int GetIsTruncated(bool *is_truncated) {
        if(m_is_truncated == "") {
            return -1;
        }
        std::stringstream ss;
        ss << m_is_truncated;
        ss >> (*is_truncated);
        return 0;
    }

    int GetParts(std::vector<PartInList> *parts) {
        *parts = m_parts;
        return 0;
    }

protected:
    int ParseCommandSpecificResponse();

private:
    std::string m_bucket;
    std::string m_key;
    std::string m_upload_id;
    std::string m_initiated;
    Owner m_owner;
    int m_part_number_marker;
    int m_next_part_number_marker;
    int m_max_parts;
    std::string m_is_truncated;
    std::vector<PartInList> m_parts;
    std::string *m_content;
    OutputStream *m_content_stream;
};
}
}
















#endif  //__LIST_PARTS_RESPONSE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
