#include "util/time_util.h"

#include <sys/time.h>
#include <time.h>

namespace bce {
namespace bos {
#define kBceUtcTimeFormat "%Y-%m-%dT%H:%M:%SZ"
#define kBceUtcTimeFormatLength 20
void TimeUtil::Init() {
    time_t now = time(NULL);

    struct tm utc_now_tm;
    gmtime_r(&now, &utc_now_tm);
    char buffer[128];
    strftime(buffer, 128, kBceUtcTimeFormat, &utc_now_tm);

    struct tm local_now_tm = utc_now_tm;
    strptime(buffer, kBceUtcTimeFormat, &local_now_tm);

    m_utc_local_time_offset_in_seconds = mktime(&local_now_tm) - now;
}

int64_t TimeUtil::NowMs() {
    struct timeval now;
    gettimeofday(&now, NULL);

    return now.tv_sec * 1000 + now.tv_usec / 1000;
}

time_t TimeUtil::Now() {
    return time(NULL);
}

std::string TimeUtil::NowUtcTime() {
    return TimestampToUtcTime(Now());
}

std::string TimeUtil::TimestampToUtcTime(time_t timestamp) {
    struct tm result_tm;
    gmtime_r(&timestamp, &result_tm);

    char buffer[128];
    int size = strftime(buffer, 128, kBceUtcTimeFormat, &result_tm);

    return std::string(buffer, size);
}

int32_t TimeUtil::UtcTimeToTimestamp(const std::string &utc_time) {
    struct tm result_tm;
    if (strptime(utc_time.c_str(), kBceUtcTimeFormat, &result_tm)
            != utc_time.c_str() + kBceUtcTimeFormatLength) {
        return -1;
    }

    return mktime(&result_tm) - m_utc_local_time_offset_in_seconds;
}

int32_t TimeUtil::m_utc_local_time_offset_in_seconds = 0;

class TimeUtilInitializer {
public:
    TimeUtilInitializer() {
        TimeUtil::Init();
    }
};

TimeUtilInitializer g_time_util_initializer_obj;
}
}

