#include "ShoppingCart.h"
#include "../gtest/gmock.h"
#include <functional>

namespace
{
    using namespace testing;
    using namespace Lesson5;

    TEST(Functional, NoParameter)
    {
        ShoppingCart cart;

        cart.Add("apple", 0.6, 5);
        cart.Add("orange", 1.5);
        EXPECT_THAT(cart.Cost(), Eq(4.5));
    }

    TEST(Functional, RefClousure)
    {
        Discounts discounts{ { "apple", 0.8 }, { "banana", 0.5 }, };
        ShoppingCart cart;

        cart.Add("apple", 1.0, 2);
        cart.Add("orange", 1.5);
        EXPECT_THAT(cart.Cost(discounts), Eq(3.1));
    }

    TEST(Functional, ValueClosure)
    {
        ShoppingCart cart1;
        cart1.Add("gum", 1.0);

        ShoppingCart cart2;
        cart2.Add("gum", 1.0);
        cart2.Add("milk", 3.5);

        const double cash = 4.0;
        auto tooExpensive = [cash](const ShoppingCart& cart) -> bool { return cash < cart.Cost(); };

        EXPECT_THAT(tooExpensive(cart1), Eq(false));
        EXPECT_THAT(tooExpensive(cart2), Eq(true));
    }

    TEST(Functional, PartialFunctionApplication)
    {
        ShoppingCart cart;
        cart.Add("banana", 3.0);

        auto discount = [](double percent, double result, const Item& item) { return result + item._price * item._quantity * percent; };
        auto halfPrice = std::bind(discount, 0.5, std::placeholders::_1, std::placeholders::_2);

        EXPECT_THAT(cart.Cost(halfPrice), Eq(1.5));
    }

    TEST(Functional, MoreAlgorithm)
    {
        ShoppingCart cart;
        cart.Add("banana", 3.0);
        cart.Add("apple", 4.2);

        EXPECT_THAT(cart.Contains("apple"), Eq(true));
        EXPECT_THAT(cart.Contains("chicken"), Eq(false));
    }
}