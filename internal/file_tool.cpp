/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file file_tool.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/08/13 13:30:28
 * @brief 
 *  
 **/

#include "internal/file_tool.h" 
#include <map>

namespace bce {
namespace bos {


int FileTool::UploadFileRequest(const std::string &bucket_name, 
        const std::string &object_name, 
        const std::string &file_name, 
        std::map<std::string, std::string> *user_meta_data, 
        std::string *etag) {
    UploadFile upload_file(m_client, bucket_name, object_name, file_name);
    
    if(user_meta_data != NULL) {
        std::map<std::string, std::string>::iterator it;
        for (it = user_meta_data->begin(); it != user_meta_data->end(); it++) {
            int ret = upload_file.AddUserMetaData(it->first, it->second);
            if(ret != 0) {
                return ret;
            }
        }
    }

    int ret = upload_file.Upload();
    if(ret != 0) {
        return ret;
    }

    if(etag != NULL) {
        int ret = upload_file.GetETag(etag);
        if(ret != 0) {
            printf("Get etag error!\n");
            return ret ;
        }
    }

    return 0;
}


int FileTool::UploadSuperFileRequest(const std::string &bucket_name, 
        const std::string &object_name, 
        const std::string &file_name, 
        std::map<std::string, std::string> *user_meta_data, 
        std::string *etag) {

    UploadSuperFile upload_super_file(m_client, bucket_name, object_name, file_name);

    if(user_meta_data != NULL) {
        std::map<std::string, std::string>::iterator it;
        for (it = user_meta_data->begin(); it != user_meta_data->end(); it++) {
            int ret = upload_super_file.AddUserMetaData(it->first, it->second);
            if(ret != 0) {
                return ret;
            }
        }
    }

    int ret = upload_super_file.Upload();
    if(ret != 0) {
        return ret;
    }

    if(etag != NULL) {
        int ret = upload_super_file.GetETag(etag);
        if(ret != 0) {
            printf("Get etag error!\n");
            return ret ;
        }
    }
    
    return 0;
}

int FileTool::DownloadFileRequest(const std::string &bucket_name, 
        const std::string &object_name,
        const std::string &file_name, 
        int64_t start,
        int64_t length, 
        std::map<std::string, std::string> *object_meta_data,
        std::string *etag,
        uint64_t *content_length,
        std::string *range) {

    DownloadFile download_file(m_client, bucket_name, object_name, file_name);
    if (start != -1 && length != -1) {
        int ret = download_file.SetRange(start, length);
        if(ret != 0) {
            printf("set range error \n");
            return ret;
        }
    }
    
    int ret = download_file.Download();
    if(ret != 0) {
        return ret;
    }

    if(object_meta_data != NULL) {
        download_file.GetObjectMetaData(object_meta_data);
    }

    if(etag != NULL) {
        download_file.GetETag(etag);
    }

    if(content_length != NULL) {
        download_file.GetLength(content_length);
    }

    if(range != NULL) {
        download_file.GetRange(range);
    }

    return 0;

}




}
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
