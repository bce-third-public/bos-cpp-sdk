/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file bns_test.cpp
 * @author yangrui03(com@baidu.com)
 * @date 2015/12/17 19:37:16
 * @brief 
 *  
 **/

#include "bos/api.h"
#include "util/bos_log.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace bce {
namespace bos {

int PrintLog(const std::string &log) {
    std::cout << log << std::endl;
}

TEST(ClientOptions, init_bns) {
    UserPrintType printfunc = Log::UserPrint;
    Log::UserPrint = PrintLog;
    ClientOptions options;
    EXPECT_EQ(options.is_use_bns, false);
    options.set_use_bns();
    EXPECT_EQ(options.is_use_bns, true);
    std::string bns_name = "bj-cu-nginx-bos-online.BCE.all";
    int ret;
    ret = options.init_bns(bns_name);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(bns_name, options.bos_bns_name);
    EXPECT_EQ(options.bns_list.size() > 0, true);
    ret = options.get_host();
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(options.boss_host.compare(std::string("bcs.duapp.com")) != 0, true);
    int tmp_num = options.get_random(0);
    EXPECT_EQ(tmp_num, -1);
    int random_num = options.get_random(10);
    EXPECT_EQ(random_num >= 0 && random_num < 10, true);
    Log::UserPrint = printfunc;
}

} // end namespace bos
} // end namespace bce













/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
