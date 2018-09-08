#include "Person.h"
#include "../gtest/gmock.h"
#include <memory>

namespace
{
    using namespace testing;

    class Device
    {
    public:
        virtual std::string GetType() const = 0;
        virtual ~Device() = default;
    };

    class Router : public Device
    {
    public:
        std::string GetType() const override { return "router"; }
        uint64_t GetSpeed() const { return _speed; }

    private:
        uint64_t _speed = 1000000;
    };

    class Mouse : public Device
    {
    public:
        std::string GetType() const override { return "mouse"; }
        uint16_t GetNumButtons() const { return _numButtons; }

    private:
        uint16_t _numButtons = 2;
    };

    TEST(DynamicCast, SharedPointer)
    {
        // upcast (it just works)
        std::shared_ptr<Device> device = std::make_shared<Router>();

        // downcast to correct type
        std::shared_ptr<Router> router = std::dynamic_pointer_cast<Router>(device);
        ASSERT_THAT(router, Ne(nullptr));
        EXPECT_THAT(router->GetSpeed(), Eq(1000000u));

        // downcast to incorrect type
        std::shared_ptr<Mouse> mouse = std::dynamic_pointer_cast<Mouse>(device);
        ASSERT_THAT(mouse, Eq(nullptr));
    }

    TEST(DynamicCast, UniquePointerUnsafe)
    {
        // upcast (it just works)
        std::unique_ptr<Device> device = std::make_unique<Router>();

        // downcast to correct type, much more complicated than with shared pointer because unique pointer is not copyable
        std::unique_ptr<Router> router = std::unique_ptr<Router>(static_cast<Router *>(device.release()));
        EXPECT_THAT(router->GetSpeed(), Eq(1000000u));

        // downcast to incorrect type, will crash!
        // std::unique_ptr<Mouse> mouse = std::unique_ptr<Mouse>(static_cast<Mouse *>(device.release()));
        // ASSERT_THAT(mouse->GetNumButtons(), Eq(2u));
    }

    TEST(DynamicCast, UniquePointerSafe)
    {
        std::unique_ptr<Device> device = std::make_unique<Router>();

        // downcast using raw pointer
        std::unique_ptr<Router> router;
        Router *rawRouter = dynamic_cast<Router *>(device.get());
        if (rawRouter != nullptr)
        {
            device.release();
            router.reset(rawRouter);
        }

        ASSERT_THAT(router, Ne(nullptr));
        EXPECT_THAT(router->GetSpeed(), Eq(1000000u));

        // downcast to incorrect type
        std::unique_ptr<Mouse> mouse;
        Mouse *rawMouse = dynamic_cast<Mouse *>(device.get());
        EXPECT_THAT(rawMouse, Eq(nullptr));
    }

    // template solution - sort of work
    template<typename Derived, typename Base, typename Del>
    std::unique_ptr<Derived, Del>
        static_unique_ptr_cast(std::unique_ptr<Base, Del>&& p)
    {
        auto d = static_cast<Derived *>(p.release());
        return std::unique_ptr<Derived, Del>(d, std::move(p.get_deleter()));
    }

    template<typename Derived, typename Base, typename Del>
    std::unique_ptr<Derived, Del>
        dynamic_unique_ptr_cast(std::unique_ptr<Base, Del>&& p)
    {
        if (Derived *result = dynamic_cast<Derived *>(p.get())) {
            p.release();
            return std::unique_ptr<Derived, Del>(result, std::move(p.get_deleter()));
        }
        return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
    }

    TEST(DynamicCast, UniquePointerTemplate)
    {
        std::unique_ptr<Device> device = std::make_unique<Router>();

        // compiler error - cannot use std::unique<Router> with default deleter
        // std::unique_ptr<Router> router = dynamic_unique_ptr_cast<Router, Device>(std::move(device));

        // the following will work only if the base class has virtual destructor
        auto router = dynamic_unique_ptr_cast<Router, Device>(std::move(device));
        ASSERT_THAT(router, Ne(nullptr));
        EXPECT_THAT(router->GetSpeed(), Eq(1000000u));

        // downcast to incorrect type
        auto mouse = dynamic_unique_ptr_cast<Mouse, Device>(std::move(device));
        EXPECT_THAT(mouse, Eq(nullptr));
    }
}