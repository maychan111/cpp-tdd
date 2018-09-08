#include <string>
#include <iostream>

namespace Lesson7
{
    // Code smell: A class contains data fields that have their own behavior and associated data.
    // https://sourcemaking.com/refactoring/replace-data-value-with-object

    class Order
    {
    public:
        Order(int orderNumber, int customerNumber, std::string customerName) : 
            _orderNumber(orderNumber),
            _customerNumber(customerNumber), _customerName(customerName)
        {
        }

        void PrintOrder() const
        {
            std::cout << "Order number is " << _orderNumber << std::endl;
            std::cout << "Customer number is " << _customerNumber << std::endl;
            std::cout << "Customer name is " << _customerName << std::endl;
        }

    private:
        int _orderNumber;
        int _customerNumber;
        std::string _customerName;
    };

    // scroll down after discussion














    // Recfactor: Improves relatedness inside classes. Data and the relevant behaviors are inside a single class.
    struct Customer
    {
        int _id;
        std::string _name;

        std::string ToString() const
        {
            std::cout << "Customer number is " << _id << std::endl;
            std::cout << "Customer name is " << _name << std::endl;
            return std::to_string(_id) + ": " + _name;
        }
    };

    class RefactoredOrder
    {
    public:
        RefactoredOrder(int orderNumber, Customer customer) : _orderNumber(orderNumber), _customer(std::move(customer))
        {
        }

        void PrintOrder() const
        {
            std::cout << "Order number is " << _orderNumber << std::endl;
            std::cout << _customer.ToString() << std::endl;
        }

    private:
        int _orderNumber;
        Customer _customer;
    };
}