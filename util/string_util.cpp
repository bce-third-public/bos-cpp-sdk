#include "util/string_util.h"
#include <ctype.h>
#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "openssl/bio.h"
#include "openssl/buffer.h"
#include "openssl/evp.h"
#include "openssl/hmac.h"
#include "openssl/md5.h"
#include "curl/curl.h"

namespace bce {
namespace bos {
int StringUtil::Split(const std::string &str, char delimiter,
            std::vector<std::string> *result) {
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        result->push_back(item);
    }

    return 0;
}

int StringUtil::Split(const std::string &str, char delimiter,
            std::set<std::string> *result) {
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        result->insert(item);
    }

    return 0;
}

int StringUtil::Split(const std::string &str,
            char major_delimiter, char minor_delimiter,
            std::map<std::string, std::string> *result) {
    std::vector<std::string> major_result;
    if (Split(str, major_delimiter, &major_result)) {
        return -1;
    }

    for (uint32_t i = 0u; i < major_result.size(); i++) {
        std::vector<std::string> tmp;
        if (Split(major_result[i], minor_delimiter, &tmp)) {
            return -1;
        }

        if (tmp.size() == 0 || tmp.size() >= 3) {
            return -1;
        }

        if (tmp.size() == 1) {
            result->insert(std::map<std::string, std::string>::value_type(tmp[0], ""));
        } else {
            result->insert(std::map<std::string, std::string>::value_type(tmp[0], tmp[1]));
        }
    }

    return 0;
}

int StringUtil::Trim(const std::string &src, std::string *out, char c) {
    int start_pos = 0;
    int length = src.size();

    for (std::string::const_iterator it = src.begin(); it != src.end(); it++) {
        if (*it != c) {
            break;
        }

        start_pos++;
        length--;
    }

    for (std::string::const_reverse_iterator it = src.rbegin(); it != src.rend(); it++) {
        if (*it != c) {
            break;
        }

        length--;
    }

    *out = src.substr(start_pos, length);

    return 0;
}

int StringUtil::ToLower(const std::string &src, std::string *lower) {
    lower->assign(src);
    std::transform(src.begin(), src.end(), lower->begin(), tolower);

    return 0;
}

int StringUtil::ToUpper(const std::string &src, std::string *upper) {
    upper->assign(src);
    std::transform(src.begin(), src.end(), upper->begin(), toupper);

    return 0;
}

std::string StringUtil::UriEncode(const std::string &input, bool encode_slash) {

    std::string output_string;
    CURL* curl = curl_easy_init();

    if (curl) {
        if (encode_slash) {
            char* output = curl_easy_escape(curl, input.c_str(), input.length());
            output_string = output;
            curl_free(output);
        } else {
            std::string left_string = input;
            size_t pos = 0;
            while ((pos = left_string.find("/")) != std::string::npos) {
                std::string sub_string = left_string.substr(0, pos);
                if (sub_string.length()) {
                    char* output = curl_easy_escape(curl, sub_string.c_str(), sub_string.length());
                    output_string += std::string(output) + "/";
                    curl_free(output);
                }
                else {
                    output_string += "/";
                }
                left_string = left_string.substr(pos + 1, left_string.length() - pos - 1);
            }
            if (left_string.length() != 0) {
                char * output = curl_easy_escape(curl, left_string.c_str(), left_string.length());
                output_string += output;
                curl_free(output);
            }

        }
        curl_easy_cleanup(curl);
    }

    return output_string;
}

