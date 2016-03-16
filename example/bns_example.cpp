/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/

// 使用bns说明：
// 1、在进程启动的时候，调用一次设置bns缓存时间，单位为ms
// bce::bos::set_bns_local_cache_time(5000);
// 2、在使用ClientOptions的时候
// ClientOptions options;
// 设置timeout，auth_version
// 设置options.set_use_bns();
// 调用init_bns方法，传入bns_name
// options.init_bns("XXX");
// 注意init_bns是否成功，成功返回0，不成功则options不可用
// 3、Client client(ak, sk, options);
// 4、调用client的接口方法，接口使用方式不变
// 注：ClientOptions，Client非线程安全

#include "bos/api.h"
#include "internal/client_impl.h"
#include "example/file_stream.h"
#include "util/memory_stream.h"
#include <iostream>

using namespace bce::bos;

int PrintLog(const std::string &log) {
    std::cout << log << std::endl;
}

int main() 
{
    Log::UserPrint = PrintLog;
    bce::bos::set_bns_local_cache_time(5000);
    ClientOptions options;
    options.set_use_bns();
    const std::string bns_name = "bj-cu-nginx-bos-online.BCE.all";
    if (options.init_bns(bns_name) == -1) {
        printf("init_bns failed\n");
        return -1;
    }
    options.auth_version = ClientOptions::kBceAuth;
    Client client("3fb7c326f25140b5a9a05497fbc09f60", "f81162192e7d4e5798e3f20f71a3909c", options);
    {
        // test PutObject
        std::string data = "test_data12345678";
        int ret = client.PutObject("bos-rd-123456", "test_object_2", data);
        printf("GetObject, ret:%d\n", ret);
    }
    {
        // test GetObject
        std::string data;
        int ret = client.GetObject("bos-rd-123456", "test_object_2", &data);
        printf("GetObject:ret : %d, data:%s\n", ret, data.c_str());
    }
    {
        // test ListObjects
        std::string bucket_name = "bos-rd-123456";
        ListObjectsRequest request(bucket_name);
        ListObjectsResponse response;
        int ret = client.ListObjects(request, &response);
        std::vector<Content> tmp_contents;
        response.GetContents(&tmp_contents);
        printf("ListObjects:ret : %d, object_size:%lu\n", ret, tmp_contents.size());
    } 
    {
        // test HeadObject
        HeadObjectRequest head_request("bos-rd-123456", "test_object_2");
        HeadObjectResponse head_result;
        int ret = client.HeadObject(head_request, &head_result);
        int length = 0;
        head_result.GetLength(&length);
        printf("HeadObject:ret : %d, length:%d\n", ret, length);
    }
    return 0;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
