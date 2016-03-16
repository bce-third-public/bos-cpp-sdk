#include "util/common_def.h"

#include <string.h>
#include <string>

bool IsVaildObjectMetaKey(const std::string &key) {
    return strncmp(key.c_str(), kObjectMetaPrefix, strlen(kObjectMetaPrefix)) == 0;
}
