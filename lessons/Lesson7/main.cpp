#include "../gtest/MainTest.h"

// Refactoring: http://martinfowler.com/books/refactoring.html
// Refactoring is a controlled technique for improving the design of an existing code base.

// Code smell: http://martinfowler.com/bliki/CodeSmell.html
// Code smell is a surface indication that usually corresponds to a deeper problem in the system

// * Primitive obsession
// * Single instance vs. singleton and techniques in C++ to implement single instance
// * Complex conditional and how to refactor into smaller functions or classes
// * Dependency injection example
//
// * Cohesion as a way to gauge whether a class is single responsibility 
// * Coupling as a way to gauge whether a class has unclear responsibility
//
// * Composition vs. inheritance: how to choose?
// * Case study: composition vs. inheritance, the double dispatch problem
//
// * Case study: identify Code Smell

int main(int argc, char* argv[])
{
    testing::MainTest(argc, argv).Run();
}