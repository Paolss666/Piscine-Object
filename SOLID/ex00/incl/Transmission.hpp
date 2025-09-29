#ifndef TRANSMISSION_HPP
#define TRANSMISSION_HPP

#include <iostream>

class Transmission {

    private:
        int _gear;
        bool _in_reverse;
        int _current_speed;

    public:
    Transmission(): _gear(0), _in_reverse(false), _current_speed(0) {
        std::cout << "Transmission created" << std::endl;
    }
    
    ~Transmission() {}

    void gears_shift_up() {
        if (_in_reverse) {
            std::cout << "Cannot shift up while in reverse" << std::endl;
            return;
        }
        if (_gear < 5) {
            _gear++;
            std::cout << "Shifted up to gear " << _gear << std::endl;
        } else {
            std::cout << "Already in highest gear" << std::endl;
        }
    }

    void gears_shift_down() {
        if (_in_reverse) {
            std::cout << "Cannot shift down while in reverse" << std::endl;
            return;
        }
        if (_gear > 0) {
            _gear--;
            std::cout << "Shifted down to gear " << _gear << std::endl;
        } else {
            std::cout << "Already in lowest gear" << std::endl;
        }
    }

    void reverse() {
        if (_current_speed == 0) {
            _in_reverse = true;
            _gear = -1;
            std::cout << "Car is now in reverse" << std::endl;
        } else {
            std::cout << "Cannot reverse while moving" << std::endl;
        }
    }

    void set_speed(int speed) {
        if (speed < 0) {
            std::cout << "Speed cannot be negative" << std::endl;
            return;
        }
        _current_speed = speed;
        if (_current_speed == 0) {
            _in_reverse = false;
            _gear = 0;
            std::cout << "Car is stationary, gear set to neutral" << std::endl;
        }
        std::cout << "Current speed set to " << _current_speed << " km/h" << std::endl;
    }

    int get_gear() const {
        return _gear;
    }

    int get_speed() const {
        return _current_speed;
    }

};

#endif
