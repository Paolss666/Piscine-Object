#include <iostream>
#include <vector>
#include <memory>
#include "shape.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "circle.hpp"

/**
 * Function that demonstrates Liskov Substitution Principle
 * It accepts any shape object and works correctly without knowing the specific type
 */
void displayShapeInfo(const shape& shape) {
    shape.display();
    std::cout << std::endl;
}

/**
 * Function that calculates total area of multiple shapes
 * Demonstrates LSP - works with any collection of Shape-derived objects
 */
double calculateTotalArea(const std::vector<shape*>& shapes) {
    double total = 0.0;
    for (size_t i = 0; i < shapes.size(); ++i) {
        total += shapes[i]->area();
    }
    return total;
}

int main() {
    std::cout << "=== Shape Hierarchy Demonstration ===" << std::endl;
    std::cout << "Demonstrating Liskov Substitution Principle\n" << std::endl;
    
    try {
        // Create instances of different shapes
        rectangle rect(5.0, 3.0);
        triangle tri(3.0, 4.0, 5.0, 2.0);  // Right triangle
        circle circ(2.5);

        std::cout << "--- Individual Shape Information ---\n" << std::endl;
        
        // Demonstrate LSP: displayShapeInfo works with any Shape-derived object
        displayShapeInfo(rect);
        displayShapeInfo(tri);
        displayShapeInfo(circ);
        
        std::cout << "--- Working with Shapes Polymorphically ---\n" << std::endl;
        
        // Store different shapes in a container using base class pointers
        // This demonstrates LSP - we can treat all shapes uniformly
        std::vector<shape*> shapes;
        shapes.push_back(new rectangle(10.0, 5.0));
        shapes.push_back(new triangle(6.0, 8.0, 10.0, 5.0));
        shapes.push_back(new circle(3.0));
        shapes.push_back(new rectangle(7.0, 7.0)); // Square

        // Process all shapes uniformly
        std::cout << "Processing collection of shapes:" << std::endl;
        for (size_t i = 0; i < shapes.size(); ++i) {
            std::cout << (i + 1) << ". ";
            shapes[i]->display();
            std::cout << std::endl;
        }
        
        // Calculate total area using LSP
        double totalArea = calculateTotalArea(shapes);
        std::cout << "Total area of all shapes: " << totalArea << std::endl;
        
        std::cout << "\n--- Testing Error Handling ---\n" << std::endl;
        
        // Test invalid inputs
        try {
            rectangle invalidRect(-5.0, 3.0);
        } catch (const std::exception& e) {
            std::cout << "Caught expected exception: " << e.what() << std::endl;
        }
        
        try {
            triangle invalidTri(1.0, 2.0, 10.0, 3.0); // Violates triangle inequality
        } catch (const std::exception& e) {
            std::cout << "Caught expected exception: " << e.what() << std::endl;
        }
        
        try {
            circle invalidCirc(0.0);
        } catch (const std::exception& e) {
            std::cout << "Caught expected exception: " << e.what() << std::endl;
        }
        
        std::cout << "\n=== Demonstration Complete ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
