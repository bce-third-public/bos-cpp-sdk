/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_bucket_request.h
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/09 19:14:48
 * @brief 
 *  
 **/


#ifndef  __LIST_BUCKET_REQUEST_H_
#define  __LIST_BUCKET_REQUEST_H_
#include <sstream>

#include "bos/model/request/request.h"
#include "bos/model/request/bos_constraint.h"

namespace bce {
namespace bos {
class ListBucketRequest : public BosRequest{
public:
    ListBucketRequest();
    virtual ~ListBucketRequest();
};
}
}










#endif  //__LIST_BUCKET_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
