#include "../include/InputParser.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>

std::vector<Train*> InputParser::parseTrainsFile(const std::string& filename,
                                                   RailwayNetwork* network) {
    std::vector<Train*> trains;
    
    if (network == NULL) {
        std::cerr << "ERROR: Network is NULL" << std::endl;
        return trains;
    }
    
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "ERROR: Cannot open trains file: " << filename << std::endl;
        return trains;
    }
    
    std::string line;
    int lineNum = 0;
    
    while (std::getline(file, line)) {
        lineNum++;
        trim(line);
        
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        std::vector<std::string> tokens = split(line, ' ');
        
        if (tokens.size() != 9) {
            std::cerr << "ERROR at line " << lineNum 
                      << ": Train requires exactly 9 parameters" << std::endl;
            std::cerr << "Line: " << line << std::endl;
            continue;
        }
        
        try {
            std::string name = tokens[0];
            double weight = atof(tokens[1].c_str());
            double friction = atof(tokens[2].c_str());
            double maxAccel = atof(tokens[3].c_str());
            double maxBrake = atof(tokens[4].c_str());
            std::string depName = tokens[5];
            std::string destName = tokens[6];
            Time depTime = parseTime(tokens[7]);
            Time stopDuration = parseTime(tokens[8]);
            
            // Validation
            if (weight <= 0) {
                throw std::runtime_error("Weight must be positive");
            }
            if (friction < 0) {
                throw std::runtime_error("Friction coefficient must be non-negative");
            }
            if (maxAccel <= 0) {
                throw std::runtime_error("Max acceleration must be positive");
            }
            if (maxBrake <= 0) {
                throw std::runtime_error("Max brake force must be positive");
            }
            
            Node* departure = network->getNode(depName);
            Node* destination = network->getNode(destName);
            
            if (departure == NULL) {
                throw std::runtime_error("Unknown departure node: " + depName);
            }
            if (destination == NULL) {
                throw std::runtime_error("Unknown destination node: " + destName);
            }
            
            Train* train = new Train(name, weight, friction, maxAccel, maxBrake,
                                    departure, destination, depTime, stopDuration);
            trains.push_back(train);
            
        } catch (const std::exception& e) {
            std::cerr << "ERROR at line " << lineNum << ": " << e.what() << std::endl;
            std::cerr << "Line: " << line << std::endl;
        }
    }
    
    file.close();
    
    std::cout << "Trains loaded: " << trains.size() << std::endl;
    
    return trains;
}

void InputParser::printUsage() {
    std::cout << "Usage: ./railway_simulation <network_file> <trains_file>" << std::endl;
    std::cout << "   or: ./railway_simulation --help" << std::endl;
}

void InputParser::printHelp() {
    std::cout << "=== Railway Simulation Help ===" << std::endl << std::endl;
    
    std::cout << "USAGE:" << std::endl;
    std::cout << "  ./railway_simulation <network_file> <trains_file>" << std::endl << std::endl;
    
    std::cout << "NETWORK FILE FORMAT:" << std::endl;
    std::cout << "  Node <NodeName>" << std::endl;
    std::cout << "    - Defines a node (station or junction)" << std::endl;
    std::cout << "    - NodeName: any string without spaces" << std::endl << std::endl;
    
    std::cout << "  Rail <StartNode> <EndNode> <Length> <SpeedLimit>" << std::endl;
    std::cout << "    - Defines a rail segment between two nodes" << std::endl;
    std::cout << "    - Length: in kilometers (positive number)" << std::endl;
    std::cout << "    - SpeedLimit: in km/h (positive number)" << std::endl << std::endl;
    
    std::cout << "  Example network file:" << std::endl;
    std::cout << "    Node CityA" << std::endl;
    std::cout << "    Node CityB" << std::endl;
    std::cout << "    Node Junction1" << std::endl;
    std::cout << "    Rail CityA Junction1 15.0 250.0" << std::endl;
    std::cout << "    Rail Junction1 CityB 20.0 200.0" << std::endl << std::endl;
    
    std::cout << "TRAINS FILE FORMAT:" << std::endl;
    std::cout << "  <Name> <Weight> <Friction> <MaxAccel> <MaxBrake> <Departure> <Destination> <DepTime> <StopDuration>" << std::endl << std::endl;
    
    std::cout << "  Parameters:" << std::endl;
    std::cout << "    - Name: train identifier (no spaces)" << std::endl;
    std::cout << "    - Weight: in metric tons" << std::endl;
    std::cout << "    - Friction: coefficient (e.g., 0.05)" << std::endl;
    std::cout << "    - MaxAccel: maximum acceleration force in kN" << std::endl;
    std::cout << "    - MaxBrake: maximum brake force in kN" << std::endl;
    std::cout << "    - Departure: departure node name" << std::endl;
    std::cout << "    - Destination: destination node name" << std::endl;
    std::cout << "    - DepTime: departure time (format: HHhMM)" << std::endl;
    std::cout << "    - StopDuration: stop duration at stations (format: HHhMM)" << std::endl << std::endl;
    
    std::cout << "  Example trains file:" << std::endl;
    std::cout << "    TrainAB 80 0.05 356.0 30.0 CityA CityB 14h10 00h10" << std::endl;
    std::cout << "    TrainAC 60 0.05 412.0 40.0 CityA CityC 14h20 00h10" << std::endl << std::endl;
    
    std::cout << "OUTPUT:" << std::endl;
    std::cout << "  For each train, a file named <TrainName>_<DepartureTime>.result" << std::endl;
    std::cout << "  will be created containing the simulation results." << std::endl << std::endl;
}
