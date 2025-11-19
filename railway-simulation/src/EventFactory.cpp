#include "../incl/EventFactory.hpp"
#include <sstream>

// DelayEvent implementation
void DelayEvent::execute() {
    // Delay is applied in simulation manager
}

std::string DelayEvent::getDescription() const {
    std::ostringstream oss;
    oss << "Train delayed by " << _delayMinutes << " minutes";
    return oss.str();
}

// SpeedReductionEvent implementation
void SpeedReductionEvent::execute() {
    // Speed reduction would modify rail speed limit temporarily
}

std::string SpeedReductionEvent::getDescription() const {
    std::ostringstream oss;
    oss << "Speed reduced by " << _reductionPercent << "%";
    return oss.str();
}

// EventFactory implementation
IEvent* EventFactory::createRandomEvent(Train* train) {
    if (train == NULL) {
        return NULL;
    }
    
    int eventType = rand() % 2;
    
    switch (eventType) {
        case 0:
            return new DelayEvent(train, 5 + (rand() % 20)); // 5-25 min delay
        default:
            return NULL;
    }
}

IEvent* EventFactory::createRandomEvent(Rail* rail) {
    if (rail == NULL) {
        return NULL;
    }
    
    int eventType = rand() % 2;
    
    switch (eventType) {
        case 0:
            return new SpeedReductionEvent(rail, 10.0 + (rand() % 30)); // 10-40% reduction
        default:
            return NULL;
    }
}
