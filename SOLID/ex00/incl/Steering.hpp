#ifndef StEERING_HPP
#define StEERING_HPP

#include <iostream>

class Steering
{
private:
    double _angle;
public:
    Steering(): _angle(0) {};

    void turn_wheel(int angle) {
        if (angle < -45 || angle > 45) {
            std::cout << "Angle must be between -45 and 45 degrees" << std::endl;
            return;
        }
        _angle = angle;
        std::cout << "Steering wheel turned to " << _angle << " degrees" << std::endl;
    }
    
    void straighten_wheels() {
        _angle = 0;
        std::cout << "Steering wheel straightened" << std::endl;
    }

    double get_angle() const {
        return _angle;
    }

    ~Steering(){};
};



#endif