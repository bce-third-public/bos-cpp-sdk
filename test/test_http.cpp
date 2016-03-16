#define private public
#include "src/http.h"
#include "src/memory_stream.h"

using namespace bce::bos;
static const int kBodySize = 1024 * 128;
static char g_body_buffer[kBodySize];
int main() {
    HttpClient http_client;
    HttpRequest request;
    request.SetHttpMethod("GET");
    request.SetUri("http://127.0.0.1:12345/");

    MemoryOutputStream body_output_stream(g_body_buffer, kBodySize);
    HttpResponse response;

    response.SetBodyOutputStream(&body_output_stream);

    int ret = http_client.Request(request, &response);
    /*
    printf("header:\n%s\n\nbody:\n%s\n", response.m_header_stream.GetBufferString().c_str(), body_output_stream.GetBufferString().c_str());

    response.ParseHttpHeader(response.m_header_stream);
    */
    response.Print();
    return ret;
}
