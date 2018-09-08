#include "../gtest/MainTest.h"
#include <string>
#include <iostream>

namespace Lesson2
{
    class Storage final
    {
    public:
        Storage() : Storage("default") {}

        Storage(const std::string& name)
        {
            _name = "Name is " + name;
        }

        void DoWork()
        {
            GTEST_PRINTF("%s\n", _name.c_str());
        }

        std::string GetData() const { return _name; }

    private:
        bool _isWritable = false;
        std::string _name;
    };
   
}