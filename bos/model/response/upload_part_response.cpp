/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file upload_part_response.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/18 13:11:38
 * @brief 
 *  
 **/

#include "bos/model/response/upload_part_response.h"
namespace bce {
namespace bos {

int UploadPartResponse::GetETag(std::string *etag) const {
    int ret = GetResponseHeader("ETag",etag);
    if(ret != 0)
        return ret;
    else {
        etag->erase(etag->begin(), etag->begin()+1);
        etag->erase(etag->end()-1, etag->end());
        return 0;
    }
}

}
}




















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
