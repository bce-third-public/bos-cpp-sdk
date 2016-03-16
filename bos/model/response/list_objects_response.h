/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file list_objects_response.h
 * @author xiaohuirong(com@baidu.com)
 * @date 2014/07/21 20:07:51
 * @brief 
 *  
 **/

#ifndef  INF_DS_BOSS_SDK_CPP_RESPONSE_LIST_OBJECTS_RESPONSE_H_
#define  INF_DS_BOSS_SDK_CPP_RESPONSE_LIST_OBJECTS_RESPONSE_H_
#include "bos/model/response/response.h"
#include "util/memory_stream.h"
#include <vector>
#include <string>
#include <sstream>
namespace bce {
namespace bos {

struct Content {
    std::string key;
    std::string lastModified;
    std::string eTag;
    std::string size;
    std::string ownerId;
    std::string ownerDisplayName;
};

class ListObjectsResponse : public BosResponse {
public:
    ListObjectsResponse() {
        m_buffer = new std::string;
        m_str_outputStream = new StringOutputStream(m_buffer);
        SetOutputStream(m_str_outputStream);
    }
    
    virtual ~ListObjectsResponse();
    int GetDelimiter(std::string *t_delimiter) {
        t_delimiter->assign(m_delimiter);
        return 0;
    }

    int GetIsTruncated(bool *t_isTruncated){
        *t_isTruncated = m_isTruncated;
        return 0;
    }

   int  GetMaxKeys(int *maxKeys){
       *maxKeys = m_maxKeys;
        return 0;
    }

   int GetMaxKeys() {
       return m_maxKeys;
   }

    int  GetMarker(std::string *t_marker){
        t_marker->assign(m_marker);
        return 0;
    }
    
   int  GetName(std::string *t_name){
        t_name->assign(m_name);
        return 0;
    }
    
    int GetNextMarker(std::string *t_nextMarker){
        t_nextMarker->assign(m_nextMarker);
        return 0;
    }
    
    int GetPrefix(std::string *t_prefix){
        t_prefix->assign(m_prefix);
        return 0;
    }

    int GetContents(std::vector<Content> *t_contents){
        *t_contents = m_contents;
        return 0;
    }
    
    int GetCommonPrefixes(std::vector<std::string> *t_common_prefixes) {
        *t_common_prefixes = m_commonPrefixes;
        return 0;
    }
protected:
    int ParseCommandSpecificResponse();
    
private:
    std::vector<std::string> m_commonPrefixes;
    std::vector<Content> m_contents;
    std::string m_prefix;
    std::string m_nextMarker;
    std::string m_name;
    std::string m_marker;
    int m_maxKeys;
    bool m_isTruncated;
    std::string m_delimiter;
    std::string *m_buffer;
    OutputStream *m_str_outputStream;
};
}
}
#endif  //__LIST_OBJECTS_RESPONSE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
