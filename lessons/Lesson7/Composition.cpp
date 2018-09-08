#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include "../gtest/gmock.h"

namespace Lesson7
{
    using namespace testing;

    // Composition vs. Inheritance: How to Choose?
    // https://www.thoughtworks.com/insights/blog/composition-vs-inheritance-how-choose
    //
    // summary of article:
    // composition and inheritance are both fundamental concepts of OOP, one cannot replace another
    // * composition serves one purpose: make wholes out of parts (mechanics)
    // * inheritance serves two purposes: semantics (meaning) and mechanics
    //
    // mechanically, subclass inherit implementation of superclass
    // semantically, subclass exposes all the interfaces of its superclass
    //
    // an over emphasis on code reuse as the primary purpose of inheritance can lead to semantic confusion

    // guidelines of using inheritance
    // #1 subclass is a proper subtype of the superclass
    // #2 superclass's implementation is appropriate for the subclass
    // #3 enhancements made by the subclass are primarily additive
    // #4 both classes are in the same logical domain

    ////////////////////////////////////////////////////////////////////////////
    // misuse #1: subclass is not a proper subtype of the superclass
    struct IntegerStack : public std::list<int>
    {
        void Push(int);
        int Pop();

        // inherit empty() and other public functions from std::list

        // semantically: integer stack is a list of intger violates
        // Liskov substitution principle the ("L" of SOLID)
        // https://en.wikipedia.org/wiki/SOLID_(object-oriented_design)

        // mechanically: violates encapsulation
        // (using list as an implementation choice should be hidden from user)
    };

    ////////////////////////////////////////////////////////////////////////////
    // misuse #2: superclass's implementation is not appropriate for the subclass
    // misuse #3: enhancements made by the subclass are primarily additive
    struct Rectangle
    {
        virtual void SetWidth(int w) { width = w; }
        virtual void SetHeight(int h) { height = h; }
        virtual int Area() { return width * height; }
        int width, height;
    };

    struct Square : public Rectangle
    {
        virtual void SetWidth(int w) { width = w; height = w; }
        virtual void SetHeight(int h) { height = h; width = h; }
    };

    // the premise of this hierarchy breaks down:
    // if square is a rectangle, then substituting square with rectangles should result
    // in the same behavior when using only rectangle's interface
    void PrintArea(Rectangle& shape)
    {
        std::cout << "area of shape is " << shape.Area() << std::endl;
    }

    TEST(Inheritance, Misuse2)
    {
        // rectangle's premise: width and height can change independently
        // square's premise: width and height cannot change independently
        // therefore they are two separate domain class that does not form a hierarchy
        // redesign: both should derive independently from a "Shape" concept
        // takeaway: class hierarchy models behaviors, not necessarily definition of of the model

        Rectangle shape1;
        shape1.SetWidth(2);
        shape1.SetHeight(3);
        PrintArea(shape1);

        Square shape2;
        shape2.SetWidth(2);
        shape2.SetHeight(3);
        PrintArea(shape2);
    }

    ////////////////////////////////////////////////////////////////////////////
    // misuse #4: both classes are in the same logical domain
    struct Customer;

    struct CustomerGroup : std::list<Customer>
    {
        // customer group is a domain class that has application logic
        // std::list is an implementation class
        //
        // coupling domain logic with implementation is an easy mistake because
        // it starts out very conveniently and the downside of tight coupling
        // only becomes a problem after introducing more domain classes

        std::string GroupName() const;
        void AddCustomerToGroup(Customer customer);
    };
}