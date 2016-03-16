#include "bos/model/request/get_object_request.h"
namespace bce {
namespace bos {
GetObjectRequest::GetObjectRequest(const std::string &bucket_name, const std::string &object_name)
    : ObjectRequest(bucket_name, object_name, kHttpGet) {
}

int GetObjectRequest::SetRange(int64_t start, int64_t length) {
    if (start < 0 || length <= 0) {
        Log::PrintLog(ERROR, TRACE, "set range fail!");
        return kBosIllegalArgument;
    }

    std::stringstream ss;
    ss << "bytes="<< start << "-";
    if (length >= 0) {
        ss << length + start - 1;
    }

    SetRequestHeader("Range", ss.str());
    return 0;
}

int GetObjectRequest::SetVersion(const std::string &version) {
    SetRequestHeader("x-bce-version", version);
    return 0;
}
}
}
