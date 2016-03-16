#ifndef INF_DS_BOSS_SDK_C_SRC_MEMORY_STREAM_H_
#define INF_DS_BOSS_SDK_C_SRC_MEMORY_STREAM_H_

#include <string.h>

#include "util/stream.h"
#include "util/common_def.h"

BEGIN_C_SDK_NAMESPACE
class MemoryInputStream : public bce::bos::InputStream {
public:
    MemoryInputStream(const void *buffer, int64_t size) {
        m_buffer = buffer;
        m_size = size;
        m_pos = 0;
    }

    virtual ~MemoryInputStream() {
    }

    virtual int64_t Read(int64_t size, std::string *data) {
        int64_t real_size = CalculateRealCopySize(size);
        data->assign(reinterpret_cast<const char *>(m_buffer) + m_pos, real_size);

        m_pos += real_size;
        return real_size;
    }

    virtual int64_t Read(char *buffer, int64_t size) {
        int64_t real_size = CalculateRealCopySize(size);
        memcpy(buffer, reinterpret_cast<const char *>(m_buffer) + m_pos, real_size);

        m_pos += real_size;
        return real_size;
    }

    virtual int64_t GetSize() const {
        return m_size;
    }

    virtual int64_t Seek(int64_t pos) {
        if (pos < 0 || pos > m_size) {
            return -1;
        }
        m_pos = pos;
        return pos;
    }

    virtual int64_t GetPos() const {
        return m_pos;
    }

private:
    const void *m_buffer;
    int64_t m_size;
    int64_t m_pos;

    int64_t CalculateRealCopySize(int64_t req_size) {
        int64_t left_data_size = m_size - m_pos;
        return left_data_size < req_size ? left_data_size : req_size;
    }
};

class MemoryOutputStream : public bce::bos::OutputStream {
public:
    MemoryOutputStream(void *buffer, int64_t size) {
        m_buffer = buffer;
        m_size = size;
        m_pos = 0;
    }

    virtual ~MemoryOutputStream() {
    }

    virtual int64_t Write(const std::string &data) {
        return Write(data.data(), data.size());
    }

    virtual int64_t Write(const char *buffer, int64_t size) {
        if (size + m_pos > m_size) {
            return -1;
        }

        memcpy(reinterpret_cast<char *>(m_buffer) + m_pos, buffer, size);
        m_pos += size;

        return size;
    }

    std::string GetBufferString() const {
        return std::string(reinterpret_cast<char *>(m_buffer), m_pos);
    }

    virtual int64_t Reserve(int64_t size) {
        if (size <= m_size) {
            return 0;
        }

        return -1;
    }

    virtual int64_t Read(uint64_t start, int64_t length, std::string *data) const {
        if (start > static_cast<uint64_t>(m_pos)) {
            return 0;
        }

        int64_t left_length = m_pos - start;
        if (length > left_length || length < 0) {
            length = left_length;
        }

        data->assign(reinterpret_cast<char *>(m_buffer) + start, length);
        return length;
    }

private:
    void *m_buffer;
    int64_t m_size;
    int64_t m_pos;
};

class StringOutputStream : public bce::bos::OutputStream {
public:
    StringOutputStream(std::string *buffer) {
        m_buffer = buffer;
    }

    virtual int64_t Write(const std::string &data) {
        return Write(data.data(), data.size());
    }

    virtual int64_t Write(const char *buffer, int64_t size) {
        m_buffer->append(buffer, size);

        return size;
    }

    virtual int64_t Reserve(int64_t size) {
        m_buffer->reserve(size);
        return 0;
    }

    virtual int64_t Read(uint64_t start, int64_t length, std::string *data) const {
        if (start > m_buffer->size()) {
            return 0;
        }

        int64_t left_length = m_buffer->size() - start;
        if (length > left_length || length < 0) {
            length = left_length;
        }

        data->assign(m_buffer->c_str() + start, length);
        return length;
    }

private:
    std::string *m_buffer;
};
END_C_SDK_NAMESPACE

#endif // INF_DS_BOSS_SDK_C_SRC_MEMORY_STREAM_H_