int StringUtil::UriDecode(const std::string &input, std::string *out) {
    const unsigned char *str = reinterpret_cast<const unsigned char *>(input.c_str());


    const int kNormalState = 0;
    const int kPercentAppearState = 1;
    const int kPercentAndHexCharAppearState = 2;
    const int kErrorState = 3;

    int state = kNormalState;
    uint32_t iter = 0;
    std::stringstream ss;

    while (true) {
        if (iter >= input.size()) {
            break;
        }

        if (state == kErrorState) {
            break;
        }

        unsigned char c = str[iter];
        unsigned char o;

        switch (state) {
            case kNormalState:
                if (c == '%') {
                    state = kPercentAppearState;
                } else {
                    if (isalnum(c) || c == '.' || c == '~' || c == '-' || c == '_' || c == '/'){
                        ss << c;
                    } else {
                        state = kErrorState;
                    }
                }

                break;
            case kPercentAppearState:
                if (IsHexChar(c)) {
                    o = ToBin(c) << 4;
                    state = kPercentAndHexCharAppearState;
                } else {
                    state = kErrorState;
                }
                break;
            case kPercentAndHexCharAppearState:
                if (IsHexChar(c)) {
                    o += ToBin(c);
                    ss << o;
                    state = kNormalState;
                } else {
                    state = kErrorState;
                }
                break;
            case kErrorState:
                return -1;
            default:
                state = kErrorState;
        }

        iter++;
    }

    if (state != kNormalState) {
        return -1;
    }

    out->assign(ss.str());

    return 0;
}

std::string StringUtil::ToHex(unsigned char c) {
    const char *hex = "0123456789ABCDEF";
    std::string result;
    result.reserve(2);
    result.push_back(hex[c >> 4]);
    result.push_back(hex[c & 0xf]);

    return result;
}

std::string StringUtil::ToHex(const std::string &src) {
    const char *hex = "0123456789ABCDEF";
    const unsigned char *c_str = reinterpret_cast<const unsigned char *>(src.c_str());

    std::stringstream ss;
    for (uint32_t i = 0; i < src.size(); i++) {
        unsigned char c = c_str[i];
        ss << hex[c >> 4] << hex[c & 0xf];
    }

    return ss.str();
}

std::string StringUtil::ToUpper(const std::string &src) {
    std::string upper;
    ToUpper(src, &upper);
    return upper;
}

std::string StringUtil::ToLower(const std::string &src) {
    std::string lower;
    ToLower(src, &lower);
    return lower;
}

std::string StringUtil::Trim(const std::string &src) {
    const char *c_str = src.c_str();

    int start = 0;
    int end = src.size() - 1;
    int length = src.size();

    for (; start < length; start++) {
        if (!isblank(c_str[start])) {
            break;
        }
    }

    for (; end >= start; end--) {
        if (!isblank(c_str[end])) {
            break;
        }
    }

    if (start > end) {
        return "";
    }

    return std::string(c_str + start, end - start + 1);
}

std::string StringUtil::Sha256Hex(const std::string &src, const std::string &sk) {
    const EVP_MD *evp_md = EVP_sha256();
    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int md_len = 0;
    if (HMAC(evp_md,
                reinterpret_cast<const unsigned char *>(sk.data()), sk.size(),
                reinterpret_cast<const unsigned char *>(src.data()), src.size(),
                md, &md_len) == NULL) {
        return "";
    }

    return ToLower(ToHex(std::string(reinterpret_cast<char *>(md), md_len)));
}

int StringUtil::Icnov(const std::string &src, const std::string &from_encode,
            const std::string &to_encode, std::string *dest) {
    dest->assign(src);
    return 0;
}

bool StringUtil::IsHexChar(unsigned char c) {
    if ('0' <= c && c <= '9') {
        return true;
    }

    if ('a' <= c && c <= 'f') {
        return true;
    }

    if ('A' <= c && c <= 'F') {
        return true;
    }

    return false;
}

unsigned char StringUtil::ToBin(unsigned char c) {
    if ('0' <= c && c <= '9') {
        return c - '0';
    }

    if ('a' <= c && c <= 'f') {
        return c - 'a' + 10;
    }

    if ('A' <= c && c <= 'F') {
        return c - 'A' + 10;
    }

    return 0xff;
}
}
}
