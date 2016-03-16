/*
 *    Author:       Can Cui(cuican01@baidu.com)
 *    Copyright:    Copyright 2013, Baidu Inc.
 *    Description:  封装日志的相关函数
 */

#ifndef INF_DS_BOSS_SDK_C_SRC_LOG_H_
#define INF_DS_BOSS_SDK_C_SRC_LOG_H_
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "util/common_def.h"

BEGIN_C_SDK_NAMESPACE
void SetLogId(uint64_t log_id);
uint64_t GetLogId();
int GetThreadId();

int GetLogLevel();
void SetLogLevel(int log_level);

#define CC_TRIM(f) strrchr((f), '/') == NULL?(f):(strrchr((f), '/')+1)
#define CC_FATAL(fmt, ...) \
    do {\
        fprintf(stderr, "[boss_c_sdk:%s:%d:%d:%llu]"fmt, CC_TRIM(__FILE__), __LINE__, \
                    GetThreadId(), GetLogId(), ##__VA_ARGS__);    \
    } while (false)

#define CC_WARNING(fmt, ...) \
    do {\
        fprintf(stderr, "[boss_c_sdk:%s:%d:%d:%llu]"fmt, CC_TRIM(__FILE__), __LINE__, \
                    GetThreadId(), GetLogId(), ##__VA_ARGS__);    \
    } while (false)

#define CC_NOTICE(fmt, ...) \
    do {\
        fprintf(stderr, "[boss_c_sdk:%s:%d:%d:%llu]"fmt, CC_TRIM(__FILE__), __LINE__, \
                    GetThreadId(), GetLogId(), ##__VA_ARGS__);    \
    } while (false)

#define CC_TRACE(fmt, ...) \
    do {\
        if (GetLogLevel() >= 8) {\
            fprintf(stderr, "[boss_c_sdk:%s:%d:%d:%llu]"fmt, CC_TRIM(__FILE__), __LINE__, \
                    GetThreadId(), GetLogId(), ##__VA_ARGS__);    \
        }\
    } while (false)

#define CC_DEBUG(fmt, ...) \
    do {\
        if (GetLogLevel() >= 16) {\
            fprintf(stderr, "[boss_c_sdk:%s:%d:%d:%llu]"fmt, CC_TRIM(__FILE__), __LINE__, \
                    GetThreadId(), GetLogId(), ##__VA_ARGS__);    \
        }\
    } while (false)

END_C_SDK_NAMESPACE
#endif //INF_DS_BOSS_SDK_C_SRC_LOG_H_
