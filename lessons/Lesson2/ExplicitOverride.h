#include "../gtest/gmock.h"
#include "../gtest/MainTest.h"
#include <string>
#include <iostream>

// Source: Effective Modern C++ by Scott Meyers
//         Item 12: Declare overriding functions override
//
// Objective: Leverage the compiler to make sure virtual functions are declared correctly
// Step 1: compile and run
// Step 2: add "const" after the base class "DoWork" function, compile and see compile error
// Step 3: fix compiler error, run again.
// Step 4: Observe how "ImplicitOverride" is not behaving according to original intention.

namespace Lesson2
{
    struct Base 
    {        
        virtual ~Base() = default;       
        virtual void DoWork()
        {
            _work = "Base";
            GTEST_PRINTF("Base::DoWork()\n");
        }  
    
        mutable std::string _work;                 
    };
    
    struct ExplicitOverride final : public Base
    {
        void DoWork() override
        {
            _work = "Derived";
            GTEST_PRINTF("ExplicitOverride::DoWork()\n");
         } 
    }; 
    
    struct ImplicitOverride final: public Base
    {
        virtual void DoWork()
        {
            _work = "Derived";
            GTEST_PRINTF("ImplicitOverride::DoWork()\n");
        } 
    }; 
}