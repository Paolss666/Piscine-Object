#include "include/SimulationManager.hpp"
#include "include/InputParser.hpp"
#include "include/OutputWriter.hpp"
#include "include/DijkstraPathfinding.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

void runSimulation(RailwayNetwork* network, std::vector<Train*>& trains) {
    SimulationManager* sim = SimulationManager::getInstance();
    
    sim->setNetwork(network);
    sim->setPathfindingStrategy(new DijkstraPathfinding());
    
    // Add all trains
    for (size_t i = 0; i < trains.size(); ++i) {
        sim->addTrain(trains[i]);
    }
    
    // Create output writers for each train
    std::vector<OutputWriter*> writers;
    for (size_t i = 0; i < trains.size(); ++i) {
        OutputWriter* writer = new OutputWriter(trains[i]);
        writers.push_back(writer);
        sim->attach(writer);
    }
    
    std::cout << "\n=== Initializing Simulation ===" << std::endl;
    sim->initialize();
    
    std::cout << "=== Running Simulation ===" << std::endl;
    
    Time startTime = sim->getCurrentTime();
    int maxIterations = 5000;
    int iteration = 0;
    
    while (!sim->isComplete() && iteration < maxIterations) {
        sim->step();
        
        // Record snapshots for each train
        for (size_t i = 0; i < trains.size(); ++i) {
            Train* train = trains[i];
            
            if (train->getCurrentTime() < train->getDepartureTime()) {
                continue; // Not departed yet
            }
            
            const Position& pos = train->getPosition();
            
            if (pos.currentRail != NULL && iteration % 1 == 0) { // Record every step
                SimulationSnapshot snapshot;
                snapshot.time = train->getCurrentTime();
                snapshot.startNode = pos.lastNode ? pos.lastNode->getName() : "";
                snapshot.endNode = pos.nextNode ? pos.nextNode->getName() : "";
                snapshot.distanceRemaining = train->getTotalDistanceToGo();
                snapshot.action = train->getStateString();
                snapshot.railLength = pos.currentRail->getLength();
                snapshot.progressPercent = (pos.distanceOnRail / pos.currentRail->getLength()) * 100.0;
                
                writers[i]->addSnapshot(snapshot);
            }
        }
        
        iteration++;
        
        // Progress indicator
        if (iteration % 100 == 0) {
            std::cout << "  Simulation step: " << iteration 
                      << " | Time: " << sim->getCurrentTime().toString() << std::endl;
        }
    }
    
    std::cout << "\n=== Simulation Complete ===" << std::endl;
    std::cout << "Total iterations: " << iteration << std::endl;
    
    // Calculate final times and write outputs
    for (size_t i = 0; i < trains.size(); ++i) {
        Time travelTime = trains[i]->getCurrentTime();
        travelTime.addMinutes(-trains[i]->getDepartureTime().toMinutes());
        
        writers[i]->setEstimatedTime(travelTime);
        writers[i]->writeToFile();
        
        std::cout << "Train " << trains[i]->getName() 
                  << " - Travel time: " << travelTime.toString() << std::endl;
    }
    
    // Cleanup
    for (size_t i = 0; i < writers.size(); ++i) {
        delete writers[i];
    }
    
    SimulationManager::destroyInstance();
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    
    // Check arguments
    if (argc == 2 && std::string(argv[1]) == "--help") {
        InputParser::printHelp();
        return 0;
    }
    
    if (argc != 3) {
        std::cerr << "ERROR: Invalid number of arguments" << std::endl;
        InputParser::printUsage();
        return 1;
    }
    
    std::cout << "=== Railway Network Simulation ===" << std::endl;
    std::cout << "Network file: " << argv[1] << std::endl;
    std::cout << "Trains file: " << argv[2] << std::endl << std::endl;
    
    // Parse network
    std::cout << "=== Loading Network ===" << std::endl;
    RailwayNetwork* network = InputParser::parseNetworkFile(argv[1]);
    if (network == NULL) {
        std::cerr << "ERROR: Failed to parse network file" << std::endl;
        return 1;
    }
    
    // Parse trains
    std::cout << "\n=== Loading Trains ===" << std::endl;
    std::vector<Train*> trains = InputParser::parseTrainsFile(argv[2], network);
    if (trains.empty()) {
        std::cerr << "ERROR: No trains loaded" << std::endl;
        delete network;
        return 1;
    }
    
    // Run simulation
    try {
        runSimulation(network, trains);
    } catch (const std::exception& e) {
        std::cerr << "ERROR during simulation: " << e.what() << std::endl;
        
        // Cleanup
        for (size_t i = 0; i < trains.size(); ++i) {
            delete trains[i];
        }
        delete network;
        return 1;
    }
    
    // Cleanup
    for (size_t i = 0; i < trains.size(); ++i) {
        delete trains[i];
    }
    delete network;
    
    std::cout << "\n=== Simulation Finished Successfully ===" << std::endl;
    
    return 0;
}
