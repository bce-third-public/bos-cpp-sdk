#ifndef INF_DS_BOSS_SDK_C_EXAMPLE_FILE_STREAM_H_
#define INF_DS_BOSS_SDK_C_EXAMPLE_FILE_STREAM_H_

#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "util/stream.h"
namespace bce {
namespace bos {
class FileInputStream : public InputStream {
public:
    FileInputStream(const std::string &file_name) {
        m_file_handle = fopen(file_name.c_str(), "r");
    }

    virtual ~FileInputStream() {
        if (m_file_handle != NULL) {
            fclose(m_file_handle);
            m_file_handle = NULL;
        }
    }

    virtual int64_t Read(int64_t size, std::string *data) {
        char *buffer = new char[size];
        int64_t data_len = Read(buffer, size);
        if (data_len > 0) {
            data->assign(buffer, data_len);
        }

        delete []buffer;
        return data_len;
    }

    virtual int64_t Read(char *buffer, int64_t size) {
        if (m_file_handle == NULL) {
            return kOpenFileFail;
        }

        int64_t ret = fread(buffer, 1, size, m_file_handle);
        if (ret < 0) {
            return errno;
        }

        return ret;
    }

    virtual int64_t GetSize() const {
        if (m_file_handle == NULL) {
            return kOpenFileFail;
        }

        struct stat stat_buffer;
        int ret = fstat(fileno(m_file_handle), &stat_buffer);
        if (ret != 0) {
            return errno;
        }

        return stat_buffer.st_size;
    }

    virtual int64_t Seek(int64_t pos) {
        if (m_file_handle == NULL) {
            return kOpenFileFail;
        }

        int ret = fseek(m_file_handle, pos, SEEK_SET);
        if (ret != 0) {
            return errno;
        }

        return ret;
    }

    virtual int64_t GetPos() const {
        int64_t pos =  ftell(m_file_handle);
        if (pos < 0) {
            return errno;
        }

        return pos;
    }

    virtual std::string GetErrorDescription(int error_code) const {
        if (error_code == kOpenFileFail) {
            return "Open File fail";
        }

        const int buffer_size = 1024;
        char buffer[buffer_size];

        if (strerror_r(error_code, buffer, buffer_size)) {
            return "Unknown error";
        }

        return std::string(buffer);
    }

private:
    static const int kOpenFileFail = -1001;
    FILE *m_file_handle;
    int64_t m_file_size;
};

class FileOutputStream : public OutputStream {
public:
    FileOutputStream(const std::string &file_name) {
        m_file_handle = fopen(file_name.c_str(), "w");
    }

    virtual ~FileOutputStream() {
        if (m_file_handle != NULL) {
            fclose(m_file_handle);
            m_file_handle = NULL;
        }
    }

    virtual int64_t Write(const std::string &data) {
        return Write(data.c_str(), data.size());
    }

    virtual int64_t Write(const char *buffer, int64_t size) {
        if (m_file_handle == NULL) {
            return kOpenFileFail;
        }

        return fwrite(buffer, 1, size, m_file_handle);
    }

    virtual int64_t Reserve(int64_t size) {
        return 0;
    }

    virtual int64_t Read(uint64_t start, int64_t length, std::string *data) const {
        return kOperationNotAllow;
    }

    virtual std::string GetErrorDescription(int error_code) const {
        if (error_code == kOpenFileFail) {
            return "Open File fail";
        }

        if (error_code == kOperationNotAllow) {
            return "operation not allow";
        }

        const int buffer_size = 1024;
        char buffer[buffer_size];

        if (strerror_r(error_code, buffer, buffer_size)) {
            return "Unknown error";
        }

        return std::string(buffer);
    }

private:
    static const int kOpenFileFail = -1001;
    static const int kOperationNotAllow = -1002;

    FILE *m_file_handle;
};
}
}

#endif // INF_DS_BOSS_SDK_C_EXAMPLE_FILE_STREAM_H_
