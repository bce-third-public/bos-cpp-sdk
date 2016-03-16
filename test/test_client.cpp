#define private public
#include "api/api.h"
#include "src/memory_stream.h"

using namespace bce::bos;
int main() {
    ClientOptions options;
    options.boss_host = "10.211.173.35:8081";
    Client client("cuicanak", "cuicansk", options);
    // Client client("cuicanak", "cuicansk");

    {
        std::string data = "test_data1234";
        // std::string data = "";
        // char *buffer = "1234567890";
        // MemoryInputStream is(buffer, strlen(buffer) + 1);

        // char tmp[1024];
        // is.Read(tmp, strlen(buffer) + 1);
        // PutObjectRequest request("cuican-test1", "/test_object_1", &is);
        // PutObjectResult result;
        // int ret = client.PutObject("cuican-test1", "/test_object_1", data);
        // printf("PutObject:ret : %d, message:%s\n", ret, result.GetMessage().c_str());
    }
    {
        std::string data;
        int ret = client.GetObject("cuican-test1", "/test_object_1", &data);
        printf("GetObject:ret : %d, data:%s\n", ret, data.c_str());
    }

    return 0;
}
