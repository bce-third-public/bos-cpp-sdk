#ifndef INF_DS_BOSS_COMMON_UTIL_AUTHORIZATION_UTIL_H_
#define INF_DS_BOSS_COMMON_UTIL_AUTHORIZATION_UTIL_H_
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace bce {
namespace bos {
class Authorization {
public:
    int ParseFromString(const std::string &str);
    int SerializeToString(std::string *str) const;

    void SetVersion(int version) {
        m_version = version;
    }

    int GetVersion() const {
        return m_version;
    }

    void SetAk(const std::string &ak) {
        m_ak = ak;
    }

    const std::string &GetAk() const {
        return m_ak;
    }

    void SetTimestamp(const std::string & utc_timestamp) {
        m_utc_timestamp = utc_timestamp;
    }

    const std::string & GetTimestamp() const {
        return m_utc_timestamp; //
    }

    void SetExpirationPeriodInSeconds(int expiration_period_in_seconds) {
        m_expiration_period_in_seconds = expiration_period_in_seconds;
    }

    int GetExpirationPeriodInSeconds() const {
        return m_expiration_period_in_seconds;
    }

    void SetSignedHeaders(const std::set<std::string> &signed_headers) {
        m_signed_headers = signed_headers;
    }

    const std::set<std::string> &GetSignedHeaders() const {
        return m_signed_headers;
    }

    void SetSignature(const std::string &signature) {
        m_signature = signature;
    }

    const std::string &GetSginature() const {
        return m_signature;
    }

private:
    int m_version;
    std::string m_ak;
    std::string m_utc_timestamp;
    int m_expiration_period_in_seconds;
    std::set<std::string> m_signed_headers;
    std::string m_signature;
};

class AuthorizationGenerator {
public:
    AuthorizationGenerator(const std::string &ak, const std::string sk, int version = 1);
    virtual ~AuthorizationGenerator() {
    }

    int GenerateAuthorizationString(const std::string &http_method, const std::string &uri,
            const std::map<std::string, std::string> &query_string,
            const std::set<std::string> &signed_headers,
            const std::map<std::string, std::string> &headers,
            const std::string &encoding,
            int expiration_period_in_seconds, std::string *authorization_string) const;

    int GenerateSignature(const std::string &http_method, const std::string &uri,
            const std::map<std::string, std::string> &query_string,
            const std::set<std::string> &signed_headers,
            const std::map<std::string, std::string> &headers,
            const std::string &encoding,
            std::string *signature) const;

private:
    std::string m_ak;
    std::string m_sk;
    int m_version;

    std::string GenerateSessionKey(const std::string &utc_timestamp, int expiration_period_in_seconds) const;

    int UriCanonicalization(const std::string &uri,
            const std::string &encoding, std::stringstream *stream) const;
    int QueryStringCanonicalization(const std::map<std::string, std::string> &query_string,
            const std::string &encoding,std::stringstream *stream) const;
    int HeadersCanonicalization(const std::set<std::string> &signed_headers,
            const std::map<std::string, std::string> &headers,
            const std::string &encoding, std::stringstream *stream) const;

    std::string NormalizeString(const std::string &str, const std::string &encoding) const ;

    virtual bool NeedHeaderIncludeInSignature(const std::string &key) const;
    virtual bool NeedQueryStringItemIncludeInSignature(const std::string &key) const;

    std::set<std::string> m_signed_headers_keys;
    std::set<std::string> m_exclusive_query_item_key_set;
};
}
}
#endif // INF_DS_BOSS_COMMON_UTIL_AUTHORIZATION_UTIL_H_
