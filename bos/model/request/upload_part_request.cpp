/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file upload_part_request.cpp
 * @author huangshuai05(com@baidu.com)
 * @date 2014/07/18 12:59:59
 * @brief 
 *  
 **/

#include "bos/model/request/upload_part_request.h"
#include "openssl/md5.h"
#include "openssl/sha.h"
#include "zlib.h"

#include "util/memory_stream.h"
#include "util/encrypt_util.h"
#include "util/string_util.h"
namespace bce {
namespace bos {
int UploadPartRequest::BuildCommandSpecific(HttpRequest *request) {
    std::string content_md5;
    std::string content_sha256;

    if(m_content_stream ->GetSize() == -1001) {
        throw BosClientException("no such file!");
    }
    CalculateObjectFinger(m_content_stream, &content_md5, &content_sha256);

    SetRequestHeader("x-bce-content-sha256", content_sha256);
    SetRequestHeader("Content-MD5", content_md5);

    std::stringstream ss;
    
    ss << (m_content_stream->GetSize() - m_content_stream->GetPos());
    SetRequestHeader("Content-Length", ss.str());
    return 0;
}



int UploadPartRequest::CalculateObjectFinger(bce::bos::InputStream *stream,
        std::string *md5, std::string *sha256) const {
    const int size_per_block = 1024 * 64;
    std::string block;
    int64_t saved_pos = stream->GetPos();

    MD5_CTX md5_ctx;
    MD5_Init(&md5_ctx);

    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);

    int ret = 0;
    while (true) {
        ret = stream->Read(size_per_block, &block);
        if (ret < 0) {
            throw BosClientException(stream->GetErrorDescription(ret));
            break;
        }

        if (ret == 0) {
            break;
        }

        MD5_Update(&md5_ctx, block.data(), block.size());
        SHA256_Update(&sha256_ctx, block.c_str(), block.size());
    }

    ret = stream->Seek(saved_pos);
    unsigned char md[16];
    MD5_Final(md, &md5_ctx);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256_ctx);

    if (ret < 0) {
        throw BosClientException(stream->GetErrorDescription(ret));
    }


    EncryptUtil::Base64Encode(std::string(reinterpret_cast<char *>(md), sizeof(md)), md5);
    sha256->assign(StringUtil::ToLower(
                        StringUtil::ToHex(std::string(
                        reinterpret_cast<const char *>(hash), SHA256_DIGEST_LENGTH))));

    return 0;
}

}
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
