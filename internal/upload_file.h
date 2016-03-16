/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file upload_file.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/08/12 10:58:19
 * @brief 
 *  
 **/




#ifndef  __UPLOAD_FILE_H_
#define  __UPLOAD_FILE_H_

#include <sstream>
#include "bos/api.h"
#include "bos/model/request/put_object_request.h"
#include "bos/model/response/put_object_response.h"
#include "util/file_stream.h"
#include "internal/client_impl.h"

namespace bce {
namespace bos {

class UploadFile {
public:
    UploadFile(const ClientImpl *t_client, const std::string &bucket, 
            const std::string &object, const std::string &file) : 
                m_client(const_cast<ClientImpl *>(t_client)) {
 
        m_ifs = NULL;

        m_ifs = new FileInputStream(file);
        m_request = new PutObjectRequest(bucket, object, m_ifs);
        m_response = new PutObjectResponse;
    }

    ~UploadFile() {
        if (m_request) {
            delete m_request ;
            m_request = NULL;
        }

        if (m_response) {
            delete m_response;
            m_response = NULL;
        }

        if (m_ifs) {
            delete m_ifs;
            m_ifs = NULL;
        }
    }
    
    int AddUserMetaData(const std::string &key, const std::string &value) {
        return m_request->AddUserMetaData(key, value);
    }
    
    int Upload() {

        if (m_ifs->GetSize() == -1001) {
            printf("no such file!\n");

            return -1;
        }

        int ret = m_client->PutObject(*m_request, m_response);
        
        if (ret != 0) {
            printf("upload error %d %s\n", ret, m_response->GetMessage().c_str());
            return ret ;
        }
        m_response->GetETag(&m_etag);
        return 0;
    }

    int GetETag(std::string *t_etag) {
        t_etag->assign(m_etag);
        return 0;
    }
    
private:
    ClientImpl *m_client;
    std::string m_etag;

    PutObjectRequest *m_request;
    PutObjectResponse *m_response;
    FileInputStream *m_ifs;
};

}
}
#endif  //__UPLOAD_FILE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
