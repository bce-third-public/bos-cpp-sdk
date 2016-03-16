#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

#include "util/common_def.h"
BEGIN_C_SDK_NAMESPACE
class Util {
public:
static int SpiltString(const std::string &src, const std::string &delimiter,
                int max_items, std::vector<std::string> *result) {
    size_t current = 0;
    size_t next = 0;

    for (; next != std::string::npos && (max_items < 0
                                            || max_items > static_cast<int>(result->size()) + 1); ) {
        next = src.find_first_of(delimiter, current);
        result->push_back(src.substr(current, next - current));

        current = next + delimiter.size();
    }

    if (next != std::string::npos) {
        result->push_back(src.substr(current));
    }

    return 0;
}

static inline std::string &Trim(std::string &s) {
    return TrimLeft(TrimRight(s));
}

private:
static inline std::string &TrimLeft(std::string &str) {
    str.erase(str.begin(), std::find_if(
                str.begin(), str.end(),
                std::not1(std::ptr_fun<int, int>(std::isspace))));
    return str;
}

static inline std::string &TrimRight(std::string &str) {
    str.erase(std::find_if(str.rbegin(),
                str.rend(),
                std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
                str.end());
    return str;
}
};

END_C_SDK_NAMESPACE
