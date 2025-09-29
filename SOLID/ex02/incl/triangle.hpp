#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"
#include <cmath>
#include <stdexcept>

class triangle : public shape
{
private:
    double _l1;
    double _l2;
    double _l3;
    double _height;
public:
    triangle(double l1, double l2, double l3, double height) : _l1(l1), _l2(l2), _l3(l3), _height(height) {
        if (l1 <= 0 || l2 <= 0 || l3 <= 0 || height <= 0)
            throw std::invalid_argument("Invalid dimensions for " + getType());
    }

    virtual double area() const {
        double s = perimeter() / 2.0; // semi-perimeter
        // Heron's formula
        return std::sqrt(s * (s - _l1) * (s - _l2) * (s - _l3));
    }

    virtual double perimeter() const
    {
        return _l1 + _l2 + _l3;
    }

    virtual std::string getType() const
    {
        return "Triangle";
    }
};

#endif