#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
// Time structure

class Time {
public:
    int hours;
    int minutes;
    std::string toString() const;
    Time(int h = 0, int m = 0) : hours(h), minutes(m) {}
    void addMinutes(int mins) {
        minutes += mins;
        while (minutes >= 60) {
            minutes -= 60;
            hours += 1;
        }
        while (minutes < 0) {
            minutes += 60;
            hours -= 1;
        }
        hours = hours % 24;
    }
    int toMinutes() const {
        return hours * 60 + minutes;
    } 
    operator bool() const {
        return hours != 0 || minutes != 0;
    }
};

class Position {
public:
    class Rail* currentRail;
    class Node* lastNode;
    class Node* nextNode;
    double distanceOnRail; // in kilometers
};

enum TrainState {
    STATE_ACCELERATING,
    STATE_MAINTAINING,
    STATE_WAITING,
    STATE_STOPPED,
    STATE_BRAKING
};

#endif // TYPES_HPP

