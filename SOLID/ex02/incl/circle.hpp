#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include <cmath>
#include <stdexcept>

class circle : public shape
{
private:
    double _radius;
public:
    circle(double radius) : _radius(radius) {
        if (radius <= 0) throw std::invalid_argument("Invalid radius for " + getType());
    }
    ~circle() {}

    virtual double area() const {
        return M_PI * _radius * _radius;
    }

    virtual double perimeter() const {
        return 2 * M_PI * _radius;
    }

    virtual std::string getType() const {
        return "Circle";
    }
};

#endif

