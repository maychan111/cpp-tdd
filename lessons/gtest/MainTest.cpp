#include "../gtest/gmock.h"
#include "MainTest.h"
#include <iostream>

namespace testing
{
    std::mutex gtest_mutex;

    MainTest::MainTest(int argc, char *argv[]) : _argc(argc), _argv(argv)
    {
        GTEST_INFO("Running %s\n", _argv[0]);
    }

    MainTest::~MainTest()
    {
        GTEST_INFO("Finished %s\n", _argv[0]);
    }

    int MainTest::Run()
    {
        try
        {
            testing::InitGoogleTest(&_argc, _argv);
            return RUN_ALL_TESTS();
        }
        catch (const std::exception& e)
        {
            GTEST_PRINTF("Uncaught exception: %s\n", e.what());
            return -1;
        }
    }
}