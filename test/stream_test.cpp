/*
 *    Author:       Can Cui(cuican01@baidu.com)
 *    Copyright:    Copyright 2013, Baidu Inc.
 *    Description:
 */

// Copyright 2013, Baidu Inc.
// Author: Can Cui <cuican01@baidu.com>


#define private public
#include "util/memory_stream.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

BEGIN_C_SDK_NAMESPACE
class MemoryInputStreamTest : public testing::Test {
public:
    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }

    void SetUp() {
        m_buffer = new char[m_size];
        strcpy(m_buffer, "123456789");
        m_memory_input_stream = new MemoryInputStream(m_buffer, m_size - 1);
    }

    void TearDown() {
        delete []m_buffer;
        delete m_memory_input_stream;
    }

protected:
    static const int m_size = 10;
    char *m_buffer;
    MemoryInputStream *m_memory_input_stream;
};

class MemoryOutputStreamTest : public testing::Test {
public:
    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }

    void SetUp() {
        m_buffer = new char[m_size];
        m_memory_output_stream = new MemoryOutputStream(m_buffer, m_size - 1);
    }

    void TearDown() {
        delete []m_buffer;
        delete m_memory_output_stream;
    }

protected:
    static const int m_size = 10;
    char *m_buffer;
    MemoryOutputStream *m_memory_output_stream;
};

class StringOutputStreamTest : public testing::Test {
public:
    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }

    void SetUp() {
        m_string_output_stream = new StringOutputStream(&m_buffer);
    }

    void TearDown() {
        delete m_string_output_stream;
    }

protected:
    std::string m_buffer;
    StringOutputStream *m_string_output_stream;
};

TEST_F(MemoryInputStreamTest, ReadString) {
    std::string data;
    EXPECT_EQ(4, m_memory_input_stream->Read(4, &data));
    EXPECT_EQ(std::string("1234"), data);
}

TEST_F(MemoryInputStreamTest, ReadStringTwice) {
    std::string data;
    EXPECT_EQ(4, m_memory_input_stream->Read(4, &data));
    EXPECT_EQ(std::string("1234"), data);
    EXPECT_EQ(3, m_memory_input_stream->Read(3, &data));
    EXPECT_EQ(std::string("567"), data);
}

TEST_F(MemoryInputStreamTest, ReadStringAll) {
    std::string data;
    EXPECT_EQ(9, m_memory_input_stream->Read(9, &data));
    EXPECT_EQ(std::string("123456789"), data);
}

TEST_F(MemoryInputStreamTest, ReadStringTooMany) {
    std::string data;
    EXPECT_EQ(9, m_memory_input_stream->Read(100, &data));
    EXPECT_EQ(std::string("123456789"), data);
}

TEST_F(MemoryInputStreamTest, ReadCStr) {
    char buffer[10];
    EXPECT_EQ(4, m_memory_input_stream->Read(buffer, 4));
    EXPECT_EQ(0, memcmp(buffer, "1234", 4));
}

TEST_F(MemoryInputStreamTest, GetSize) {
    EXPECT_EQ(9, m_memory_input_stream->GetSize());
}

TEST_F(MemoryInputStreamTest, Seek) {
    std::string data;
    EXPECT_EQ(4, m_memory_input_stream->Read(4, &data));
    EXPECT_EQ(std::string("1234"), data);
    EXPECT_EQ(4, m_memory_input_stream->GetPos());
    EXPECT_EQ(0, m_memory_input_stream->Seek(0));
    EXPECT_EQ(0, m_memory_input_stream->GetPos());
    EXPECT_EQ(3, m_memory_input_stream->Read(3, &data));
    EXPECT_EQ(std::string("123"), data);

    EXPECT_EQ(-1, m_memory_input_stream->Seek(100));
}

TEST_F(MemoryOutputStreamTest, Write) {
    EXPECT_EQ(4, m_memory_output_stream->Write("1234"));
    EXPECT_EQ(std::string("1234"), m_memory_output_stream->GetBufferString());
    EXPECT_EQ(3, m_memory_output_stream->Write("567"));
    EXPECT_EQ(std::string("1234567"), m_memory_output_stream->GetBufferString());
    EXPECT_EQ(-1, m_memory_output_stream->Write("8910"));
}

TEST_F(MemoryOutputStreamTest, Reserve) {
    EXPECT_EQ(0, m_memory_output_stream->Reserve(3));
    EXPECT_EQ(-1, m_memory_output_stream->Reserve(100));
}

TEST_F(MemoryOutputStreamTest, Read) {
    EXPECT_EQ(4, m_memory_output_stream->Write("1234"));
    std::string data;
    EXPECT_EQ(2, m_memory_output_stream->Read(1, 2, &data));
    EXPECT_EQ(std::string("23"), data);

    EXPECT_EQ(3, m_memory_output_stream->Read(1, 10, &data));
    EXPECT_EQ(std::string("234"), data);

    EXPECT_EQ(0, m_memory_output_stream->Read(10, 2, &data));
}

TEST_F(StringOutputStreamTest, Write) {
    EXPECT_EQ(4, m_string_output_stream->Write("1234"));
    EXPECT_EQ(std::string("1234"), *(m_string_output_stream->m_buffer));
    EXPECT_EQ(3, m_string_output_stream->Write("567"));
    EXPECT_EQ(std::string("1234567"), *(m_string_output_stream->m_buffer));
}

TEST_F(StringOutputStreamTest, Reserve) {
    EXPECT_EQ(0, m_string_output_stream->Reserve(3));
    EXPECT_EQ(0, m_string_output_stream->Reserve(100));
}

TEST_F(StringOutputStreamTest, Read) {
    EXPECT_EQ(4, m_string_output_stream->Write("1234"));
    std::string data;
    EXPECT_EQ(2, m_string_output_stream->Read(1, 2, &data));
    EXPECT_EQ(std::string("23"), data);

    EXPECT_EQ(3, m_string_output_stream->Read(1, 10, &data));
    EXPECT_EQ(std::string("234"), data);

    EXPECT_EQ(0, m_string_output_stream->Read(10, 2, &data));
}

END_C_SDK_NAMESPACE
