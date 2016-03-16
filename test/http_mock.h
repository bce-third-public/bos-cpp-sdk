#ifndef INF_DS_BOSS_SDK_C_TEST_HTTP_MOCK_H_
#define INF_DS_BOSS_SDK_C_TEST_HTTP_MOCK_H_
#include <stdlib.h>

#include <map>
#include <string>
#include <sstream>

#include "test/file_util.h"

class HttpMock {
public:
    static int Start() {
        system("/bin/sh start_mock_server.sh");
        return 0;
    }
    static int Stop() {
        system("/bin/sh stop_mock_server.sh");
        return 0;
    }

    HttpMock() {
        m_response_code = 200;
    }

    int AddExpectHeader(const std::string &key, const std::string &val) {
        m_expect_header[key] = val;
        return 0;
    }

    int SetExpectData(const std::string &data) {
        m_expect_data = data;
        return 0;
    }

    int AddResponseHeader(const std::string &key, const std::string &val) {
        m_response_header[key] = val;
        return 0;
    }

    int SetResponseData(const std::string &data) {
        m_response_data = data;
        return 0;
    }

    int SetResponseCode(int code) {
        m_response_code = code;
        return 0;
    }

    int SetObjectName(const std::string &bucket_name, const std::string &object_name) {
        m_bucket_name = bucket_name;
        m_object_name = object_name;
        return 0;
    }

    int FinishMockSetting() {
        std::stringstream ss;
        ss << "{"
            << "\"req\" : {"
                << "\"header\" : {"
                    << "\"required\" : "
                        << Map2JsonStr(m_expect_header) << ","
                    << "\"optional\" : {}"
                << "},"
                << "\"body\" : \"" << m_expect_data << "\""
            << "},"
            << "\"res\" : {"
                << "\"header\" :"
                    << Map2JsonStr(m_response_header) << ","
                << "\"body\" : \"" << m_response_data << "\","
                << "\"code\" : " << m_response_code << ""
            << "}"
          << "}";

       FileUtil::WriteFile(std::string("json-api_v1_")
               + m_bucket_name + "_" + m_object_name, ss.str());
       return 0;
    }

private:
    std::map<std::string, std::string> m_expect_header;
    std::string m_expect_data;

    std::map<std::string, std::string> m_response_header;
    std::string m_response_data;
    int m_response_code;

    std::string Map2JsonStr(const std::map<std::string, std::string> &map_obj) {
        std::stringstream ss;
        ss << "{";
        for (std::map<std::string, std::string>::const_iterator it =  map_obj.begin();
                it != map_obj.end(); it++) {
            if (it != map_obj.begin()) {
                ss << ",";
            }
            ss << "\"" << it->first << "\" : \"" << it->second << "\"";
        }

        ss << "}";

        return ss.str();
    }

    std::string m_bucket_name;
    std::string m_object_name;
};
#endif //INF_DS_BOSS_SDK_C_TEST_HTTP_MOCK_H_
