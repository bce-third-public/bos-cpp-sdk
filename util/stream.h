#ifndef INF_DS_BOSS_SDK_C_COMMOM_STREAM_H_
#define INF_DS_BOSS_SDK_C_COMMOM_STREAM_H_
#include <stdint.h>

#include <string>

namespace bce {
namespace bos {
class Stream {
public:
    virtual ~Stream() {
    }

    virtual std::string GetErrorDescription(int error_code) const {
        return "";
    }
};

class InputStream : public Stream {
public:
    virtual ~InputStream() {
    }

    virtual int64_t Read(int64_t size, std::string *data) = 0;
    virtual int64_t Read(char *buffer, int64_t size) = 0;

    virtual int64_t GetSize() const = 0;
    virtual int64_t Seek(int64_t pos) = 0;
    virtual int64_t GetPos() const = 0;
};

class OutputStream : public Stream {
public:
    virtual ~OutputStream() {
    }

    virtual int64_t Write(const std::string &data) = 0;
    virtual int64_t Write(const char *buffer, int64_t size) = 0;
    virtual int64_t Reserve(int64_t size) = 0;

    virtual int64_t Read(uint64_t start, int64_t length, std::string *data) const = 0;
};
}
} // namespace boss

#endif // INF_DS_BOSS_SDK_C_COMMOM_STREAM_H_
