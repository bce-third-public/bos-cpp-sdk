/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file head_object_response.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/17 11:30:47
 * @brief 
 *  
 **/


#include "bos/model/response/head_object_response.h"

namespace bce {
namespace bos {

int HeadObjectResponse::GetObjectMetaData(std::map<std::string, std::string> *object_meta_data) const {
    for (std::map<std::string, std::string>::const_iterator it = GetResponseHeader().begin();
            it != GetResponseHeader().end(); it++) {
        if (IsVaildObjectMetaKey(it->first)) {
            object_meta_data->insert(std::pair<std::string, std::string>(it->first, it->second));
        }
    }

    return 0;
}
}
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
