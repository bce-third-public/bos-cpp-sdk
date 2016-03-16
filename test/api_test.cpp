/*
 *    Author:       Can Cui(cuican01@baidu.com)
 *    Copyright:    Copyright 2013, Baidu Inc.
 *    Description:
 */

// Copyright 2013, Baidu Inc.
// Author: Can Cui <cuican01@baidu.com>

#define private public
#include "bos/api.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "internal/client_impl.h"
#include "test/http_mock.h"

using ::testing::_;
using ::testing::An;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::AtMost;
using ::testing::SetArgPointee;

namespace bce {
namespace bos {
class ClientTest : public testing::Test {
public:
    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }

    void SetUp() {
        m_http_mock_obj = new HttpMock;
        m_options.boss_host = "127.0.0.1:12349";
        m_client = new Client("ak", "sk", m_options);
    }

    void TearDown() {
        delete m_http_mock_obj;
        delete m_client;
    }

protected:
    HttpMock *m_http_mock_obj;
    Client *m_client;
    ClientOptions m_options;
};

TEST_F(ClientTest, TestGetObject) {
    std::string bucket_name = "test-bucket";
    std::string object_name = "test_object";
    m_http_mock_obj->AddResponseHeader("ETag", "test_etag");
    m_http_mock_obj->AddResponseHeader("x-bce-version", "test_version");
    m_http_mock_obj->AddResponseHeader("x-bce-meta-key", "x-bce-meta-value");
    m_http_mock_obj->SetResponseData("mock_http_server_test_data");
    m_http_mock_obj->SetResponseCode(200);
    m_http_mock_obj->SetObjectName(bucket_name, object_name);
    m_http_mock_obj->FinishMockSetting();

    std::string object_content;
    EXPECT_EQ(0, m_client->GetObject(bucket_name, object_name, &object_content));
    EXPECT_EQ(object_content, std::string("mock_http_server_test_data"));
}

TEST_F(ClientTest, TestGetObjectRange) {
    std::string bucket_name = "test-bucket";
    std::string object_name = "test_object";
    m_http_mock_obj->AddExpectHeader("Range", "bytes=100-299");
    m_http_mock_obj->AddExpectHeader("x-bce-version", "req_version");
    m_http_mock_obj->AddResponseHeader("ETag", "test_etag");
    m_http_mock_obj->AddResponseHeader("x-bce-version", "test_version");
    m_http_mock_obj->AddResponseHeader("x-bce-meta-key", "x-bce-meta-value");
    m_http_mock_obj->SetResponseData("mock_http_server_test_data");
    m_http_mock_obj->SetResponseCode(206);
    m_http_mock_obj->SetObjectName(bucket_name, object_name);
    m_http_mock_obj->FinishMockSetting();

    GetObjectRequest request(bucket_name, object_name);
    request.SetRange(100, 200);
    request.SetVersion("req_version");

    std::string object_content;
    GetObjectResponse result(&object_content);
    EXPECT_EQ(0, m_client->GetObject(request, &result));
    EXPECT_EQ(object_content, std::string("mock_http_server_test_data"));

    std::map<std::string, std::string> object_meta_data;
    EXPECT_EQ(0, result.GetObjectMetaData(&object_meta_data));
    EXPECT_EQ(1u, object_meta_data.size());
    std::map<std::string, std::string>::iterator it = object_meta_data.find("x-bce-meta-key");
    EXPECT_NE(it, object_meta_data.end());
    EXPECT_EQ(it->second, std::string("x-bce-meta-value"));

    std::string etag;
    EXPECT_EQ(0, result.GetETag(&etag));
    EXPECT_EQ(std::string("test_etag"), etag);
    //EXPECT_EQ(206, result.GetStatusCode());

    std::string version;
    EXPECT_EQ(0, result.GetVersion(&version));
    EXPECT_EQ(std::string("test_version"), version);
}

TEST_F(ClientTest, TestGetObjectFail) {
    std::string bucket_name = "test-bucket";
    std::string object_name = "test_object";
    m_http_mock_obj->AddResponseHeader("ETag", "test_etag");
    m_http_mock_obj->AddResponseHeader("x-bce-version", "test_version");
    m_http_mock_obj->AddResponseHeader("x-bce-meta-key", "x-bce-meta-value");
    std::string error_data = "{\\\"code\\\":\\\"NoSuchKey\\\",\\\"message\\\":\\\"The specified key does not exist.\\\",\\\"requestId\\\":\\\"466cc300-17d8-4417-9e4d-b75e1b5a7e5f\\\"}";
    m_http_mock_obj->SetResponseData(error_data);
    m_http_mock_obj->SetResponseCode(400);
    m_http_mock_obj->SetObjectName(bucket_name, object_name);
    m_http_mock_obj->FinishMockSetting();

    GetObjectRequest request(bucket_name, object_name);

    std::string object_content;
    GetObjectResponse result(&object_content);
    EXPECT_EQ(kBosServiceError, m_client->GetObject(request, &result));
    EXPECT_EQ(std::string("NoSuchKey"), result.GetErrorCode());
    EXPECT_EQ(std::string("The specified key does not exist."), result.GetMessage());
    EXPECT_EQ(std::string("466cc300-17d8-4417-9e4d-b75e1b5a7e5f"), result.GetRequestId());
    //EXPECT_EQ(400, result.GetStatusCode());
}

TEST_F(ClientTest, TestGetObjectBucketNameIllegal) {
    std::string bucket_name = "t";
    std::string object_name = "test_object";

    GetObjectRequest request(bucket_name, object_name);
    std::string object_content;
    GetObjectResponse result(&object_content);
    EXPECT_EQ(kBosIllegalArgument, m_client->GetObject(request, &result));
    // EXPECT_EQ(kBosIllegalArgument, result.GetErrorCode());
    EXPECT_EQ(std::string("bucket name: 't' Illegal"), result.GetMessage());
}

TEST_F(ClientTest, TestPutObject) {
    std::string bucket_name = "test-bucket";
    std::string object_name = "test_object";
    std::string object_content = "test_object_xxxx";
    m_http_mock_obj->SetExpectData(object_content);

    // m_http_mock_obj->AddExpectHeader("Content-MD5", "Ed9fupnnVzLs3k7GiKkaHQ==");
    // m_http_mock_obj->AddExpectHeader("x-bce-crc32", "2uN+rg==");

    m_http_mock_obj->AddResponseHeader("ETag", "test_etag");
    m_http_mock_obj->AddResponseHeader("x-bce-version", "test_version");
    m_http_mock_obj->SetResponseCode(200);
    m_http_mock_obj->SetObjectName(bucket_name, object_name);
    m_http_mock_obj->FinishMockSetting();

    EXPECT_EQ(0, m_client->PutObject(bucket_name, object_name, object_content));
}

TEST_F(ClientTest, TestPutObjectWithMeta) {
    std::string bucket_name = "test-bucket";
    std::string object_name = "test_object";
    std::string object_content = "test_object_xxxx";
    m_http_mock_obj->SetExpectData(object_content);

    // m_http_mock_obj->AddExpectHeader("Content-MD5", "Ed9fupnnVzLs3k7GiKkaHQ==");
    // m_http_mock_obj->AddExpectHeader("x-bce-crc32", "2uN+rg==");

    m_http_mock_obj->AddResponseHeader("x-bce-meta-key1", "x-bce-meta-value1");
    m_http_mock_obj->AddResponseHeader("x-bce-meta-key2", "x-bce-meta-value2");
    m_http_mock_obj->AddResponseHeader("ETag", "test_etag");
    m_http_mock_obj->AddResponseHeader("x-bce-version", "test_version");
    m_http_mock_obj->SetResponseCode(200);
    m_http_mock_obj->SetObjectName(bucket_name, object_name);
    m_http_mock_obj->FinishMockSetting();

    PutObjectRequest request(bucket_name, object_name, object_content);
    request.AddUserMetaData("x-bce-meta-key1", "x-bce-meta-value1");
    request.AddUserMetaData("x-bce-meta-key2", "x-bce-meta-value2");

    PutObjectResponse result;
    EXPECT_EQ(0, m_client->PutObject(request, &result));

    std::string etag;
    EXPECT_EQ(0, result.GetETag(&etag));
    EXPECT_EQ(std::string("test_etag"), etag);

    std::string version;
    EXPECT_EQ(0, result.GetVersion(&version));
    EXPECT_EQ(std::string("test_version"), version);
    //EXPECT_EQ(200, result.GetStatusCode());
}

TEST_F(ClientTest, TestPutObjectFail) {
    std::string bucket_name = "test-bucket";
    std::string object_name = "test_object";
    std::string object_content = "test_object_xxxx";
    m_http_mock_obj->SetExpectData(object_content);

    m_http_mock_obj->AddResponseHeader("ETag", "test_etag");
    m_http_mock_obj->AddResponseHeader("x-bce-version", "test_version");
    std::string error_data = "{\\\"code\\\":\\\"NoSuchKey\\\",\\\"message\\\":\\\"The specified key does not exist.\\\",\\\"requestId\\\":\\\"466cc300-17d8-4417-9e4d-b75e1b5a7e5f\\\"}";
    m_http_mock_obj->SetResponseData(error_data);
    m_http_mock_obj->SetResponseCode(400);
    m_http_mock_obj->SetObjectName(bucket_name, object_name);
    m_http_mock_obj->FinishMockSetting();

    PutObjectRequest request(bucket_name, object_name, object_content);
    request.AddUserMetaData("x-bce-meta-key1", "x-bce-meta-value1");
    request.AddUserMetaData("x-bce-meta-key2", "x-bce-meta-value2");

    PutObjectResponse result;
    EXPECT_EQ(kBosServiceError, m_client->PutObject(request, &result));
    EXPECT_EQ(std::string("NoSuchKey"), result.GetErrorCode());
    EXPECT_EQ(std::string("The specified key does not exist."), result.GetMessage());
    EXPECT_EQ(std::string("466cc300-17d8-4417-9e4d-b75e1b5a7e5f"), result.GetRequestId());
    //EXPECT_EQ(400, result.GetStatusCode());
}

TEST_F(ClientTest, TestPutObjectObjectNameIllegal) {
    std::string bucket_name = "test-bucket";
    std::string object_name = "test_object";
    for (int i = 0; i < 8; i++) {
        object_name = object_name + object_name;
    }
    std::string object_content = "test_object_xxxx";

    PutObjectRequest request(bucket_name, object_name, object_content);
    PutObjectResponse result;
    EXPECT_EQ(kBosIllegalArgument, m_client->PutObject(request, &result));
    EXPECT_EQ(std::string("object name: '") + object_name + std::string("' Illegal"), result.GetMessage());
}
}
}
