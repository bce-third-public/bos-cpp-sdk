/*
 *    Author:       Can Cui(cuican01@baidu.com)
 *    Copyright:    Copyright 2013, Baidu Inc.
 *    Description:
 */

#ifndef INF_DS_BOSS_SDK_C_SRC_ENCRYPT_UTIL_H_
#define INF_DS_BOSS_SDK_C_SRC_ENCRYPT_UTIL_H_
#include <stdint.h>
#include <string>
#include <vector>
#include "util/common_def.h"

BEGIN_C_SDK_NAMESPACE
class EncryptUtil {
public:
    static const int HMAC_TYPE_SHA1 = 1;
    static int Hmac(int type, const std::string &key, const std::string &data, std::string *result);

    static int Base64Encode(const std::string &data, std::string *result);

    static int UrlEncode(const std::string &data, std::string *result);

private:
    static const uint32_t kMd5BinaryLength = 16;
    static const uint32_t kMd5StringLength = 16;
};
END_C_SDK_NAMESPACE
#endif // INF_DS_BOSS_SDK_C_SRC_ENCRYPT_UTIL_H_

