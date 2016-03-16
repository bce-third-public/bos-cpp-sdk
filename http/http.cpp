#include "http/http.h"

#include <sstream>

#include "curl/curl.h"

#include "util/stream.h"
#include "util/exception.h"
#include "util/log.h"
#include "util/util.h"
#include <iostream>
BEGIN_C_SDK_NAMESPACE
int HttpClient::Init() { 
    printf("call curl_global_init\n");
    return curl_global_init(CURL_GLOBAL_ALL);
}

int HttpClient::UnInit() {
    printf("call curl_global_cleanup\n");
    curl_global_cleanup();
    return 0;
}

int HttpClient::Request(const HttpRequest &request, HttpResponse *response) {
    
    CURL *curl_handle = NULL;

    struct curl_slist *http_header_slist = NULL;
    int ret = 0;
    do {

        curl_handle = curl_easy_init();
        if (curl_handle == NULL) {
            // curl_global_cleanup();
            throw BosClientException("Init Net Handle fail");
        }

        std::string url = request.GetUrl();
        // printf("http_request: url:%s\n", url.c_str());
        curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteStream);
        curl_easy_setopt(curl_handle, CURLOPT_HEADERFUNCTION, RecvHeaderLine);
        // prevent core dump when used in multi-thread application 
        // for the case the libcurl is not built with c-ares
        curl_easy_setopt(curl_handle, CURLOPT_NOSIGNAL, 1);

        const bce::bos::InputStream *req_stream = request.GetInputStream();

        HttpMethod http_method = request.GetHttpMethod();
	
	//std::cout<<http_method<<std::endl;

        curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, response);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, response);	
    	std::string post_data;  
        if (http_method == kHttpPut) {
            curl_easy_setopt(curl_handle, CURLOPT_UPLOAD, 1L);
            curl_easy_setopt(curl_handle, CURLOPT_READFUNCTION, ReadStream);
            curl_easy_setopt(curl_handle, CURLOPT_READDATA, req_stream);
	        if(req_stream == NULL) {
	        	curl_easy_setopt(curl_handle, CURLOPT_INFILESIZE_LARGE, 0);
	        } else {
           	     curl_easy_setopt(curl_handle, CURLOPT_INFILESIZE_LARGE,
                	    req_stream->GetSize() - req_stream->GetPos());
	        }
        } else if (http_method == kHttpDelete) {
	        curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "DELETE");
	    } else if (http_method == kHttpHead) {
	        curl_easy_setopt(curl_handle, CURLOPT_NOBODY, true);
	    } else if(http_method == kHttpPost) {
	        if(req_stream == NULL) {
	   	        curl_easy_setopt(curl_handle, CURLOPT_POST, true);
	    	    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, 0);
	        } else {
		        int64_t size = req_stream->GetSize()-req_stream->GetPos();
    		    bce::bos::InputStream *reader = const_cast<bce::bos::InputStream *>(req_stream);
		        reader->Read(size, &post_data);
	   	        curl_easy_setopt(curl_handle, CURLOPT_POST, true);
		        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, post_data.c_str());
		        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, size);
	        }
	    }
        // set http header
        std::vector<std::string > headers;
        request.GetAllHeaders(&headers);
        for (uint32_t i = 0; i < headers.size(); i++) {
            http_header_slist = curl_slist_append(http_header_slist, headers[i].c_str());
            // printf("http_request: header:%s\n", headers[i].c_str());
        }

        if (http_header_slist != NULL) {
            curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, http_header_slist);
        }

        int timeout = request.GetTimeout();
        if (timeout > 0) {
            curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT_MS, timeout);
        }

        int ret = curl_easy_perform(curl_handle);
        if (ret != 0) {
    	    printf("curl_easy_perform :ret %d\n",ret);
            std::stringstream ss;
            ss << "Request server fail, ret:" << ret;

            if (curl_handle != NULL) {
                curl_easy_cleanup(curl_handle);
            }

            if (http_header_slist != NULL) {
                curl_slist_free_all(http_header_slist);
            }
            // curl_global_cleanup();
            throw BosClientException(ss.str());
        }

        ret = 0;
    } while (false);

    if (curl_handle != NULL) {
        curl_easy_cleanup(curl_handle);
    }

    if (http_header_slist != NULL) {
        curl_slist_free_all(http_header_slist);
    }
    // curl_global_cleanup();
    // curl_global_cleanup();
    return ret;
}

size_t HttpClient::WriteStream(void *ptr, size_t size, size_t nmemb, void *user_data) {
    if (user_data == NULL) {
        return size * nmemb;
    }

    HttpResponse *response = reinterpret_cast<HttpResponse *>(user_data);

    return response->WriteBody(reinterpret_cast<char *>(ptr), size * nmemb);
}

size_t HttpClient::ReadStream(void *ptr, size_t size, size_t nmemb, void *stream) {
    if (stream == NULL) {
        return 0;
    }

    bce::bos::InputStream *reader = reinterpret_cast<bce::bos::InputStream *>(stream);
    return reader->Read(reinterpret_cast<char *>(ptr), size * nmemb);
}

size_t HttpClient::RecvHeaderLine(void *ptr, size_t size, size_t nmemb, void *user_data) {
    HttpResponse *response = reinterpret_cast<HttpResponse *>(user_data);
    if (response->AddResponseLine(std::string(reinterpret_cast<char *>(ptr), size * nmemb))) {
        return 0;
    }
    return size * nmemb;
}

END_C_SDK_NAMESPACE
