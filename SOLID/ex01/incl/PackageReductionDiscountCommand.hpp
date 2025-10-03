#ifndef PACKAGEREDUCTIONDISCOUNTCOMMAND_HPP
#define PACKAGEREDUCTIONDISCOUNTCOMMAND_HPP

#include "command.hpp"

class PackageReductionDiscountCommand : public Command {
private:
    Command* _wrappedCommand;
    double _threshold;
    double _reductionAmount;
    
public:
    PackageReductionDiscountCommand(Command* command, 
                                    double threshold = 150.0, 
                                    double reductionAmount = 10.0)
        : Command(command->getId(), command->getDate(), command->getClient()),
          _wrappedCommand(command), 
          _threshold(threshold), 
          _reductionAmount(reductionAmount) {
        std::vector<Article*> articles = command->getArticles();
        for (size_t i = 0; i < articles.size(); ++i) {
            _articles.push_back(articles[i]);
        }
    }
    
    virtual double get_total_price() const {
        double basePrice = _wrappedCommand->get_total_price();
        
        if (basePrice > _threshold) {
            std::cout << "[Package Reduction Applied: -" << _reductionAmount 
                      << " euros for orders over " << _threshold << " euros]" << std::endl;
            return basePrice - _reductionAmount;
        }
        
        return basePrice;
    }
    
    ~PackageReductionDiscountCommand() {
        _articles.clear();
    }
};


#endif