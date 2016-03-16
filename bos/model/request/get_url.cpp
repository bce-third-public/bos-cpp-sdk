/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file ./get_url.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/31 12:53:25
 * @brief 
 *  
 **/


#include "bos/model/request/get_url.h"
#include <sstream>
#include "util/string_util.h"
#include "util/authorization_util.h"

namespace bce {
namespace bos {

std::string GetUrlRequest::GetRelativeUrl() {
    std::stringstream ss;
    if(m_bucket == "") {
        ss << "/v1";
    } else if(m_object == "") {
        ss << "/v1/" << m_bucket;
    } else {
        ss << "/v1/" << m_bucket << "/" << m_object;
    }

    return ss.str();
}

int GetUrlRequest::GenerateAuthorizationString(const std::string &access_key_id, const std::string &access_key_secret, std::string *authorization_string) {
    AuthorizationGenerator *auth = new AuthorizationGenerator(access_key_id, access_key_secret);
    
    int ret = auth->GenerateAuthorizationString(GetMethod(), GetRelativeUrl(), m_query_strings, 
            m_signed_headers, m_headers, "GBK", m_expiration_period_in_seconds, authorization_string);
    delete auth;
    return ret;
}
int GetUrlRequest::BuildUrl(const std::string &access_key_id, const std::string &access_key_secret, std::string *url) {
    
    std::string authorization_string;
    if(GenerateAuthorizationString(access_key_id, access_key_secret, &authorization_string)) {
        return -1;
    }
    AddQueryString("authorization", authorization_string);

    std::stringstream ss;
    ss << GetMethod() << " " << "http://" << m_host << StringUtil::UriEncode(GetRelativeUrl(), false);

    ss << "?";
    std::map<std::string, std::string>::const_iterator it = m_query_strings.begin();
    ss << it->first << "=" << StringUtil::UriEncode(it->second);
    it++;

    for(; it != m_query_strings.end(); it++) {
        ss << "&" << it->first << "=" <<StringUtil::UriEncode(it->second);
    }
    
    url->assign(ss.str());
    return 0;
}

int GetUrlRequest::GetPresignedUrlForObject(
    const std::string &access_key_id, 
    const std::string& access_key_secret, 
    std::string *url) {
    int ret = 0;
    std::string authorization_string;

    std::string relative_url;
    if (!m_bucket_domain.empty()) {
        relative_url = "/" + m_object;
    } else {
        relative_url = GetRelativeUrl();
    }
    AuthorizationGenerator *auth = new AuthorizationGenerator(access_key_id, access_key_secret);
    ret = auth->GenerateAuthorizationString(
        GetMethod(), relative_url, m_query_strings, 
        m_signed_headers, m_headers, "GBK", 
        m_expiration_period_in_seconds, 
        &authorization_string);
    delete auth;
    if (ret) {
        Log::PrintLog(WARNING, TRACE, "GenerateAuthorizationString failed with code");
        return ret;
    }

    AddQueryString("authorization", authorization_string);

    std::stringstream ss;
    ss << "http://" 
    << (m_bucket_domain.empty() ? m_host : m_bucket_domain)
    << StringUtil::UriEncode(relative_url, false);

    ss << "?";
    std::map<std::string, std::string>::const_iterator it = m_query_strings.begin();
    ss << it->first << "=" << StringUtil::UriEncode(it->second);
    it++;

    for (; it != m_query_strings.end(); it++) {
        ss << "&" << it->first << "=" << StringUtil::UriEncode(it->second);
    }
    
    url->assign(ss.str());
    return ret;
}
}
}











/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
