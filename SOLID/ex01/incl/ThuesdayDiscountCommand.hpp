#ifndef THUESDAYDISCOUNT_HPP
#define THUESDAYDISCOUNT_HPP

#include "command.hpp"

class TuesdayDiscountCommand : public Command {
private:
    Command* _wrappedCommand;
    double _discountRate;
    
public:
    TuesdayDiscountCommand(Command* command, double discountRate = 0.10)
        : Command(command->getId(), command->getDate(), command->getClient()),
          _wrappedCommand(command), _discountRate(discountRate) {
        // Copy articles from wrapped command
        std::vector<Article*> articles = command->getArticles();
        for (size_t i = 0; i < articles.size(); ++i) {
            _articles.push_back(articles[i]);
        }
    }
    
    virtual double get_total_price() const {
        double basePrice = _wrappedCommand->get_total_price();
        
        // Apply discount only on Tuesday
        if (_date == "Tuesday") {
            std::cout << "[Tuesday Discount Applied: " << (_discountRate * 100) 
                      << "%]" << std::endl;
            return basePrice * (1.0 - _discountRate);
        }
        
        return basePrice;
    }
    
    ~TuesdayDiscountCommand() {
        _articles.clear();
    }
};

#endif