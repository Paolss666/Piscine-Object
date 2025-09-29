#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>

class Engine {

private:
    bool _running;
public:
    Engine(): _running(false) {
    }

    void start() {
        if (!_running) {
            _running = true;
            std::cout << "Engine started" << std::endl;
        } else {
            std::cout << "Engine is already running" << std::endl;
        }
    }

    void stop() {
        if (_running) {
            _running = false;
            std::cout << "Engine stopped" << std::endl;
        } else {
            std::cout << "Engine is already stopped" << std::endl;
        }
    }

    bool is_running() const {
        return _running;
    }

    ~Engine() {
        if (_running) {
            stop();
        }
        std::cout << "Engine destroyed" << std::endl;
    }

};

#endif