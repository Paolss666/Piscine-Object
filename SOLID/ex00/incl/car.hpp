#include <string>
#include <iostream>
#include "Engine.hpp"
#include "Transmission.hpp"
#include "Steering.hpp"
#include "Brakers.hpp"

#ifndef CAR_HPP
#define CAR_HPP

class Car{

private:
    Engine _engine;
    Transmission _transmission;
    Steering _steering;
    Brakers _brakes;

public: 
    Car(){};

    void start(){
        _engine.start();
        _transmission.gears_shift_up();
        _transmission.set_speed(0);
        std::cout << "Car started with gear " << _transmission.get_gear() << " and speed " << _transmission.get_speed() << std::endl;
    }

    void stop(){
        _engine.stop();
        _brakes.apply_force_on_brakes(100);
    };

    void reverse(){
        _transmission.reverse();
    }

    void accelerate(int speed){
        if (!_engine.is_running()){
            std::cout << "Engine is not running. Cannot accelerate." << std::endl;
            return;
        }
        _transmission.set_speed(speed);
        std::cout << "Car accelerated to " << _transmission.get_speed() << " km/h." << std::endl;
    }

    void shift_gears_up(){
        _transmission.gears_shift_up();
    }

    void shift_gears_down(){
        _transmission.gears_shift_down();
    }

    void turn_wheel(int angle){
        _steering.turn_wheel(angle);
    }

    void straighten_wheels(){
        _steering.straighten_wheels();
    }

    void apply_force_on_brakes(int force){
        _brakes.apply_force_on_brakes(force);
    }

    void apply_emergency_brakes(){
        _brakes.apply_emergency_brakes();
    }

    ~Car(){
        if (_engine.is_running()){
            stop();
        }
        std::cout << "Car destroyed" << std::endl;
    }

};


#endif // CAR_HPP