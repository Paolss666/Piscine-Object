#include "../include/InputParser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

void InputParser::trim(std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        str = "";
        return;
    }
    size_t end = str.find_last_not_of(" \t\r\n");
    str = str.substr(start, end - start + 1);
}

std::vector<std::string> InputParser::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        trim(token);
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

Time InputParser::parseTime(const std::string& timeStr) {
    // Format: XXhXX
    size_t hPos = timeStr.find('h');
    if (hPos == std::string::npos) {
        throw std::runtime_error("Invalid time format: " + timeStr);
    }
    
    int hours = atoi(timeStr.substr(0, hPos).c_str());
    int minutes = atoi(timeStr.substr(hPos + 1).c_str());
    
    return Time(hours, minutes);
}

bool InputParser::isValidNodeName(const std::string& name) {
    return !name.empty() && name.find_first_of(" \t\r\n") == std::string::npos;
}

bool InputParser::isValidNumber(const std::string& str) {
    if (str.empty()) return false;
    
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') start = 1;
    
    bool hasDigit = false;
    bool hasDot = false;
    
    for (size_t i = start; i < str.length(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            hasDigit = true;
        } else if (str[i] == '.' && !hasDot) {
            hasDot = true;
        } else {
            return false;
        }
    }
    
    return hasDigit;
}

RailwayNetwork* InputParser::parseNetworkFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "ERROR: Cannot open network file: " << filename << std::endl;
        return NULL;
    }
    
    RailwayNetwork* network = new RailwayNetwork();
    std::string line;
    int lineNum = 0;
    
    while (std::getline(file, line)) {
        lineNum++;
        trim(line);
        
        if (line.empty() || line[0] == '#') {
            continue; // Skip empty lines and comments
        }
        
        std::vector<std::string> tokens = split(line, ' ');
        
        if (tokens.empty()) {
            continue;
        }
        
        try {
            if (tokens[0] == "Node") {
                if (tokens.size() != 2) {
                    throw std::runtime_error("Node requires exactly 1 argument");
                }
                
                if (!isValidNodeName(tokens[1])) {
                    throw std::runtime_error("Invalid node name: " + tokens[1]);
                }
                
                network->addNode(tokens[1]);
                
            } else if (tokens[0] == "Rail") {
                if (tokens.size() != 5) {
                    throw std::runtime_error("Rail requires exactly 4 arguments");
                }
                
                if (!isValidNodeName(tokens[1]) || !isValidNodeName(tokens[2])) {
                    throw std::runtime_error("Invalid node names");
                }
                
                if (!isValidNumber(tokens[3]) || !isValidNumber(tokens[4])) {
                    throw std::runtime_error("Invalid numeric values");
                }
                
                double length = atof(tokens[3].c_str());
                double speedLimit = atof(tokens[4].c_str());
                
                if (length <= 0) {
                    throw std::runtime_error("Rail length must be positive");
                }
                
                if (speedLimit <= 0) {
                    throw std::runtime_error("Speed limit must be positive");
                }
                
                if (!network->hasNode(tokens[1])) {
                    throw std::runtime_error("Unknown node: " + tokens[1]);
                }
                
                if (!network->hasNode(tokens[2])) {
                    throw std::runtime_error("Unknown node: " + tokens[2]);
                }
                
                network->addRail(tokens[1], tokens[2], length, speedLimit);
                
            } else {
                throw std::runtime_error("Unknown command: " + tokens[0]);
            }
            
        } catch (const std::exception& e) {
            std::cerr << "ERROR at line " << lineNum << ": " << e.what() << std::endl;
            std::cerr << "Line content: " << line << std::endl;
            delete network;
            file.close();
            return NULL;
        }
    }
    
    file.close();
    
    std::cout << "Network loaded: " << network->getNodeCount() 
              << " nodes, " << network->getRailCount() << " rails" << std::endl;
    
    return network;
}
