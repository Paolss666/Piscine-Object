#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <iomanip>
#include <string>
// Liskov substitution principle
// Subtypes must be substitutable for their base types without affecting the correctness of the program

class shape
{
public:
    virtual  ~shape(){};

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string getType() const = 0;

    void display() const
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Shape: " << getType() << ", Area: " << area() << ", Perimeter: " << perimeter() << std::endl;
    }
};


#endif