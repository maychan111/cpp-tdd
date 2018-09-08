#pragma once
#include "../gtest/gmock.h"

class Resource final
{
public:
    Resource()
    {
        std::cout << "  default constructor" << std::endl;
    }

    explicit Resource(int oneElement)
    {
        std::cout << "  single parameter constructor" << std::endl;
        _size = 1;
        _values = new int[1];
        _values[0] = oneElement;
    }

    Resource(std::initializer_list<int> values)
    {
        std::cout << "  initializer_list constructor of size " << values.size() << std::endl;

        _size = values.size();
        _values = new int[_size];

        size_t i = 0;
        for (auto v : values)
            _values[i++] = v;
    }

    Resource(const Resource& rhs)
    {
        std::cout << "  copy constructor" << std::endl;

        if (rhs._size > 0)
        {
            _values = new int[rhs._size];
            _size = rhs._size;
            memcpy(_values, rhs._values, sizeof(int) * _size);
        }
    }

    Resource(Resource&& rhs) noexcept
    {
        std::cout << "  move constructor" << std::endl;

        if (rhs._size > 0)
        {
            _values = rhs._values;
            _size = rhs._size;
            rhs._values = nullptr;
            rhs._size = 0;
        }
    }

    Resource& operator=(const Resource& rhs)
    {
        std::cout << "  copy assignment (" << _size << " <- " << rhs._size << ")" << std::endl;

        if (this != &rhs)
        {
            delete[] _values;

            _values = new int[rhs._size];
            _size = rhs._size;
            memcpy(_values, rhs._values, sizeof(int) * _size);
        }
        return *this;
    }

    Resource& operator=(Resource&& rhs) noexcept
    {
        std::cout << "  move assignment (" << _size << " <- " << rhs._size << ")" << std::endl;

        if (this != &rhs)
        {
            std::swap(rhs._values, _values);
            std::swap(rhs._size, _size);
        }
        return *this;
    }

    ~Resource()
    {
        std::cout << "  destructor: value size " << _size << std::endl;
        delete[] _values;
    }

    size_t GetSize() const { return _size; }
    const int *GetVector() const { return _values; }

private:

    // let's assume that's no such thing as standard library and you have to manage your raw pointer
    int *_values = nullptr;
    size_t _size = 0;
};