#include <memory>
#include <stdexcept>
#include <list>
#include "../gtest/gmock.h"
#include "../gtest/MainTest.h"

namespace
{
    using namespace testing;

    /* Stack vs. Heap

    1. Object Size:      stack: determined at compile time; heap: at runtime
    2. Available Space:  stack: limited; heap: virtually limitless
    3. Scope:            stack: per thread, function scope; heap: global, program scope
    4. Management:       stack: managed by compiler generated code; heap: managed by code you write
    5. Speed:            stack: faster; heap: slower

    Therefore, use heap only if
        - the amount of memory you need cannot be determined at compile time (e.g. polymorphic creation, dynamic array)
        - the amount of memory you need exceeds the size of the stack frame
        - The lifetime of the memory you need in the function exceeds the function's lifetime

    standard containers help minimize your direct involvement in heap management because they manage it for you
    e.g. std::string std::vector, std::list, etc.
    The container itself should live on the stack, some of the data managed by the container may live on the heap

    After all the above considerations, if you still want to use the heap, then you must use pointers to manage the heap allocation.
    Note: the use of pointer does not necessarily mean that the memory it is pointing to is allocated from the heap

    These are common problems with raw pointers
        uninitialised pointer
        memory leak
        unclear about ownership
        unsafe exception
        more difficult to use with standard containers
    */

    struct Device
    {
        Device(const std::string& s) : _name(s) {}

        void SetName(std::string name) { _name = name; }
        std::string GetName() const { return _name; }

    private:
        std::string _name;
    };

    TEST(RawVsSmart, AlwaysInitializedSmartPointer)
    {
        std::unique_ptr<Device> device;
        ASSERT_THAT(device, Eq(nullptr));
    }

    TEST(RawVsSmart, MemoryLeak)
    {
        auto device = new Device("phone");
        ASSERT_THAT(device->GetName(), Eq("phone"));

        // comment out the following line will cause a memory leak
        delete device;
    }

    TEST(RawVsSmart, AutomaticCleanup)
    {
        auto device = std::make_unique<Device>("mouse");
        ASSERT_THAT(device->GetName(), Eq("mouse"));

        // device is deleted when smart goes out of scope

        // can't even try to delete it
        // delete device;
    }

    TEST(RawVsSmart, UnclearOwnership)
    {
        auto myDevice = new Device("phone");

        // auto yourDevice = myDevice;
        // many lines of code later ...

        delete myDevice;

        // undefined behavior if trying to delete a pointer twice
        // delete yourDevice;
    }

    TEST(RawVsSmart, ClearOwnership)
    {
        auto myDevice = std::make_unique<Device>("phone");

        // error - cannot make copies of unique_ptr
        // auto yourDevice = myDevice;

        // ok - moved ownership from 1 to 2
        auto yourDevice = std::move(myDevice);

        // no memory leak!
    }

    TEST(RawVsSmart, UnsafeException)
    {
        auto UseDevice = [](Device *device)
        {
            if (device == nullptr || device->GetName().empty())
                throw std::runtime_error("should not be null or empty");
        };

        try
        {
            // initialize raw data with a non-empty string will not cause memory leak
            Device *device = new Device("phone");

            // initialize raw data with an empty string will cause memory leak
            // BigData *raw = new BigData(std::string(""));

            UseDevice(device);

            delete device;
        }
        catch (std::exception e)
        {
            GTEST_PRINTF("Exception %s\n", e.what());
        }
    }

    TEST(RawVsSmart, SafeException)
    {
        auto UseDevice = [](Device *raw)
        {
            if (raw == nullptr || raw->GetName().empty())
                throw std::runtime_error("should not be null or empty");
        };

        try
        {
            auto phone = std::make_unique<Device>("phone");
            auto unnamedDevice = std::make_unique<Device>("");

            UseDevice(phone.get());
            UseDevice(unnamedDevice.get());
        }
        catch (std::exception e)
        {
            GTEST_PRINTF("Exception %s\n", e.what());
        }

        // no memory leak
    }

    TEST(RawVsSmart, HardToUseRawPointerInContainer)
    {
        std::list<Device *> container;
        container.push_back(new Device("phone"));
        container.push_back(new Device("tablet"));

        // memory leak if you don't loop through the container to delete the items
        for (auto item : container)
            delete item;
    }

    TEST(RawVsSmart, EasyToUseSmartPointerInContainer)
    {
        std::list<std::unique_ptr<Device>> container;
        container.push_back(std::make_unique<Device>("phone"));
        container.push_back(std::make_unique<Device>("tablet"));

        // automatically delete the items
    }
}