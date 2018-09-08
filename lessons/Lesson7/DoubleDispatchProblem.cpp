#include <string>
#include <iostream>
#include <chrono>
#include <memory>
#include "../gtest/gtest.h"

namespace DoubleDispatchProblem
{
    using namespace testing;

    // double dispatch:
    //     a mechanism that dispatches a function call to different concrete functions
    //     depending on the runtime types of two objects
    //
    // multiple dispatch: based on runtime types of more than two objects)

    struct Shape
    {
    };

    struct Rectangle : public Shape
    {
    };

    struct Polygon : public Shape
    {
    };

    struct Surface
    {
        virtual void Draw(Shape& shape) { std::cout << "not implemented" << std::endl; }
        virtual void Draw(Rectangle& shape) = 0;
        virtual void Draw(Polygon& shape) = 0;
    };

    struct Paper : public Surface
    {
        void Draw(Shape& shape) override { std::cout << "paper: not implemented" << std::endl; }
        void Draw(Rectangle& shape) override { std::cout << "draw rectangle on paper" << std::endl; }
        void Draw(Polygon& shape) override { std::cout << "draw polygon on paper" << std::endl; }
    };

    struct Screen : public Surface
    {
        void Draw(Shape& shape) override { std::cout << "screen: not implemented" << std::endl; }
        void Draw(Rectangle& shape) override { std::cout << "draw rectangle on screen" << std::endl; }
        void Draw(Polygon& shape) override { std::cout << "draw polygon on screen" << std::endl; }
    };

    TEST(DoubleDispatch, StaticTyping)
    {
        Paper surface1;
        Screen surface2;

        Polygon shape1;
        Rectangle shape2;

        surface1.Draw(shape1);
        surface1.Draw(shape2);

        surface2.Draw(shape1);
        surface2.Draw(shape2);
    }

    void Draw(std::vector<std::pair<Surface*, Shape*>> drawings)
    {
        for (auto drawing : drawings)
            drawing.first->Draw(*drawing.second);
    }

    TEST(DoubleDispatch, DynamicTyping)
    {
        Paper surface1;
        Screen surface2;

        Polygon shape1;
        Rectangle shape2;

        std::vector<std::pair<Surface*, Shape*>> drawings =
        {
            { &surface1, &shape1 },
            { &surface1, &shape2 },
            { &surface2, &shape1 },
            { &surface2, &shape2 }
        };

        Draw(drawings);
    }
}