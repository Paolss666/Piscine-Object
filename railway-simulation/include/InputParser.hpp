#ifndef INPUTPARSER_HPP
#define INPUTPARSER_HPP

#include "RailwayNetwork.hpp"
#include "Train.hpp"
#include <string>
#include <vector>

/**
 * @class InputParser
 * @brief Parses input files for network and trains
 * 
 * SOLID: Single Responsibility - handles file parsing only
 * DRY: Reusable parsing methods
 */
class InputParser {
public:
    static RailwayNetwork* parseNetworkFile(const std::string& filename);
    static std::vector<Train*> parseTrainsFile(const std::string& filename, 
                                                RailwayNetwork* network);
    
    static void printUsage();
    static void printHelp();
    
private:
    InputParser(); // Utility class
    
    static void trim(std::string& str);
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static Time parseTime(const std::string& timeStr);
    static bool isValidNodeName(const std::string& name);
    static bool isValidNumber(const std::string& str);
};

#endif // INPUTPARSER_HPP
