/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/

// ʹ��bns˵����
// 1���ڽ���������ʱ�򣬵���һ������bns����ʱ�䣬��λΪms
// bce::bos::set_bns_local_cache_time(5000);
// 2����ʹ��ClientOptions��ʱ��
// ClientOptions options;
// ����timeout��auth_version
// ����options.set_use_bns();
// ����init_bns����������bns_name
// options.init_bns("XXX");
// ע��init_bns�Ƿ�ɹ����ɹ�����0�����ɹ���options������
// 3��Client client(ak, sk, options);
// 4������client�Ľӿڷ������ӿ�ʹ�÷�ʽ����
// ע��ClientOptions��Client���̰߳�ȫ

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
