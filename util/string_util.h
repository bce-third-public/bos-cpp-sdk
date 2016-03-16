#ifndef INF_DS_BOSS_COMMON_UTIL_STRING_UTIL_H_
#define INF_DS_BOSS_COMMON_UTIL_STRING_UTIL_H_
#include <map>
#include <set>
#include <string>
#include <vector>

namespace bce {
namespace bos {
class StringUtil {
public:
    static int Split(const std::string &str, char delimiter,
            std::vector<std::string> *result);

    static int Split(const std::string &str, char delimiter,
            std::set<std::string> *result);

    static int Split(const std::string &str,
            char major_delimiter, char minor_delimiter,
            std::map<std::string, std::string> *result);

    static int Trim(const std::string &src, std::string *out, char c = '\n');

    static int ToLower(const std::string &src, std::string *lower);
    static int ToUpper(const std::string &src, std::string *lower);

    static std::string UriEncode(const std::string &input, bool encode_slash = true);
    static int UriDecode(const std::string &input, std::string *out);
    static std::string ToHex(unsigned char c);
    static std::string ToHex(const std::string &src);
    static std::string ToUpper(const std::string &src);
    static std::string ToLower(const std::string &src);
    static std::string Trim(const std::string &src);

    static std::string Sha256Hex(const std::string &src, const std::string &sk);

    static int Icnov(const std::string &src, const std::string &from_encode,
            const std::string &to_encode, std::string *dest);

private:
    static bool IsHexChar(unsigned char c);
    static unsigned char ToBin(unsigned char c);
};
}
}

#endif // INF_DS_BOSS_COMMON_UTIL_STRING_UTIL_H_
