#ifndef INF_DS_BOSS_SDK_C_SRC_COMMON_DEF_H_
#define INF_DS_BOSS_SDK_C_SRC_COMMON_DEF_H_
#include <string>
#define BEGIN_C_SDK_NAMESPACE namespace bce { namespace bos  {
#define END_C_SDK_NAMESPACE } /* end namespace bos */\
} /* end namespace bce */

#define GENERATE_FIELD_GETTER_AND_SETTER(type_name, hump_name, underline_name)\
    void Set##hump_name(const type_name &data) {\
        m_##underline_name = data;\
    }\
    type_name Get##hump_name() const {\
        return m_##underline_name;\
    }


#define GENERATE_PTR_FIELD_GETTER_AND_SETTER(type_name, hump_name, underline_name)\
    void Set##hump_name(type_name *data) {\
        m_##underline_name = data;\
    }\
    type_name *Get##hump_name() const {\
        return m_##underline_name;\
    }

#define kBossHttpHeaderPrefix "x-bce-"
#define kObjectMetaPrefix "x-bce-meta-"
bool IsVaildObjectMetaKey(const std::string &key);
#endif // INF_DS_BOSS_SDK_C_SRC_COMMON_DEF_H_

