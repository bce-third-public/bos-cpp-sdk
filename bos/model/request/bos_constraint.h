#ifndef INF_DS_BOSS_SDK_C_REQUEST_BOS_CONSTRAINT_H_
#define INF_DS_BOSS_SDK_C_REQUEST_BOS_CONSTRAINT_H_
#include <sys/types.h>
#include <regex.h>

#include "bos/model/request/request.h"
#include "util/exception.h"
namespace bce {
namespace bos {
class BosConstraint {
public:
    static bool CheckBucketName(const std::string &bucket_name) {
        if (bucket_name.size() < 3 || bucket_name.size() > 63) {
            std::stringstream ss;
            ss << "bucket name: '" << bucket_name << "' Illegal";
            throw BosIllegalArgumentException(ss.str());
            return false;
        }

        regex_t bucket_name_regex;
        if (regcomp(&bucket_name_regex, "^[a-z0-9][-0-9a-z]*[a-z0-9]$", REG_EXTENDED)) {
            throw BosClientException("Unknwon Client Exception");
        }

        bool ret = CheckNameByReg(&bucket_name_regex, bucket_name);
        regfree(&bucket_name_regex);

        if (!ret) {
            std::stringstream ss;
            ss << "bucket name: '" << bucket_name << "' Illegal";
            throw BosIllegalArgumentException(ss.str());
        }
        return ret;
    }

    static bool CheckObjectName(const std::string &object_name) {
        if (object_name.size() > 256) {
            std::stringstream ss;
            ss << "object name: '" << object_name << "' Illegal";
            throw BosIllegalArgumentException(ss.str());
        }

        regex_t object_name_regex;
        if (regcomp(&object_name_regex, "^.*$", REG_EXTENDED)) {
            throw BosClientException("Unknwon Client Exception");
        }

        bool ret = CheckNameByReg(&object_name_regex, object_name);
        regfree(&object_name_regex);
        if (!ret) {
            std::stringstream ss;
            ss << "object name: '" << object_name << "' Illegal";
            throw BosIllegalArgumentException(ss.str());
        }

        return ret;
    }

private:
    static bool CheckNameByReg(const regex_t *regex, const std::string &name) {
        int ret = regexec(regex, name.c_str(), 0, NULL, 0);
        if (!ret) {
            return true;
        }

        if (ret == REG_NOMATCH) {
            return false;
        }

        char error_buffer[1024];
        regerror(ret, regex, error_buffer, sizeof(error_buffer));
        throw BosClientException(std::string(error_buffer));
    }

};
}
}

#endif // INF_DS_BOSS_SDK_C_REQUEST_BOS_CONSTRAINT_H_
