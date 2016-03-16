#ifndef INF_DS_BOSS_SDK_C_SRC_EXCEPTION_H_
#define INF_DS_BOSS_SDK_C_SRC_EXCEPTION_H_
#include <stdint.h>
#include <stdio.h>

#include <string>

#include "bos/api.h"
#include "util/common_def.h"

BEGIN_C_SDK_NAMESPACE
class BosBaseException {
public:
    BosBaseException(const std::string &message) {
        m_message = message;
    }

    virtual ~BosBaseException() {
    }

    std::string GetMessage() const {
        return m_message;
    }

    virtual int GetErrorCode() const = 0;

private:
    std::string m_message;
};

class BosClientException : public BosBaseException {
public:
    BosClientException(const std::string &message) : BosBaseException(message) {}
    virtual ~BosClientException() {
    }

    virtual int GetErrorCode() const {
        return bce::bos::kBosClientError;
    }

};

class BosIllegalArgumentException : public BosBaseException {
public:
    BosIllegalArgumentException(const std::string &message) : BosBaseException(message) {}
    virtual ~BosIllegalArgumentException() {
    }

    virtual int GetErrorCode() const {
        return bce::bos::kBosIllegalArgument;
    }
};

class BosServiceException : public BosBaseException {
public:
    BosServiceException(const std::string &message) : BosBaseException(message) {
    }
    virtual ~BosServiceException() {
    }

    virtual int GetErrorCode() const {
        return bce::bos::kBosServiceError;
    }

private:
};
END_C_SDK_NAMESPACE
#endif // INF_DS_BOSS_SDK_C_SRC_EXCEPTION_H_
