/*
 *    Author:       Can Cui(cuican01@baidu.com)
 *    Copyright:    Copyright 2013, Baidu Inc.
 *    Description:  
 */
#include "util/encrypt_util.h"

#include "curl/curl.h"
#include "openssl/bio.h"
#include "openssl/buffer.h"
#include "openssl/evp.h"
#include "openssl/hmac.h"
#include "openssl/md5.h"

BEGIN_C_SDK_NAMESPACE
int EncryptUtil::Hmac(int type, const std::string &key,
        const std::string &data, std::string *result) {
    const EVP_MD *evp_md = NULL;
    switch (type) {
    case HMAC_TYPE_SHA1:
        evp_md = EVP_sha1();
        break;
    default:
        return -1;
    }

    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int md_len = 0;
    if (HMAC(evp_md,
                reinterpret_cast<const unsigned char *>(key.data()), key.size(),
                reinterpret_cast<const unsigned char *>(data.data()), data.size(),
                md, &md_len) == NULL) {
        return -1;
    }

    result->assign(reinterpret_cast<char *>(md), md_len);

    return 0;
}

int EncryptUtil::Base64Encode(const std::string &data, std::string *result) {
    result->resize((data.size() / 3 + 1) * 4);

    int encode_size = EVP_EncodeBlock(reinterpret_cast<unsigned char *>(
                const_cast<char *>(result->data())),
            reinterpret_cast<const unsigned char *>(data.data()), data.size());

    result->resize(encode_size);

    return 0;
}

int EncryptUtil::UrlEncode(const std::string &data, std::string *result) {
    char *result_c_str = curl_escape(data.c_str(), data.size());
    result->assign(result_c_str);
    curl_free(result_c_str);
    return 0;
}
END_C_SDK_NAMESPACE
