#include "../include/OutputWriter.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

OutputWriter::OutputWriter(Train* train) : _train(train) {
    if (train != NULL) {
        std::ostringstream oss;
        oss << train->getName() << "_" << train->getDepartureTime().toString() << ".result";
        _filename = oss.str();
    }
}

OutputWriter::~OutputWriter() {
}

void OutputWriter::addSnapshot(const SimulationSnapshot& snapshot) {
    _snapshots.push_back(snapshot);
}

void OutputWriter::setEstimatedTime(const Time& time) {
    _estimatedTime = time;
}

void OutputWriter::onNotify(const std::string& event) {
    // Could log events
}

std::string OutputWriter::formatNode(const std::string& nodeName) const {
    // Format to fixed width for alignment
    std::ostringstream oss;
    oss << std::setw(10) << std::left << nodeName;
    return oss.str();
}

std::string OutputWriter::generateVisualGraph(const SimulationSnapshot& snapshot) const {
    std::ostringstream oss;
    
    int totalCells = static_cast<int>(snapshot.railLength);
    if (totalCells < 1) totalCells = 1;
    if (totalCells > 50) totalCells = 50; // Limit visual size
    
    int trainPosition = static_cast<int>((snapshot.progressPercent / 100.0) * totalCells);
    if (trainPosition >= totalCells) trainPosition = totalCells - 1;
    if (trainPosition < 0) trainPosition = 0;
    
    for (int i = 0; i < totalCells; ++i) {
        if (i == trainPosition) {
            oss << "[x]";
        } else {
            // Check if another train is here
            bool otherTrainHere = false;
            for (size_t j = 0; j < snapshot.otherTrainPositions.size(); ++j) {
                int otherPos = static_cast<int>((snapshot.otherTrainPositions[j] / 100.0) * totalCells);
                if (i == otherPos) {
                    otherTrainHere = true;
                    break;
                }
            }
            
            if (otherTrainHere) {
                oss << "[O]";
            } else {
                oss << "[ ]";
            }
        }
    }
    
    return oss.str();
}

void OutputWriter::writeToFile() {
    if (_train == NULL) {
        return;
    }
    
    std::ofstream outFile(_filename.c_str());
    if (!outFile.is_open()) {
        std::cerr << "ERROR: Cannot create output file: " << _filename << std::endl;
        return;
    }
    
    // Write header
    outFile << "Train: " << _train->getName() << std::endl;
    outFile << "Final travel time: " << _estimatedTime.toString() << std::endl;
    outFile << std::endl;
    
    // Write snapshots
    for (size_t i = 0; i < _snapshots.size(); ++i) {
        const SimulationSnapshot& snap = _snapshots[i];
        
        outFile << "[" << snap.time.toString() << "] - "
                << "[" << formatNode(snap.startNode) << "]"
                << "[" << formatNode(snap.endNode) << "] - "
                << "[" << std::fixed << std::setprecision(2) 
                << snap.distanceRemaining << "km] - "
                << "[" << std::setw(8) << snap.action << "] - "
                << generateVisualGraph(snap)
                << std::endl;
    }
    
    outFile.close();
    
    std::cout << "Output written to: " << _filename << std::endl;
}
