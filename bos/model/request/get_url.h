/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file get_url.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/31 12:09:47
 * @brief 
 *  
 **/




#ifndef  __GET_URL_H_
#define  __GET_URL_H_

#include <sstream>
#include <vector>
#include <map>
#include <set>
#include "bos/model/request/http_request.h"
#include "util/bos_log.h"


namespace bce {
namespace bos {

class GetUrlRequest {

public:
    GetUrlRequest(const HttpMethod &method, const int expiration_period_in_seconds = 1800) : 
        m_method(method), m_expiration_period_in_seconds(expiration_period_in_seconds) {

    }
    ~GetUrlRequest() {

    }

    int SetBucket(const std::string &bucket) {
        m_bucket = bucket;
        Log::PrintLog(DEBUG, TRACE, "set bucket_name , " + m_bucket);
        return 0;
    }
    
    int SetExpirationPeriodInSeconds(int num) {
        m_expiration_period_in_seconds = num;
        std::stringstream ss;
        ss << num;
        std::string tmp = ss.str();
        Log::PrintLog(DEBUG, TRACE, "set expiration period in seconds , " + tmp);
        return 0;
    }

    int SetObject(const std::string object) {
        Log::PrintLog(DEBUG, TRACE, "set object_name , " + object);
        m_object = object;
        return 0;
    }

    int SetHttpMethod(HttpMethod &method) {

        Log::PrintLog(DEBUG, TRACE, "set http method , " + GetMethod());
        m_method = method;
        return 0;
    }
    
    int SetHost(const std::string &host) {
        m_host = host;
        Log::PrintLog(DEBUG, TRACE, "set host , " + m_host);
        return 0;
    }

    int SetBucketDomain(const std::string &domain) {
        m_bucket_domain = domain;
        Log::PrintLog(DEBUG, TRACE, "set domain, " + m_bucket_domain);
        return 0;
    }

    int AddHeader(const std::string &key, const std::string &value) {
        m_headers[key] = value;
        m_signed_headers.insert(key);

        Log::PrintLog(DEBUG, TRACE, "add signed header , " + key + " : " + value);
        return 0;
    }

    int AddQueryString(const std::string &key, const std::string &value) {
        m_query_strings[key] = value;
        Log::PrintLog(DEBUG, TRACE, "add query string , " + key + " : " + value);
        return 0;
    }

    int BuildUrl(const std::string &access_key_id, const std::string &access_key_secret, std::string *url) ;
    
    int GenerateAuthorizationString(const std::string &access_key_id, const std::string &access_key_secret, std::string *authorization_string);

    int GetPresignedUrlForObject(
        const std::string &access_key_id, 
        const std::string& access_key_secret, 
        std::string *url);
    

    std::string GetRelativeUrl();

    std::string GetMethod() const {
        switch (m_method) {
            case kHttpGet:
            return "GET";
        case kHttpPut:
            return "PUT";
        case kHttpPost:
            return "POST";
        case kHttpHead:
            return "HEAD";
        case kHttpDelete:
            return "DELETE";
        default:
            return "";
        }
    }

private:

    HttpMethod m_method;
    int m_expiration_period_in_seconds;
    std::string m_bucket;
    std::string m_object;
    std::string m_host;
    std::map<std::string, std::string> m_headers;
    std::map<std::string, std::string> m_query_strings;
    std::set<std::string> m_signed_headers;
    std::string m_bucket_domain;
};
}
}













#endif  //__GET_URL_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
