#include "../incl/HeaderStrategy.hpp"
#include "../incl/Logger.hpp"
#include <vector>
#include <iostream>

int main() {
    // Create header strategies
    ConstantHeader constantHeader("[INFO] ");
    DateHeader dateHeader;
    
    // Create various loggers
    std::vector<ILogger*> loggers;
    
    // File logger without header
    FileLogger fileLogger("log_no_header.txt");
    loggers.push_back(&fileLogger);
    
    // File logger with constant header
    FileLoggerWithHeader fileLoggerConstant("log_constant_header.txt", &constantHeader);
    loggers.push_back(&fileLoggerConstant);
    
    // File logger with date header
    FileLoggerWithHeader fileLoggerDate("log_date_header.txt", &dateHeader);
    loggers.push_back(&fileLoggerDate);
    
    // Create a single reference to std::cout that will be used by all stream loggers
    std::ostream& stream = std::cout;
    
    // Stream logger without header (to std::cout)
    StreamLogger streamLogger(stream);
    loggers.push_back(&streamLogger);
    
    // Stream logger with constant header
    StreamLoggerWithHeader streamLoggerConstant(stream, &constantHeader);
    loggers.push_back(&streamLoggerConstant);
    
    // Stream logger with date header
    StreamLoggerWithHeader streamLoggerDate(stream, &dateHeader);
    loggers.push_back(&streamLoggerDate);
    
    // Create list of messages to log
    std::vector<std::string> messages;
    messages.push_back("Application started successfully");
    messages.push_back("Processing user request");
    messages.push_back("Database connection established");
    messages.push_back("Operation completed");
    messages.push_back("Application shutting down");
    
    // Test: iterate through all messages and log with each logger
    std::cout << "=== Testing all loggers ===" << std::endl;
    std::cout << std::endl;
    
    for (size_t i = 0; i < messages.size(); ++i) {
        std::cout << "--- Logging message " << (i + 1) << ": \"" 
                  << messages[i] << "\" ---" << std::endl;
        
        for (size_t j = 0; j < loggers.size(); ++j) {
            loggers[j]->write(messages[i]);
        }
        
        std::cout << std::endl;
    }
    
    std::cout << "=== Logging complete ===" << std::endl;
    std::cout << "Check the generated log files:" << std::endl;
    std::cout << "  - log_no_header.txt" << std::endl;
    std::cout << "  - log_constant_header.txt" << std::endl;
    std::cout << "  - log_date_header.txt" << std::endl;
    
    return 0;
}