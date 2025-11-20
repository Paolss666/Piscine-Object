#include "../incl/OutputWriter.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
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
    
    // One cell per kilometer of THIS segment
    int totalCells = std::max(1, static_cast<int>(std::ceil(snapshot.railLength)));
    if (totalCells > 50) totalCells = 50; // Limit visual size
    
    // Calculate train position on THIS segment (distance traveled from start)
    double distanceOnSegment = snapshot.railLength - snapshot.distanceRemaining;
    if (distanceOnSegment < 0.0) distanceOnSegment = 0.0;
    if (distanceOnSegment > snapshot.railLength) distanceOnSegment = snapshot.railLength;
    
    int trainCell = static_cast<int>(std::floor(distanceOnSegment));
    if (trainCell >= totalCells) trainCell = totalCells - 1;
    if (trainCell < 0) trainCell = 0;
    
    // Mark other trains (robustly accept km, percent (0-100), or fraction (0-1))
    std::vector<bool> otherAt(totalCells, false);
    for (size_t j = 0; j < snapshot.otherTrainPositions.size(); ++j) {
        double p = snapshot.otherTrainPositions[j];
        double posKm = 0.0;
        if (p < 0.0) continue;
        const double eps = 1e-6;
        if (p <= snapshot.railLength + eps) {
            // provided in kilometers
            posKm = p;
        } else if (p <= 1.0 + eps) {
            // fraction of segment (0..1)
            posKm = p * snapshot.railLength;
        } else if (p <= 100.0 + eps) {
            // percent (0..100)
            posKm = (p / 100.0) * snapshot.railLength;
        } else {
            // fallback treat as kilometers
            posKm = p;
        }
        if (posKm < 0.0) continue;
        if (posKm > snapshot.railLength) posKm = snapshot.railLength;
        int otherCell = static_cast<int>(std::floor(posKm));
        if (otherCell >= totalCells) otherCell = totalCells - 1;
        if (otherCell >= 0 && otherCell < totalCells) otherAt[otherCell] = true;
    }
    
    for (int i = 0; i < totalCells; ++i) {
        if (otherAt[i]) {
            // Other train blocks this cell (show 'O'). If both present, O takes precedence.
            oss << "[O]";
        } else if (i == trainCell) {
            oss << "[x]";
        } else {
            oss << "[ ]";
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
