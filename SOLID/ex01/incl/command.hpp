#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <vector>

class Client{
    private:
        std::string _name;
    public:
        Client(const std::string& name) : _name(name) {}
        std::string getName() const { return _name; }
        ~Client() {}
};

class Article{
    private:
        std::string _title;
        double _price;
    public:
        Article(const std::string& title, double price) : _title(title), _price(price) {}
        std::string getTitle() const { return _title; }
        double getPrice() const { return _price; }
        ~Article() {}
};



class Command {
protected:
    int _id;
    std::string _date;
    Client _client;
    std::vector<Article*> _articles;
    
public:
    Command(int id, const std::string& date, const Client& client) 
        : _id(id), _date(date), _client(client), _articles() {}
    
    virtual void addArticle(Article* article) { 
        _articles.push_back(article); 
    }
    
    int getId() const { return _id; }
    std::string getDate() const { return _date; }
    Client getClient() const { return _client; }
    std::vector<Article*> getArticles() const { return _articles; }
    
    // Virtual method to allow decorators to override
    virtual double get_total_price() const {
        double total = 0.0;

        std::vector<Article*> articles = getArticles();
        for (size_t i = 0; i < articles.size(); ++i) {
            total += articles[i]->getPrice();
        }
        return total;
    }
    
    virtual void printInvoice() const {
        std::cout << "========================================" << std::endl;
        std::cout << "Command #" << _id << " - Date: " << _date << std::endl;
        std::cout << "Client: " << _client.getName() << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Articles:" << std::endl;
        
        double subtotal = 0.0;
        std::vector<Article*> articles = getArticles();
        for (size_t i = 0; i < articles.size(); ++i) {
            std::cout << "  - " << articles[i]->getTitle() 
                      << ": " << articles[i]->getPrice() << " euros" << std::endl;
            subtotal += articles[i]->getPrice();
        }
        
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Subtotal: " << subtotal << " euros" << std::endl;
        
        double total = get_total_price();
        if (total < subtotal) {
            std::cout << "Discount: -" << (subtotal - total) << " euros" << std::endl;
        }
        std::cout << "Total: " << total << " euros" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << std::endl;
    }
    
    virtual ~Command() {
        std::vector<Article*> articles = getArticles();
        for (size_t i = 0; i < articles.size(); ++i) {
            delete articles[i];
        }
    }
};

#endif