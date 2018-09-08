#pragma once
#include "Item.h"
#include <vector>
#include <numeric>
#include <functional>

// http://en.cppreference.com/w/cpp/utility/functional/function

namespace Lesson5
{
    using PricingCalculator = std::function<double(const Item&)>;

    double DefaultPricingCalculator(const Item& item)
    {
        return item._price * item._quantity;
    }

    class ShoppingCart2
    {
    public:

        ShoppingCart2() : _pricingCalculator(DefaultPricingCalculator) {}
        ShoppingCart2(PricingCalculator discounter) : _pricingCalculator(discounter == nullptr ? DefaultPricingCalculator : discounter) {}

        template <typename ...Params>
        void Add(Params&&... params)
        {
            _items.emplace_back(std::forward<Params>(params)...);
        };

        double operator()() const
        {
            return std::accumulate(std::begin(_items), std::end(_items), 0.0, [this](double result, const Item& item)
            {
                return result + _pricingCalculator(item);
            });
        }

    private:

        std::vector<Item> _items;
        PricingCalculator _pricingCalculator;
    };
}