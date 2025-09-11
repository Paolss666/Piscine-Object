#include "../incl/Vector.hpp"

int main()
{
    try
    {
        Graph graph(10.0f, 10.0f);
        graph.addPoint(Vector2(2.0f, 3.0f));
        graph.addPoint(Vector2(5.0f, 5.0f));
        graph.addPoint(Vector2(7.0f, 8.0f));
        graph.displayWithCoordinates();

        std::cout << "\nRemoving point (5, 5):" << std::endl;
        graph.removePoint(Vector2(5.0f, 5.0f));
        graph.displayWithCoordinates();

        std::cout << "\nClearing all points:" << std::endl;
        graph.clearPoints();
        graph.displayWithCoordinates();

        std::cout << "\nAttempting to add an out-of-bounds point (15, 15):" << std::endl;
        graph.addPoint(Vector2(15.0f, 15.0f));

    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}