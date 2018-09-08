#pragma once
#include <random>

namespace Lesson6
{
    // demostrates template: default type names
    // demostrates C++11 random number generators
    //   better than rand() because rand() is not thread safe

    template <typename T = int, 
        typename Dist = std::uniform_int_distribution<T>, 
        typename Rng = std::mt19937_64>
    class Random
    {
    public:
        Random()
        {
             Seed();
        }

        Random(T min, T max) : _distribution(min, max)
        {
             Seed();
        }

        T Get() 
        { 
            return _distribution(_randomNumberGenerator); 
        }

    private:

        void Seed()
        {
            std::random_device device;
            std::uniform_int_distribution<int> seedDist;
            _randomNumberGenerator.seed(seedDist(device));
        }

        Rng _randomNumberGenerator;
        Dist _distribution;
    };
}
