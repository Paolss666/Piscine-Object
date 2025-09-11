#include "../incl/Vector.hpp"


bool Graph::isValidPoint(const Vector2 &point) const
{
    return (point._x >= 0 && point._x <= _size._x && point._y >= 0 && point._y <= _size._y);
}

bool Graph::pointExists(const Vector2 &point) const
{
    for (std::vector<Vector2>::const_iterator it = _points.begin(); it != _points.end(); ++it)
    {
        if (*it == point)
            return true;
    }
    return false;
}


Graph::Graph(float width, float height) : _size(width, height)
{
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("Width and height must be positive values.");
}


Graph& Graph::operator=(const Graph& other)
{
    if (this != &other)
    {
        _size = other._size;
        _points = other._points;
    }
    return *this;
}

Graph::Graph(const Graph &g) : _size(g._size), _points(g._points) {}

void Graph::setSize(float width, float height)
{
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("Width and height must be positive values.");
    
    
    _size._x = width;
    _size._y = height;
    std::vector<Vector2> validPoints;
    for (std::vector<Vector2>::iterator it = _points.begin(); it != _points.end();  ++it)
    {
        if (isValidPoint(*it))
            validPoints.push_back(*it);
    }
    _points = validPoints;
}

void Graph::setSize(const Vector2 &size)
{
    setSize(size._x, size._y);
}


bool Graph::addPoint(float x, float y)
{
    return addPoint(Vector2(x, y));
}

bool Graph::addPoint(const Vector2 &point)
{
    if (!isValidPoint(point))
        throw std::out_of_range("Point is out of graph bounds.");
    if (pointExists(point))
        throw std::invalid_argument("Point already exists in the graph.");
    _points.push_back(point);
    return true;
}

bool Graph::removePoint(const Vector2 &point)
{
    if (!pointExists(point))
        throw std::invalid_argument("Point does not exist in the graph.");
    for (std::vector<Vector2>::iterator it = _points.begin(); it != _points.end(); ++it)
    {
        if (*it == point)
        {
            _points.erase(it);
            return true;
        }
    }
    return false;
}

void Graph::clearPoints()
{
    _points.clear();
}

int Graph::getPointCount() const
{
    return _points.size();
}

bool Graph::hasPoint(const Vector2 &point) const
{
    return pointExists(point);
}

bool Graph::hasPoint(float x, float y) const
{
    return pointExists(Vector2(x, y));
}

void Graph::display() const
{
    std::cout << *this;
}

void Graph::displayWithCoordinates() const
{
    std::cout << "Graph size: " << _size << std::endl;
    std::cout << "Points (" << getPointCount() << "):" << std::endl;
    
    for (std::vector<Vector2>::const_iterator it = _points.begin();
         it != _points.end(); ++it)
    {
        std::cout << "  " << *it << std::endl;
    }
    
    std::cout << "\nGraph visualization:" << std::endl;
    display();
}


std::ostream& operator<<(std::ostream& os, const Graph& graph)
{
    int width = static_cast<int>(graph._size._x);
    int height = static_cast<int>(graph._size._y);
    
    // Draw from top to bottom (reverse Y axis for display)
    for (int y = height - 1; y >= 0; --y)
    {
        // Print Y axis label
        os << y << " ";
        
        // Draw the row
        for (int x = 0; x < width; ++x)
        {
            bool hasPoint = false;
            
            // Check if there's a point at this position
            for (std::vector<Vector2>::const_iterator it = graph._points.begin();
                 it != graph._points.end(); ++it)
            {
                if (static_cast<int>(it->_x) == x && static_cast<int>(it->_y) == y)
                {
                    hasPoint = true;
                    break;
                }
            }
            
            if (hasPoint)
                os << "X ";
            else
                os << ". ";
        }
        os << std::endl;
    }
    
    // Print X axis labels
    os << "  ";
    for (int x = 0; x < width; ++x)
    {
        os << x << " ";
    }
    os << std::endl;
    
    return os;
}


Graph::~Graph() {
    _points.clear();

}