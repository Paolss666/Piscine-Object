#include "../incl/car.hpp"

int main() {
    std::cout << "=== Creating a new car ===" << std::endl;
    Car myCar;

    std::cout << "\n=== Starting the car ===" << std::endl;
    myCar.start();

    std::cout << "\n=== Accelerating ===" << std::endl;
    myCar.accelerate(20);
    myCar.shift_gears_up();
    myCar.accelerate(30);
    myCar.shift_gears_up();

    std::cout << "\n=== Turning ===" << std::endl;
    myCar.turn_wheel(45.0);
    myCar.straighten_wheels();

    std::cout << "\n=== Normal braking ===" << std::endl;
    myCar.apply_force_on_brakes(300.0);

    std::cout << "\n=== More acceleration ===" << std::endl;
    myCar.accelerate(50);
    myCar.shift_gears_up();

    std::cout << "\n=== Emergency situation ===" << std::endl;
    myCar.apply_emergency_brakes();

    std::cout << "\n=== Reversing ===" << std::endl;
    myCar.reverse();
    myCar.shift_gears_down();

    std::cout << "\n=== Stopping the car ===" << std::endl;
    myCar.stop();

    std::cout << "\n=== Trying to accelerate with engine off ===" << std::endl;
    myCar.accelerate(10);

    return 0;
}

