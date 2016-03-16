/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file upload_super_file.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/08/07 16:06:30
 * @brief 
 *  
 **/




#ifndef  __UPLOAD_SUPER_FILE_H_
#define  __UPLOAD_SUPER_FILE_H_




#include <sstream>
#include <pthread.h>
#include <vector>
#include <utility>
#include "bos/api.h"
#include "json/json.h"
#include "util/file_stream.h"
#include "bos/model/request/bos_constraint.h"
#include "internal/client_impl.h"

namespace bce {
namespace bos {

struct ThreadData {
    ClientImpl *m_client;
    std::string *m_bucket;
    std::string *m_object;
    std::string *m_upload_id;
    std::string *m_buffer;
    int m_part_number;
    std::string *m_etag;
    int m_ret;
};

class UploadSuperFile {
public:
    UploadSuperFile(ClientImpl* client, const std::string &bucket_name, 
            const std::string &object_name, const std::string &file_name) : 
                m_client(client), m_bucket_name(bucket_name), 
                m_object_name(object_name), m_file_name(file_name) {
    }
    
    ~UploadSuperFile() {

    }
    int SaveCache(const std::string &upload_id, 
            const std::vector<std::pair<int, std::string> > &parts);
    
    int LoadCache(std::string *upload_id, 
            std::vector<std::pair<int, std::string> > *parts, bool *uploaded_part);

    int Upload();
    
    int GetLocation(std::string *t_location) {
        t_location->assign(m_location);
        return 0;
    }

    int GetBucket(std::string *t_bucket) {
        t_bucket->assign(m_bucket);
        return 0;
    }
    
    int GetKey(std::string *t_key) {
        t_key->assign(m_key);
        return 0;
    }

    int GetETag(std::string *t_etag) {
        t_etag->assign(m_etag);
        return 0;
    }

    int AddUserMetaData(const std::string &key, const std::string &value) {
        if (IsVaildObjectMetaKey(key)) {
            m_user_meta_data[key] = value;
            return 0;
        } 
        return kBosIllegalArgument;
    }

private:
    ClientImpl *m_client;
    std::string m_bucket_name;
    std::string m_object_name;
    std::string m_file_name;
    std::map<std::string, std::string> m_user_meta_data;
    static void* ThreadUpload(void *argv);
    std::string m_location;
    std::string m_bucket;
    std::string m_key;
    std::string m_etag;
};

}
}

#endif  //__UPLOAD_SUPER_FILE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
