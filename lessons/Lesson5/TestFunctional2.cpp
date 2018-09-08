#include "ShoppingCart2.h"
#include "../gtest/gmock.h"

namespace
{
    using namespace testing;
    using namespace Lesson5;
    
    // std::function: polymorphic function wrapper

    TEST(Functional2, DefaultDiscounter)
    {
        ShoppingCart2 cart;
        cart.Add("bread", 1.2);
        cart.Add("butter", 3.3);

        ASSERT_THAT(cart(), Eq(4.5));
    }

    TEST(Functional2, Lambda)
    {
        auto oneDollarEach = [](auto item) { return 1.0; };

        ShoppingCart2 cart(oneDollarEach);
        cart.Add("bread", 1.2);
        cart.Add("butter", 3.3);

        ASSERT_THAT(cart(), Eq(2.0));
    }

    class Discounter
    {
    public:
        Discounter(double percent) : _percent(percent) {}

        double GetPrice(const Item& item) { return item._price * item._quantity * _percent; }

    private:
        double _percent;
    };

    TEST(Functional2, BindMemberFunction)
    {
        Discounter halfPrice(0.5);

        ShoppingCart2 cart(std::bind(&Discounter::GetPrice, halfPrice, std::placeholders::_1));
        cart.Add("apple", 1.2);
        cart.Add("orange", 2.0);

        ASSERT_THAT(cart(), Eq(1.6));
    }

    class Discounter2
    {
    public:
        Discounter2(double percent) : _percent(percent) {}

        double operator()(const Item& item) { return item._price * item._quantity * _percent; }

    private:
        double _percent;
    };

    TEST(Functional2, Operator)
    {
        Discounter2 noDiscount(1.0);

        ShoppingCart2 cart(std::bind(noDiscount, std::placeholders::_1));
        cart.Add("apple", 1.2);
        cart.Add("orange", 2.0);

        ASSERT_THAT(cart(), Eq(3.2));
    }
}