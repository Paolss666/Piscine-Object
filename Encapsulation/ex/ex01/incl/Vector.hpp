#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

class Vector2
{
    public:
    float _x;
    float _y;
    Vector2(float x, float y) : _x(x), _y(y) {};
    // Copy constructor

    Vector2(const Vector2 &v) : _x(v._x), _y(v._y) {};
    //Assginament operator
    Vector2& operator=(const Vector2 &v)
    {
        if (this != &v)
        {
            _x = v._x;
            _y = v._y;
        }
        return *this;
    };

    bool operator==(const Vector2 &v) const
    {
        return (_x == v._x && _y == v._y);
    };

    bool operator!=(const Vector2 &v) const
    {
        return !(*this == v);
    };

    // Output operator
    friend std::ostream& operator<<(std::ostream &os, const Vector2 &v)
    {
        os << "Vector2(" << v._x << ", " << v._y << ")";
        return os;
    }

    ~Vector2(){};
};



class Graph
{
private:
    Vector2 _size;
    std::vector<Vector2> _points; 

    bool isValidPoint(const Vector2 &point) const;
    bool pointExists(const Vector2 &point) const;
    // void drawAxis() const;
    // void drawGrid() const;

public:
    
    Graph(float width = 10.0f, float height = 10.0f);

    // copy constructor
    Graph(const Graph &g);

    // Assignment operator
    Graph& operator=(const Graph &g);

    // Setters
    void setSize(float width, float height);
    void setSize(const Vector2 &size);
    bool addPoint(const Vector2 &point);
    bool addPoint(float x, float y);
    bool removePoint(const Vector2 &point);
    void clearPoints();

    // Getters

    int getPointCount() const;
    bool hasPoint(const Vector2 &point) const;
    bool hasPoint(float x, float y) const;


    // Display
    void display() const;
    void displayWithCoordinates() const;


    // friend output operator
    friend std::ostream& operator<<(std::ostream &os, const Graph &g);
    ~Graph();
};




#endif