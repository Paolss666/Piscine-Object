#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include <stdexcept>

class rectangle : public shape
{
private:
    double _width;
    double _height; 
public:
    rectangle(double width, double height) : _width(width), _height(height) {
        if (width <= 0 || height <= 0) throw std::invalid_argument("Invalid dimensions for " + getType());
    }

    virtual double area() const
    {
        return _width * _height;
    }

    virtual double perimeter() const
    {
        return 2 * (_width + _height);
    }

    virtual std::string getType() const 
    {
        return "Rectangle";
    }
};

#endif