/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file copy_object_request.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/16 13:16:08
 * @brief 
 *  
 **/




#ifndef  __COPY_OBJECT_REQUEST_H_
#define  __COPY_OBJECT_REQUEST_H_

#include <sstream>

#include "bos/model/request/object_request.h"
#include "util/common_def.h"
#include "bos/model/request/bos_constraint.h"

namespace bce {
namespace bos {
class CopyObjectRequest : public ObjectRequest {
public:
    CopyObjectRequest(const std::string &bucket_name, const std::string &object_name, const std::string &source_bucket_name, const std::string &source_object_name);

    virtual ~CopyObjectRequest() {
    }

    int AddCopySourceIfMatch(const std::string &etag);

    int AddCopyMetaDataDirective(const std::string &directive);

    int AddUserMetaData(const std::string &key, const std::string &value) {
        if(IsVaildObjectMetaKey(key)) {
            SetRequestHeader(key, value);
            return 0;
        }
        Log::PrintLog(ERROR, TRACE, "add user meta data fail!");
        return kBosIllegalArgument;
    }
    virtual bool CheckParameter() {
        ObjectRequest::CheckParameter();

        BosConstraint::CheckBucketName(m_source_bucket_name);
        BosConstraint::CheckObjectName(m_source_object_name);

        return true;
    }

private:
    std::string m_source_bucket_name;
    std::string m_source_object_name;

};
}
}














#endif  //__COPY_OBJECT_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
