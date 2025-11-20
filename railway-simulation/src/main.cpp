#include "../incl/SimulationManager.hpp"
#include "../incl/InputParser.hpp"
#include "../incl/OutputWriter.hpp"
#include "../incl/DijkstraPathfinding.hpp"
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
    
    // Track if trains have started moving
    std::vector<bool> hasStartedMoving(trains.size(), false);
    std::vector<Time> actualDepartureTime(trains.size());
    
    while (!sim->isComplete() && iteration < maxIterations) {
        sim->step();
        
        // Record snapshots for each train
        for (size_t i = 0; i < trains.size(); ++i) {
            Train* train = trains[i];
            
            // Check if train should have departed but hasn't moved
            if (train->getCurrentTime() >= train->getDepartureTime()) {
                if (!hasStartedMoving[i] && train->getState() != STATE_STOPPED) {
                    hasStartedMoving[i] = true;
                    actualDepartureTime[i] = train->getCurrentTime();
                    std::cout << "  Train " << train->getName() 
                              << " started moving at " << train->getCurrentTime().toString()
                              << " (scheduled: " << train->getDepartureTime().toString() << ")"
                              << std::endl;
                }
                
                // Debug: Check why train is stuck
                if (!hasStartedMoving[i] && iteration % 50 == 0) {
                    std::cout << "  WARNING: Train " << train->getName() 
                              << " still stopped at " << train->getCurrentTime().toString()
                              << " (scheduled departure: " << train->getDepartureTime().toString() << ")"
                              << " State: " << train->getStateString()
                              << std::endl;
                }
            }
            
            const Position& pos = train->getPosition();
            
            // Only record snapshots after departure time
            if (train->getCurrentTime() >= train->getDepartureTime() && 
                pos.currentRail != NULL && iteration % 1 == 0) {
                
                SimulationSnapshot snapshot;
                snapshot.time = train->getCurrentTime();
                snapshot.startNode = pos.lastNode ? pos.lastNode->getName() : "";
                snapshot.endNode = pos.nextNode ? pos.nextNode->getName() : "";
                snapshot.distanceRemaining = train->getTotalDistanceToGo();
                snapshot.action = train->getStateString();
                snapshot.railLength = pos.currentRail->getLength();
                snapshot.progressPercent = (pos.distanceOnRail / pos.currentRail->getLength()) * 100.0;
                
                // Populate other train positions
                snapshot.otherTrainPositions.clear();
                
                for (size_t j = 0; j < trains.size(); ++j) {
                    if (i == j) continue;
                    
                    Train* otherTrain = trains[j];
                    
                    // Check if other train has departed
                    if (otherTrain->getCurrentTime() < otherTrain->getDepartureTime()) {
                        continue;
                    }
                    
                    const Position& otherPos = otherTrain->getPosition();
                    
                    // Check if other train has a valid current rail
                    if (otherPos.currentRail == NULL) {
                        continue;
                    }
                    
                    // Check if on the same rail segment
                    if (otherPos.currentRail == pos.currentRail &&
                        otherPos.lastNode == pos.lastNode &&
                        otherPos.nextNode == pos.nextNode) {
                        
                        // Add the other train's position in kilometers
                        snapshot.otherTrainPositions.push_back(otherPos.distanceOnRail);
                    }
                }
                
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
    
    // Calculate final times and write outputs with proper day handling
    for (size_t i = 0; i < trains.size(); ++i) {
        // Get arrival and departure times
        Time arrivalTime = trains[i]->getCurrentTime();
        Time departureTime = trains[i]->getDepartureTime();
        
        // Convert to minutes for calculation
        int arrivalMinutes = arrivalTime.toMinutes();
        int departureMinutes = departureTime.toMinutes();
        
        // Handle day rollover (if arrival is next day)
        // This assumes the train journey is less than 24 hours
        if (arrivalMinutes < departureMinutes) {
            arrivalMinutes += 24 * 60; // Add 24 hours for next day
        }
        
        // Calculate travel time in minutes
        int travelMinutes = arrivalMinutes - departureMinutes;
        
        // Convert back to hours and minutes
        int travelHours = travelMinutes / 60;
        int travelMins = travelMinutes % 60;
        
        // Create proper travel time (handle cases over 24 hours if needed)
        Time travelTime(travelHours, travelMins);
        
        writers[i]->setEstimatedTime(travelTime);
        writers[i]->writeToFile();
        
        std::cout << "\nTrain " << trains[i]->getName() << " Summary:"
                  << "\n  Scheduled departure: " << departureTime.toString()
                  << "\n  Actual departure: " << (hasStartedMoving[i] ? 
                        actualDepartureTime[i].toString() : "Never departed")
                  << "\n  Arrival: " << arrivalTime.toString();
        
        // Show if arrival is next day
        if (arrivalTime.toMinutes() < departureTime.toMinutes()) {
            std::cout << " (next day)";
        }
        
        std::cout << "\n  Travel time: " << travelTime.toString() 
                  << " (" << travelMinutes << " minutes)" << std::endl;
                  
        // Check if train is still at origin
        const Position& finalPos = trains[i]->getPosition();
    }
    
    // Cleanup
    for (size_t i = 0; i < writers.size(); ++i) {
        delete writers[i];
    }
    
    SimulationManager::destroyInstance();
}

int main(int argc, char** argv) {
    // srand(time(NULL));
    
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
    
    // Print train information
    
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