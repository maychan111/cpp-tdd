#include "Person.h"
#include "../gtest/gmock.h"
#include "../gtest/MainTest.h"
#include <memory>
#include <list>

namespace
{
    using namespace testing;

    /*
        Smart Pointer Parameters: How should you prefer to pass smart pointers, and why?
        http://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/
    */

    class Widget
    {
    public:

        Widget(int id) : _id(id)
        {
            GTEST_PRINTF("[%d] constructor\n", getId());
        }

        ~Widget()     
        {
            GTEST_PRINTF("[%d] destructor\n", getId());
        }

        int getId() const { return _id; }
        void modifyFoo() { _foo++; }

    private:
        int _id = 0;
        int _foo = 0;
    };

    struct Parameter : public testing::Test
    {
        Parameter() { GTEST_PRINTF("Parameter constructor\n"); }
        ~Parameter() { GTEST_PRINTF("Parameter destructor\n"); }
    };

    TEST_F(Parameter, IsRawPointer)
    {
        // pass by raw pointer if:
        // 1. callee does not participate in lifetime strategy
        // 2. the parameter may be optional (nullptr)
        // Pro: callee does not need to know how the pointer is managed
        //      caller does not need to commit to a lifetime strategy

        auto call = [](Widget *w)
        {
            if (w)
                w->modifyFoo();
        };

        auto w = Widget{ 1 };
        call(&w);

        auto uw = std::make_unique<Widget>(2);
        call(uw.get());

        auto sw = std::shared_ptr<Widget>(std::move(uw));
        call(sw.get());
    }

    TEST_F(Parameter, IsReference)
    {
        // pass by raw pointer if:
        // 1. callee does not participate in lifetime strategy
        // 2. the parameter is not optional
        // 3. the callee may change the object 

        auto call = [](Widget& w) { w.modifyFoo(); };

        auto w = Widget{ 1 };
        call(w);

        auto uw = std::make_unique<Widget>(2);
        call(*uw.get());

        auto sw = std::shared_ptr<Widget>(std::move(uw));
        call(*sw.get());
    }

    TEST_F(Parameter, IsConstReference)
    {
        // pass by raw pointer if:
        // 1. callee does not participate in lifetime strategy
        // 2. the parameter is not optional
        // 3. the callee with not change the object

        auto call = [](const Widget& w) { return w.getId(); };

        const auto w = Widget{ 1 };
        call(w);

        auto uw = std::make_unique<Widget>(2);
        call(*uw.get());

        auto sw = std::shared_ptr<Widget>(std::move(uw));
        call(*sw.get());
    }

    TEST_F(Parameter, IsUniquePtrByValue)
    {
        // pass by unique_ptr by value to indicate callee should take ownership

        std::unique_ptr<Widget> result;
        EXPECT_THAT(result.get(), IsNull());

        auto call = [&](std::unique_ptr<Widget> w)
        {
            result = std::move(w);
        };

        auto uw = std::make_unique<Widget>(1);

        call(std::move(uw));
        EXPECT_THAT(result.get(), NotNull());
    }

    TEST_F(Parameter, IsUniquePtrByReference)
    {
        // Use a non-const unique_ptr& parameter only to modify the unique_ptr
        auto call = [](std::unique_ptr<Widget>& w)
        {
            w.reset(new Widget(2)); // w is modified
        };

        auto w = std::make_unique<Widget>(1);

        call(w);
        EXPECT_THAT(w.get(), NotNull());

        // no reason to have a const unique_ptr reference because lifetime is already managed by caller, so just pass * or &
    }

    TEST_F(Parameter, IsSharedPtrByValue)
    {
        // pass by shared_ptr by value means callee should take shared ownership

        std::shared_ptr<Widget> result;
        EXPECT_THAT(result.get(), IsNull());

        auto call = [&result](std::shared_ptr<Widget> w)
        {
            result = std::move(w);
        };

        auto w = std::make_shared<Widget>(1);
        call(w);

        EXPECT_THAT(w.get(), NotNull());
        EXPECT_THAT(result.get(), NotNull());
    }

    TEST_F(Parameter, IsSharedPtrByReference)
    {
        // pass by shared_ptr by reference for in/out shared_ptr manipulation
        auto call = [](std::shared_ptr<Widget>& w)
        {
            w.reset();
        };

        auto w = std::make_shared<Widget>(1);
        call(w);

        EXPECT_THAT(w.get(), IsNull());
    }

    TEST_F(Parameter, IsSharedPtrByConstReference)
    {
        // pass by shared_ptr by reference if you are not sure if callee might share ownership
        std::shared_ptr<Widget> result;
        auto call = [&result](const std::shared_ptr<Widget>& w)
        {
            if (w)
                result = w;
        };

        auto w = std::make_shared<Widget>(1);

        call(nullptr);
        EXPECT_THAT(result.get(), IsNull());

        call(w);
        EXPECT_THAT(result.get(), NotNull());
    }
}