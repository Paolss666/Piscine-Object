#include "../incl/OutputWriter.hpp"
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
    // std::cout << "[Event] " << event << std::endl;
    (void)event;
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
    
    // The graph represents the CURRENT rail segment only (from startNode to endNode)
    // One cell per kilometer of THIS segment
    int totalCells = static_cast<int>(snapshot.railLength);
    if (totalCells < 1) totalCells = 1;
    if (totalCells > 50) totalCells = 50; // Limit visual size
    
    // Calculate train position on THIS segment
    // progressPercent should be: (distance_traveled_on_segment / segment_length) * 100
    // OR: 100 - (distance_remaining_on_segment / segment_length) * 100
    
    // If you're tracking distance remaining on the segment:
    double distanceOnSegment = snapshot.railLength - snapshot.distanceRemaining;
    if (distanceOnSegment < 0) distanceOnSegment = 0;
    if (distanceOnSegment > snapshot.railLength) distanceOnSegment = snapshot.railLength;
    
    double progressOnSegment = (distanceOnSegment / snapshot.railLength) * 100.0;
    int trainPosition = static_cast<int>((progressOnSegment / 100.0) * totalCells);
    
    if (trainPosition >= totalCells) trainPosition = totalCells - 1;
    if (trainPosition < 0) trainPosition = 0;
    
    for (int i = 0; i < totalCells; ++i) {
        if (i == trainPosition) {
            oss << "[x]";
        } else {
            // Check if another train is here
            bool otherTrainHere = false;
            for (size_t j = 0; j < snapshot.otherTrainPositions.size(); ++j) {
                // otherTrainPositions should contain positions on THIS segment (0-100%)
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
