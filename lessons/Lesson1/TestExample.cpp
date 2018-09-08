#include "../gtest/gmock.h"
#include <vector>
#include <memory>

namespace 
{
    /* reference: 
        Google Test/Mock: https://github.com/google/googletest
    */
    using namespace testing;

    int add(int i, int j) { return i + j; }
        
    TEST(Example, Comparison)
    {
        EXPECT_EQ(add(1, 2), 3);
        EXPECT_THAT(add(1, 2), Eq(3));

        EXPECT_THAT(add(1, 2), Ne(2));
        EXPECT_THAT(add(1, 2), Gt(2));
        EXPECT_THAT(add(1, 2), Ge(3));
        EXPECT_THAT(add(1, 2), Lt(10));
        EXPECT_THAT(add(1, 2), Le(10));
        EXPECT_THAT(add(1, 2), Not(4));

        bool test = true;
        EXPECT_THAT(test, Eq(true));
    }

    TEST(Example, NullPointerCheck)
    {
        std::unique_ptr<int> value;
        EXPECT_THAT(value, IsNull());
    }

    TEST(Example, AssertVsExpect)
    {
        char c = 't';
        char *pointer = &c;
        ASSERT_THAT(pointer, IsNull());
        EXPECT_THAT(pointer[0], Eq('x'));
    }

    TEST(Example, MatchStringInVariousWays)
    {
        std::string s;
        EXPECT_THAT(s, IsEmpty());

        s = "test";
        EXPECT_THAT(s, HasSubstr("est"));
        EXPECT_THAT(s, StartsWith("te"));
        EXPECT_THAT(s, StrCaseEq("TEST"));
        EXPECT_THAT("foo", StrEq("foo"));
    }

    TEST(Example, CombineMatchers)
    {
        std::vector<int> value = { 1, 10, 3 };

        EXPECT_THAT(value, AllOf(Not(IsEmpty()), SizeIs(3)));
        EXPECT_THAT(value, AnyOf(Contains(1), Contains(3)));
    }
}