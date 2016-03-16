#ifndef INF_DS_BOSS_COMMON_UTIL_TIME_UTIL_H_
#define INF_DS_BOSS_COMMON_UTIL_TIME_UTIL_H_
#include <stdint.h>
#include <string>

namespace bce {
namespace bos {
class TimeUtil {
public:
    static void Init();
    static int64_t NowMs();
    static time_t Now();

    static std::string NowUtcTime();
    static std::string TimestampToUtcTime(time_t timestamp);
    static int32_t UtcTimeToTimestamp(const std::string &utc_time);

private:
    static int32_t m_utc_local_time_offset_in_seconds;
};

}
}
#endif // INF_DS_BOSS_COMMON_UTIL_TIME_UTIL_H_
