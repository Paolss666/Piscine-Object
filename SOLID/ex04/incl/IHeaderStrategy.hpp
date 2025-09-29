#ifndef IHEADERSTRATEGY_HPP
#define IHEADERSTRATEGY_HPP

#include <string>

// Interface Segregation: Separate the header functionality
class IHeaderStrategy {
public:
    virtual ~IHeaderStrategy() {}
    virtual std::string getHeader() const = 0;
};

#endif