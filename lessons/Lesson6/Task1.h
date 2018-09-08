#pragma once
#include <string>

namespace Lesson6
{
    struct PowerRepeater
    {
        PowerRepeater(std::string initialValue, int numTimes = 1) : _text(std::move(initialValue)), _numTimes(numTimes) {}

        std::string operator()() 
        { 
            for (int i = 0; i < _numTimes; i++)
                _text.append(_text); 

            return _text;
        }

        std::string _text;
        int _numTimes;
    };
}