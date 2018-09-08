#include "../gtest/gmock.h"
#include <vector>
#include <numeric>
#include <functional>

namespace
{
    // Test fixture allows multiple tests to reuse same configuration
    using namespace testing;

    namespace
    {
        // this is the class we will be testing
        class MyStrings
        {
        public:

            void Append(std::string s) { _values.emplace_back(s); }

            std::string Get() const
            {
                return std::accumulate(std::begin(_values), std::end(_values), std::string{},
                    [](const auto& a, const auto& b)
                {
                    return a + b;
                });
            }

        private:
            std::vector<std::string> _values;
        };
    }

    struct MyStringOperations : public testing::Test
    {
        MyStringOperations()
        {
            _myStrings.Append("a");
            _myStrings.Append("bc");
            _myStrings.Append("d");
        }

        MyStrings _myStrings;
    };

    TEST_F(MyStringOperations, TestFixtureDemo1)
    {
        EXPECT_THAT(_myStrings.Get(), Eq("abcd"));
    }

    TEST_F(MyStringOperations, TestFixtureDemo2)
    {
        _myStrings.Append("e");
        EXPECT_THAT(_myStrings.Get(), Eq("abcde"));
    }
}