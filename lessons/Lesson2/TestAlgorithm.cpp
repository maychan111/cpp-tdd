#include "../gtest/gmock.h"
#include <vector>
#include <list>
#include <numeric>

namespace
{
    using namespace testing;

    // Exercise: change std::vector<int> to std::list<int64_t>
    // for (std::list<int>::iterator it = items.begin(); it != items.end(); it++)
    TEST(Algorithm, BeforeRangeFor)
    {
        std::vector<int> items;
        items.push_back(11);
        items.push_back(22);
        items.push_back(5);

        int sum = 0;
        for (size_t i = 0; i < items.size(); i++)
            sum += items[i];

        EXPECT_THAT(sum, Eq(38));
    }

    // Exercise: change std::vector<int> to std::list<int64_t>
    TEST(Algorithm, UseRangeFor)
    {
        auto items = std::vector<int>{ 11, 22, 5 };  // uniform initialization
        auto sum = decltype(items)::value_type{ 0 }; // type deduction

        for (auto i : items)
            sum += i;

        EXPECT_THAT(sum, Eq(38));
    }

    std::list<long> GetItems() { return std::list<long>{ 11, 22, 5 }; }

    // Refactor to use standard library so we are more expressive
    TEST(Algorithm, UseStandardLibrary)
    {
        auto items = GetItems();
        auto sum = std::accumulate(std::begin(items), std::end(items), 0);
        EXPECT_THAT(sum, Eq(38));
    }

    // Use a custom function for Accumulate
    TEST(Alogrithm, Accumulate)
    {
        auto items = std::list<long>{ 5, 0, 2 };

        // DIY
        {
            long product = 1;
            for (auto item : items)
            {
                if (item != 0)
                    product *= item;
            }
            EXPECT_THAT(product, Eq(10));
        }

        // use standard library
        {
            auto product = std::accumulate(std::begin(items), std::end(items), 1,
                [](auto product, auto item) {  return item == 0 ? product : product * item; });

            EXPECT_THAT(product, Eq(10));
        }
    }

    // Loops that requires break
    TEST(Alogrithm, AnyOf)
    {
        auto items = std::vector<std::string>{ "hello", "world", "" };

        // DIY
        {
            bool hasEmptyString = false;
            for (auto& item : items)
            {
                if (item.empty())
                {
                    hasEmptyString = true;
                    break;
                }
            }
            EXPECT_THAT(hasEmptyString, Eq(true));
        }

        // use standard library
        {
            auto hasEmptyString = std::any_of(std::begin(items), std::end(items), [](auto& s) {  return s.empty(); });
            EXPECT_THAT(hasEmptyString, Eq(true));
        }
    }
}