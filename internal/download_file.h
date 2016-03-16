/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file download_file.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/08/12 11:13:14
 * @brief 
 *  
 **/




#ifndef  __DOWNLOAD_FILE_H_
#define  __DOWNLOAD_FILE_H_

#include <sstream>
#include "bos/model/request/get_object_request.h"
#include "bos/model/response/get_object_response.h"
#include "util/file_stream.h"
#include "bos/api.h"
#include "internal/client_impl.h"

namespace bce {
namespace bos {

class DownloadFile {
public:
    DownloadFile(const ClientImpl * t_client, const std::string &bucket, 
            const std::string &object, const std::string &file) {
        m_client = const_cast<ClientImpl *>(t_client);    

        m_ofs = NULL;
        m_ofs = new FileOutputStream(file);

        m_request = new GetObjectRequest(bucket, object);
        m_response = new GetObjectResponse(m_ofs);
    }

    ~DownloadFile() {
        if (m_response) {
            delete m_response;
        }

        if (m_request) {
            delete m_request;
        }

        if (m_ofs) {
            delete m_ofs;
        }
    }
    
    int SetRange(int64_t start, int64_t length) {
        return m_request->SetRange(start, length);
    }

    int Download() {
        if (m_ofs == NULL) {
            
            printf("no sush file!\n");
            return -1;
        }

        int ret = m_client->GetObject(*m_request, m_response);

        if (ret != 0) {
            printf("download error %d %s\n", ret, m_response->GetMessage().c_str());
            return ret;
        }
        return 0;
    }

    int GetObjectMetaData(std::map<std::string, std::string> *object_meta_data) const {
        return m_response->GetObjectMetaData(object_meta_data);
    }

    int GetETag(std::string *etag) const {
        return m_response->GetETag(etag);
    } 

    int GetLength(uint64_t *length) const {
        return m_response->GetLength(length);
    }

    int GetRange(std::string *range) const {
        return m_response->GetRange(range);
    }

private:
    ClientImpl *m_client;
    
    FileOutputStream *m_ofs;
    GetObjectRequest *m_request;
    GetObjectResponse *m_response;

};

}
}














#endif  //__DOWNLOAD_FILE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
