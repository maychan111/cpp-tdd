#pragma once
#include "Item.h"
#include "Discounts.h"
#include <vector>
#include <numeric>
#include <algorithm>

// http://en.cppreference.com/w/cpp/language/lambda

namespace Lesson5
{
    class ShoppingCart
    {
    public:

        template <typename ...Params>
        void Add(Params&&... params)
        {
            _items.emplace_back(std::forward<Params>(params)...);
        };

        double Cost() const
        {
            return std::accumulate(std::begin(_items), std::end(_items), 0.0, [](double result, const Item& item)
            {
                return result + item._price * item._quantity;
            });
        }

        double Cost(const Discounts& d)
        {
            return std::accumulate(std::begin(_items), std::end(_items), 0.0, [&d](double result, const Item& item)
            {
                return result + item._price * item._quantity *  d.Lookup(item._name);
            });
        }

        template <typename F>
        double Cost(F func)
        {
            return std::accumulate(std::begin(_items), std::end(_items), 0.0, func);
        }
        
        bool Contains(const std::string& name) const
        {
            return std::find_if(std::begin(_items), std::end(_items), [&](auto item) { return name == item._name; }) != _items.end();
        }

    private:
        std::vector<Item> _items;
    };
}