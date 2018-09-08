#include "ExplicitOverride.h"
#include "../gtest/gmock.h"
#include <array>

namespace 
{
    using namespace Lesson2;
    using namespace testing;
        
    TEST(ExplicitOverride, CanAccessViaDerivedClass)
    {
        ExplicitOverride item1;
        item1.DoWork();
        
        ImplicitOverride item2;
        item2.DoWork();
        
        EXPECT_THAT(item1._work, Eq("Derived"));
        EXPECT_THAT(item2._work, Eq("Derived"));
    }
    
    TEST(ExplicitOverride, CanAccessViaBaseClass)
    {
        ExplicitOverride item1;
        ImplicitOverride item2;

        std::array<Base*, 2> items = { &item1, &item2 };
        
        for (auto item : items)
        {
            item->DoWork();
            EXPECT_THAT(item->_work, Eq("Derived"));
        }
    }

    class A
    {
    public:
        virtual void Work() { std::cout << "A" << std::endl; }
    };

    class B : public A
    {
    public:

    };

    class C : public B
    {
    public:
        virtual void Work() { B::Work(); }
    };

    TEST(test, test)
    {
        C c;
        c.Work();
    }
}