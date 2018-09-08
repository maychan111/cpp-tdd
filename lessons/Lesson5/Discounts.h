#pragma once
#include <string>
#include <map>

namespace Lesson5
{
    class Discounts
    {
    public:

        Discounts(std::initializer_list<std::pair<std::string, double>> values)
        {
            _discounts.insert(values.begin(), values.end());
        }

        double Lookup(const std::string& name) const
        {
            auto it = _discounts.find(name);
            return it == _discounts.end() ? 1.0 : it->second;
        }

    private:
        std::map<std::string, double> _discounts;
    };
}