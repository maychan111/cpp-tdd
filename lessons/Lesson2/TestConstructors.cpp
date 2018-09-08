#include "../gtest/MainTest.h"
#include "../gtest/gmock.h"
#include "Device.h"
#include "Storage.h"
#include <array>

namespace
{
    using namespace Lesson2;
    using namespace testing;

    TEST(Constructors, CannotCallDeletedFunctions)
    {
        Device device;
        EXPECT_THAT(device.GetData(), IsEmpty());

        Device d2("my device");
        EXPECT_THAT(d2.GetData(), Eq("my device"));

        // the following would not compile because copy constructor is deleted
        // Device d3 = d2;

        // the following would not compile because assignment is deleted
        // d2 = device;

        // however, we can move it
        Device d4(std::move(d2));
        EXPECT_THAT(d2.GetData(), IsEmpty());
        EXPECT_THAT(d4.GetData(), Eq("my device"));

        GTEST_PRINTF("d2: %s\n", d2.GetData().c_str());
        GTEST_PRINTF("d4: %s\n", d4.GetData().c_str());
    }

    TEST(Constructors, UseDelegatingConstructor)
    {
        Storage storage1;
        EXPECT_THAT(storage1.GetData(), Not(IsEmpty()));

        Storage storage2("fast");
        EXPECT_THAT(storage2.GetData(), Not(IsEmpty()));

        GTEST_PRINTF("storage1: %s\n", storage1.GetData().c_str());
        GTEST_PRINTF("storage2: %s\n", storage2.GetData().c_str());
    }
}