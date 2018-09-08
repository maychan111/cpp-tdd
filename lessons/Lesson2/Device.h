#include <string>
#include <iostream>

namespace Lesson2
{
    class Device final
    {
    public:

        Device() = default;
        Device(const std::string& s) : _data(s) {}

        Device(const Device& rhs) = delete;
        Device& operator=(const Device& rhs) = delete;

        Device(Device&& rhs) = default;

        const std::string& GetData() const { return _data; }

    private:
        std::string _data;
    };
}