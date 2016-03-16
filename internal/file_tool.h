/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file file_tool.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/08/13 13:33:05
 * @brief 
 *  
 **/




#ifndef  __FILE_TOOL_H_
#define  __FILE_TOOL_H_

#include "internal/upload_file.h"
#include "internal/download_file.h"
#include "internal/upload_super_file.h"
#include "internal/client_impl.h"
namespace bce {
namespace bos {

class FileTool {
public:
    FileTool(ClientImpl *client) : m_client(client) {

    }

    ~FileTool() {

    }

    int UploadFileRequest(const std::string &bucket_name, const std::string &object_name, 
        const std::string &file_name, 
        std::map<std::string, std::string> *user_meta_data = NULL, 
        std::string *etag = NULL);

    
    int DownloadFileRequest(const std::string &bucket_name, 
        const std::string &object_name,
        const std::string &file_name, 
        int64_t start = -1,
        int64_t length = -1, 
        std::map<std::string, std::string> *object_meta_data = NULL,
        std::string *etag = NULL,
        uint64_t *content_length = NULL,
        std::string *range = NULL) ;

    
    int UploadSuperFileRequest(const std::string &bucket_name, 
        const std::string &object_name, 
        const std::string &file_name, 
        std::map<std::string, std::string> *user_meta_data = NULL, 
        std::string *etag = NULL) ;
private:
    ClientImpl *m_client;
};
}
}













#endif  //__FILE_TOOL_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
