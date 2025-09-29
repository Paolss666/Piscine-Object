#ifndef HEADERSTRATEGY_HPP
#define HEADERSTRATEGY_HPP

#include <string>
#include "IHeaderStrategy.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

class ConstantHeader: public IHeaderStrategy {
    private:
    std::string _header;
public:
    ConstantHeader(const std::string &header): _header(header) {}
    ~ConstantHeader() {}
    std::string getHeader() const {
        return _header;
    }
};

class DateHeader : public IHeaderStrategy {
public:
    std::string getHeader() const {
        std::time_t now = std::time(NULL);
        std::tm* localTime = std::localtime(&now);
        
        std::ostringstream oss;
        oss << "[" 
            << std::setfill('0') << std::setw(4) << (localTime->tm_year + 1900) << "-"
            << std::setfill('0') << std::setw(2) << (localTime->tm_mon + 1) << "-"
            << std::setfill('0') << std::setw(2) << localTime->tm_mday << " "
            << std::setfill('0') << std::setw(2) << localTime->tm_hour << ":"
            << std::setfill('0') << std::setw(2) << localTime->tm_min << ":"
            << std::setfill('0') << std::setw(2) << localTime->tm_sec << "] ";
        
        return oss.str();
    }
};

#endif
