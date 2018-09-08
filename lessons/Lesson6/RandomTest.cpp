#include "Random.h"
#include "../gtest/gmock.h"
#include "../gtest/MainTest.h"

namespace
{
    using namespace Lesson6;
    using namespace testing;

    TEST(Random, UseDefaultTemplate)
    {
        Random<> random(1, 1000);
        GTEST_INFO("numbers between 1 and 1000: %d %d %d\n", random.Get(), random.Get(), random.Get());
    }

    TEST(Random, PartiallySpecifyTypes)
    {
        Random<uint64_t> random(0xffffffff, 0xffffffffff);
        GTEST_INFO("very large numbers: %llu %llu %llu\n", random.Get(), random.Get(), random.Get());
    }

    TEST(Random, SpecifyMoreTypes)
    {
        Random<double, std::uniform_real_distribution<double>> random;
        GTEST_INFO("real numbers between 0 and 1: %1.3f %1.3f %1.3f\n", random.Get(), random.Get(), random.Get());
    }
}