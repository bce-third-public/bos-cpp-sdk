#include "util/authorization_util.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>

#include "util/string_util.h"
#include "util/time_util.h"
namespace bce {
namespace bos {
#define kBceRequestHeaderPrefix "x-bce-"
#define kBceRequestHeaderPrefixLength 6

AuthorizationGenerator::AuthorizationGenerator(const std::string &ak,
        const std::string sk, int version) {
    m_ak = ak;  //
    m_sk = sk;
    m_version = version;
    m_signed_headers_keys.insert("host");
    m_exclusive_query_item_key_set.insert("authorization");
    m_signed_headers_keys.insert("content-length");
    m_signed_headers_keys.insert("content-type");
    m_signed_headers_keys.insert("content-md5");
}

int AuthorizationGenerator::GenerateAuthorizationString(const std::string &http_method, const std::string &uri,
            const std::map<std::string, std::string> &query_string,
            const std::set<std::string> &signed_headers,
            const std::map<std::string, std::string> &headers,
            const std::string &encoding,
            int expiration_period_in_seconds, std::string *authorization_string) const {
    std::string utc_time_now = TimeUtil::NowUtcTime();

    std::string session_key = GenerateSessionKey(utc_time_now, expiration_period_in_seconds);

    std::string signature;
    if (GenerateSignature(http_method, uri, query_string, signed_headers,
                headers, encoding, &signature)) {
        return -1;
    }

    Authorization authorization;
    authorization.SetVersion(m_version);
    authorization.SetAk(m_ak);
    authorization.SetTimestamp(utc_time_now);
    authorization.SetExpirationPeriodInSeconds(expiration_period_in_seconds);

    /*
    std::set<std::string> signed_headers;
    for (std::map<std::string, std::string>::const_iterator cit = headers.begin();
            cit != headers.end(); cit++) {
        std::string lower_key = StringUtil::ToLower(StringUtil::Trim(cit->first));
        if (NeedIncludeInSignature(lower_key)) {
            signed_headers.insert(lower_key);
        }
    }
    */
    authorization.SetSignedHeaders(signed_headers);

    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    printf("%s\n", session_key.c_str());
    printf("%s\n", signature.c_str());
    printf("%s\n", StringUtil::Sha256Hex(signature, session_key).c_str());
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    authorization.SetSignature(StringUtil::Sha256Hex(signature, session_key));

    authorization.SerializeToString(authorization_string);

    return 0;
}


int AuthorizationGenerator::GenerateSignature(const std::string &http_method,
            const std::string &uri, const std::map<std::string, std::string> &query_string,
            const std::set<std::string> &signed_headers,
            const std::map<std::string, std::string> &headers,
            const std::string &encoding,
            std::string *signature) const {
    std::stringstream ss;
    ss << StringUtil::ToUpper(http_method) << "\n";

    UriCanonicalization(uri, encoding, &ss);
    ss << "\n";

    QueryStringCanonicalization(query_string, encoding, &ss);
    ss << "\n";

    HeadersCanonicalization(signed_headers, headers, encoding, &ss);

    signature->assign(ss.str());

    return 0;
}

int AuthorizationGenerator::UriCanonicalization(const std::string &uri,
        const std::string &encoding, std::stringstream *stream) const {
    (*stream) << StringUtil::UriEncode(uri, false);
    return 0;
}

int AuthorizationGenerator::QueryStringCanonicalization(
        const std::map<std::string, std::string> &query_string_items,
        const std::string &encoding, std::stringstream *stream) const {
    std::stringstream &ss = *stream;
    std::vector<std::string> canonical_query_string_vector;
    canonical_query_string_vector.reserve(query_string_items.size());

    for (std::map<std::string, std::string>::const_iterator it = query_string_items.begin();
            it != query_string_items.end(); it++) {
        std::string key = StringUtil::Trim(it->first);
        std::string value = StringUtil::Trim(it->second);
        if (key == "") {
            continue;
        }

        if (!NeedQueryStringItemIncludeInSignature(key)) {
            continue;
        }

        canonical_query_string_vector.push_back(NormalizeString(key, encoding)
                + "=" + NormalizeString(value, encoding));
    }

    std::sort(canonical_query_string_vector.begin(), canonical_query_string_vector.end());
    bool has_item = false;
    for (uint32_t i = 0; i < canonical_query_string_vector.size(); i++) {
        if (has_item) {
            ss << "&";
        }

        has_item = true;

        ss << canonical_query_string_vector[i];
    }

    return 0;
}

int AuthorizationGenerator::HeadersCanonicalization(const std::set<std::string> &signed_headers,
        const std::map<std::string, std::string> &headers,
        const std::string &encoding,std::stringstream *stream) const {
    std::stringstream &ss = *stream;
    std::vector<std::string> canonical_headers;
    canonical_headers.reserve(headers.size());
    for (std::map<std::string, std::string>::const_iterator cit = headers.begin();
            cit != headers.end(); cit++) {
        std::string key = StringUtil::ToLower(NormalizeString(StringUtil::Trim(cit->first), encoding));
        if (key == "") {
            continue;
        }

        if (signed_headers.size() != 0) {
            if (signed_headers.find(key) == signed_headers.end()) {
                continue;
            }
        }
        else if (!NeedHeaderIncludeInSignature(key)) {
            continue;
        }

        canonical_headers.push_back(key + ":" + NormalizeString(StringUtil::Trim(cit->second), encoding));
    }

    std::sort(canonical_headers.begin(), canonical_headers.end());

    for (uint32_t i = 0; i < canonical_headers.size(); i++) {
        if (i != 0) {
            ss << "\n";
        }
        ss << canonical_headers[i];
    }

    return 0;
}

bool AuthorizationGenerator::NeedHeaderIncludeInSignature(const std::string &key) const {
    if (m_signed_headers_keys.find(key) != m_signed_headers_keys.end()) {
        return true;
    }

    if (key.compare(0, kBceRequestHeaderPrefixLength, kBceRequestHeaderPrefix)) {
        return false;
    }

    return true;
}

bool AuthorizationGenerator::NeedQueryStringItemIncludeInSignature(const std::string &key) const {
    if (m_exclusive_query_item_key_set.find(key) == m_exclusive_query_item_key_set.end()) {
        return true;
    }

    return false;
}

std::string AuthorizationGenerator::NormalizeString(const std::string &str,
        const std::string &encoding) const {
    std::string utf8_string;
    if (StringUtil::Icnov(str, encoding, "UTF-8", &utf8_string)) {
        return "";
    }

    return StringUtil::UriEncode(utf8_string);
}

std::string AuthorizationGenerator::GenerateSessionKey(const std::string &utc_timestamp, int expiration_period_in_seconds) const {
    std::stringstream ss;
    ss << "bce-auth-v" << m_version << "/" << m_ak << "/" << utc_timestamp << "/" << expiration_period_in_seconds;
    printf("xxx:%s, session_key:%s, sk:%s\n",
            ss.str().c_str(), StringUtil::Sha256Hex(ss.str(), m_sk).c_str(), m_sk.c_str());

    return StringUtil::Sha256Hex(ss.str(), m_sk);
}

int Authorization::SerializeToString(std::string *str) const {
    std::stringstream ss;
    ss << "bce-auth-v" << m_version << "/"
        << m_ak << "/"
        << m_utc_timestamp << "/"
        << m_expiration_period_in_seconds << "/";

    for (std::set<std::string>::const_iterator cit = m_signed_headers.begin();
            cit != m_signed_headers.end(); cit++) {
        if (cit != m_signed_headers.begin()) {
            ss << ";";
        }

        ss << *cit;
    }

    ss << "/";
    ss << m_signature;

    str->assign(ss.str());

    return 0;
}

int Authorization::ParseFromString(const std::string &str) {
    std::vector<std::string> str_items;
    StringUtil::Split(str, '/', &str_items);

    if (str_items.size() != 6) {
        return -1;
    }

    const char *version_prefix = "bce-auth-v";
    int version_prefix_length = strlen(version_prefix);
    if (str_items[0].compare(0, version_prefix_length, version_prefix) != 0) {
        return -1;
    }
    m_version = atoi(str_items[0].c_str() + version_prefix_length);

    m_ak = str_items[1];
    m_utc_timestamp = str_items[2];
    m_expiration_period_in_seconds = atoi(str_items[3].c_str());
    StringUtil::Split(str_items[4], ';', &m_signed_headers);
    m_signature = str_items[5];

    return 0;
}
}
}
