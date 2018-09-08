#include <string>
#include <iostream>
#include <chrono>
#include <memory>
#include "../gtest/gtest.h"

namespace VisitorPattern
{
    using namespace testing;

    // Visitor pattern is one (of many) solution which implements the behaviour of double dispatch

    struct Shape;
    struct Rectangle;
    struct Polygon;

    struct Surface
    {
        virtual void Draw(Shape& shape) { std::cout << "not implemented" << std::endl; }
        virtual void Draw(Rectangle& shape) = 0;
        virtual void Draw(Polygon& shape) = 0;
    };

    struct Paper : public Surface
    {
        void Draw(Rectangle& shape) override { std::cout << "draw rectangle on paper" << std::endl; }
        void Draw(Polygon& shape) override { std::cout << "draw polygon on paper" << std::endl; }
    };

    struct Screen : public Surface
    {
        void Draw(Rectangle& shape) override { std::cout << "draw rectangle on screen" << std::endl; }
        void Draw(Polygon& shape) override { std::cout << "draw polygon on screen" << std::endl; }
    };

    struct Shape
    {
        virtual void DrawOn(Surface& surface) { surface.Draw(*this); }
    };

    struct Rectangle : public Shape
    {
        // override necessary to resolve types correctly at runtime
        void DrawOn(Surface& surface) override { surface.Draw(*this); }
    };

    struct Polygon : public Shape
    {
        // override necessary to resolve types correctly at runtime
        void DrawOn(Surface& surface) override { surface.Draw(*this); }
    };

    void Draw(std::vector<std::pair<Surface*, Shape*>> drawings)
    {
        for (auto drawing : drawings)
            drawing.second->DrawOn(*drawing.first);
    }

    TEST(VisitorPattern, DynamicTyping)
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