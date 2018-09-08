#pragma once

namespace Lesson6
{
    class Factorial
    {
    public:
        Factorial(uint64_t n) : _n(n) {}

        void DoWork() { _result = Compute(_n); }

        uint64_t _result;

    private:

        uint64_t Compute(uint64_t n) const { return n <= 1 ? 1 : n * Compute(n - 1); }
        uint64_t _n;
    };
}