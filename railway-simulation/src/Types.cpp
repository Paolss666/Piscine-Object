#include "../include/Types.hpp"
#include <sstream>
#include <iomanip>

std::string Time::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours 
        << "h" << std::setw(2) << minutes;
    return oss.str();
}
