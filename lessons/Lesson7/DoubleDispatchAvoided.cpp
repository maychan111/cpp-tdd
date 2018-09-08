#include <string>
#include <iostream>
#include <chrono>
#include <memory>
#include "../gtest/gtest.h"

namespace DoubleDispatchAvoided
{
    using namespace testing;

    // visitor pattern is sometimes considered a code smell - a different approach may be better
    // problem with visitor pattern is that it usually violates open/close principle

    // source: https://lostechies.com/derekgreer/2010/04/19/double-dispatch-is-a-code-smell/

    // possible solution is usually domain specific
    // this particular solution abstracts shape into smaller concepts (line segments)
    // possible benefits is that each surface only have to implement drawing line semgents (or a few other concepts)
    // new shapes can be defined in terms of line segments (or a few other concepts)

    struct LineSegment;

    struct Shape
    {
        virtual std::vector<LineSegment*> GetLineSegments() = 0;
    };

    struct LineSegment : public Shape
    {
        LineSegment(int id) : _id(id) {}

        std::vector<LineSegment*> GetLineSegments() override { return { this }; }

        int _id;
    };

    struct Rectangle : public Shape
    {
        Rectangle(int t, int l, int r, int b) : top(t), left(l), right(r), bottom(b) {}

        LineSegment top, left, right, bottom;
        std::vector<LineSegment*> GetLineSegments() override { return{ &top, &left, &right, &bottom }; }
    };

    struct Surface
    {
        virtual void Draw(LineSegment& segment) = 0;
    };

    struct Paper : public Surface
    {
        void Draw(LineSegment& segment) override { std::cout << "draw line segment " << segment._id << " on paper" << std::endl; }
    };

    struct Screen : public Surface
    {
        void Draw(LineSegment& segment) override { std::cout << "draw line segment " << segment._id << " on screen" << std::endl; }
    };

    void Draw(std::vector<std::pair<Surface*, Shape*>> drawings)
    {
        for (auto drawing : drawings)
        {
            for (auto& lineSegment : drawing.second->GetLineSegments())
                drawing.first->Draw(*lineSegment);
        }
    }

    TEST(Redesign, DynamicTyping)
    {
        Paper surface1;
        Screen surface2;

        LineSegment shape1{ 1 };
        Rectangle shape2{ 2, 3, 4, 5 };

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