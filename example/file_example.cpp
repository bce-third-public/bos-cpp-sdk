#include "bos/api.h"
#include "internal/client_impl.h"
#include "example/file_stream.h"

#include "util/memory_stream.h"
#include <iostream>

using namespace bce::bos;

int PrintLog(const std::string &log) {
    std::cout << log << std::endl;
}

int main() {
    Log::UserPrint = PrintLog;
    ClientOptions options;
    options.boss_host = "bos.bce-sandbox.baidu.com";
    options.auth_version = ClientOptions::kBceAuth;
    Client client("0cf03dc6f2324ea2b2f96d2f7120f9ca", "c9739003a32c4df6ba3aae73da333c1e", options);

    {
        FileInputStream ifs("file_example.cpp");

        PutObjectRequest request("bos-4", "test-file", &ifs);
        PutObjectResponse result;
        int ret = client.PutObject(request, &result);
        std::string etag;
        result.GetETag(&etag);
        std::string version;
        result.GetVersion(&version);
        printf("PutObject:ret : %d, message:%s etag:%s, version:%s\n",
                ret, result.GetMessage().c_str(), etag.c_str(), version.c_str());
    }

    {
        GetObjectRequest request("bos-4", "test-file");

        FileOutputStream ofs("file_stream.out");
        GetObjectResponse result(&ofs);
        int ret = client.GetObject(request, &result);

        printf("ret:%d, message:%s\n", ret, result.GetMessage().c_str());
    }

    return 0;
}
