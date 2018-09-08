#include "../gtest/gmock.h"
#include <stdexcept>
#include <map>

namespace
{
    using namespace testing;

    MATCHER(IsEven, "") { return (arg % 2) == 0; }

    TEST(Advanced, UserDefinedMatcher)
    {
        EXPECT_THAT(4, IsEven());
        EXPECT_THAT(3, Not(IsEven()));
    }

    TEST(Advanced, MatchContainer)
    {
        std::vector<int> value = { 10, 30, 12 };

        EXPECT_THAT(value, ElementsAre(10, 30, 12));
        EXPECT_THAT(value, UnorderedElementsAre(10, 12, 30));
        EXPECT_THAT(value, Each(IsEven()));
    }

    TEST(Advanced, CustomMessage)
    {
        const bool condition = false;
        if (condition)
            FAIL() << "should not ber here";
    }

    TEST(Advanced, VerifyThrownException)
    {
        auto f = []() { throw std::runtime_error("my bad"); };

        EXPECT_THROW(f(), std::runtime_error);
        EXPECT_ANY_THROW(f()) << "expect to throw some exception";
    }

    TEST(Advanced, VerifyNoExceptionThrown)
    {
        auto f = []() { return 10; };

        int i = 0;
        EXPECT_NO_THROW({ i = f(); });
        EXPECT_THAT(i, Eq(10));
    }

    TEST(Advanced, VerifyFloatingPoint)
    {
        double d1 = 1.01;
        double d2 = 1.009;
        EXPECT_THAT(d1, DoubleNear(d2, 0.01));
    }

    template<typename Container>
    void Verify(std::string message, Container&& v)
    {
        SCOPED_TRACE(message);
        EXPECT_THAT(v, SizeIs(Gt(1u)));
        EXPECT_THAT(v.begin(), Ne(v.end()));
    }

    TEST(Advanced, ScopedVerification)
    {
        auto v1 = std::map<int, std::string>{ { 1, "value 1" }, { 2, "value 2" } };
        auto v2 = std::map<int, std::string>{ { 3, "value 3" }, { 4, "value 4" } };

        Verify("validating v1", v1);
        Verify("validating v2", v2);
    }
}