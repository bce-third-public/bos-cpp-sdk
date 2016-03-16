#define private public
#include "bos/api.h"
#include "util/memory_stream.h"

using namespace bce::bos;
int main() {
    ClientOptions options;
    options.boss_host = "10.216.45.63:8081";
    options.auth_version = ClientOptions::kBceAuth;
    Client client("cuicanak", "cuicansk", options);
    {
        std::string data = "test_data12345678";
        int ret = client.PutObject("cuican-test3", "test_object_2", data);
        printf("GetObject, ret:%d\n", ret);
    }
    {
        std::string data;
        int ret = client.GetObject("cuican-test3", "test_object_2", &data);
        printf("GetObject:ret : %d, data:%s\n", ret, data.c_str());
    }

    return 0;
}
