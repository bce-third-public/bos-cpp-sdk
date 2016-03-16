/*
 *    Author:       Can Cui(cuican01@baidu.com)
 *    Copyright:    Copyright 2013, Baidu Inc.
 *    Description:
 */

// Copyright 2013, Baidu Inc.
// Author: Qianqiong Zhang <zhangqianqiong02@baidu.com>

// TODO(cuican01): test driver
#include "gtest/gtest.h"

#include "test/http_mock.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    // HttpMock::Start();
    // sleep(3);
    int ret = RUN_ALL_TESTS();
    // HttpMock::Stop();

    return ret;
}
