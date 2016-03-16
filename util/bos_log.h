/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file bos_log.h
 * @author huangshuai05(com@baidu.com)
 * @date 2014/08/13 16:17:14
 * @brief 
 *  
 **/




#ifndef  __BOS_LOG_H_
#define  __BOS_LOG_H_

#include <sstream>

#define TRACE __FILE__, __LINE__

namespace bce {
namespace bos {



const int DEBUG = 0;
const int INFO = 1;
const int WARNING = 2;
const int ERROR = 3;
const int FATAL = 4;

typedef int (*UserPrintType)(const std::string &log) ;

class Log {

public:
    static UserPrintType UserPrint;
    
    static int PrintLog(int t_level, const std::string &file, int line, const std::string &message) {
        if(t_level < m_level) {
            return 0;
        } 
        std::stringstream ss;
        ss << "file = " << file;
        ss << " line = " << line;
        return UserPrint("LOG [" + GetString(t_level) + "] " + ss.str() + " " +  message);
    }

    static int SetLevel(int t_level) {
        m_level = t_level;
        return 0;
    }

private:
   static int m_level; 
   static std::string GetString(int tmp) {
       if (tmp == 0) {
           return "DEBUG";
       } else if (tmp == 1) {
           return "INFO";
       } else if (tmp == 2) {
           return "WARNING";
       } else if (tmp == 3) {
           return "ERROR";
       } else if (tmp == 4) {
           return "FATAL";
       } else {
           return "";
       }
   }
};

}
}
#endif  //__BOS_LOG_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
