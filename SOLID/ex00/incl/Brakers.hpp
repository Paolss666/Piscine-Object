#ifndef BRAKERS_HPP
#define BRAKERS_HPP

#include <iostream>

class Brakers
{
private:
    double _force;
public:
    Brakers(): _force(0) {};
    ~Brakers(){};

    void apply_force_on_brakes(int force) {
        if (force < 0) {
            std::cout << "Force cannot be negative" << std::endl;
            return;
        }
        _force = force;
        std::cout << "Applied force of " << _force << " on the brakes" << std::endl;
    }

    void apply_emergency_brakes() {
        _force = 100; // maximum force
        std::cout << "Emergency brake applied with force " << _force << std::endl;
    }

};

#endif