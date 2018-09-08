#pragma once
#include <inttypes.h>
#include <string>

namespace Lesson5
{
    struct Item
    {
        Item(std::string name, double p) : _name(name), _price(p), _quantity(1) {}
        Item(std::string name, double p, unsigned int q) : _name(name), _price(p), _quantity(q) {}

        std::string _name;
        double _price;
        unsigned int _quantity;
    };
}
