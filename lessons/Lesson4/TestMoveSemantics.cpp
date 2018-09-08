#include "Resource.h"
#include <string>
#include <list>

namespace
{
    using namespace testing;

    // a good explanation: http://thbecker.net/articles/rvalue_references/section_01.html
    //
    // Why rvalue reference? May lead to faster code if you use rvalue reference.
    // How? Compiler calls move constructor/assignment when possible
    //
    // lvalue : an expression that refers to a memory location and allows us to take the address of that memory location
    // rvalue : an expression that is not a lvalue

    Resource CreateSingleResource()
    {
        return Resource(7000);
    }

    Resource CreateSingleResourceBadly()
    {
        // std::move caused Resource(7000) to become lvalue return value optimization cannot be
        // performed on a lvalue
        auto r = std::move(Resource(7000));
        return r;
    }

    TEST(MoveSemantics, Construct)
    {
        std::cout << "Resource r1;" << std::endl;
        Resource r1; 

        std::cout << "Resource r2{ 1, 2, 3, 4, 5 };" << std::endl;
        Resource r2{ 1, 2, 3, 4, 5 };

        std::cout << "Resource r3 = r2;" << std::endl;
        Resource r3 = r2;

        std::cout << "Resource r4 = std::move(r2);" << std::endl;
        Resource r4 = std::move(r2); // cast r2, a lvalue to a rvalue

        std::cout << "Resource r5{ 1, 2, 3, 4 };" << std::endl;
        Resource r5{ 1, 2, 3, 4 };

        std::cout << "Resource r6 = CreateSingleResource();" << std::endl;
        Resource r6 = CreateSingleResource();

        std::cout << "Resource r7 = CreateSingleResourceBadly();" << std::endl;
        Resource r7 = CreateSingleResourceBadly();
    }

    TEST(MoveSemantics, Assignment)
    {
        Resource r;  // r is a lvalue
        r = Resource({ 1, 2, 3, 4, 5 });  // rhs is rvalue
        r = CreateSingleResource(); // CreateSingleResource() is a rvalue
    }

    TEST(MoveSemantics, RValueReference)
    {
        std::list<Resource> resources;

        resources.emplace_back(std::initializer_list<int>{ 10, 11, 12, 13 });
        resources.emplace_back(34);
        resources.emplace_back();
        
        auto temp = Resource{ 1, 2 };
        resources.emplace_back(std::move(temp));
    }

    template <typename ...Params>
    Resource ResourceFactory(Params&&... params)
    {
        return Resource(std::forward<Params>(params)...);
    }

    TEST(MoveSemantics, PerfectForwarding)
    {        
        int num = 3;

        auto r1 = ResourceFactory(num);
        auto r2 = ResourceFactory(3);
        auto r3 = ResourceFactory(std::initializer_list<int>{ 1, 2, num });
    }
}