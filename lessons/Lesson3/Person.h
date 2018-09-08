#include "../gtest/MainTest.h"

namespace Lesson3
{
    class Person
    {
    public:
        Person(const std::string& name) : _name(name)
        {
            GTEST_PRINTF("  Construct %s\n", _name.c_str());
        }

        ~Person()
        {
            GTEST_PRINTF("  Destruct %s\n", _name.c_str());
        }

        void Print() const
        {
            GTEST_PRINTF("  I am %s\n", _name.c_str());
        }

        std::string GetName() const { return _name; }

    private:
        std::string _name;
    };
}
