#ifndef OUTPUTWRITER_HPP
#define OUTPUTWRITER_HPP

#include "Train.hpp"
#include "IObserver.hpp"
#include <string>
#include <fstream>
#include <vector>

/**
 * @struct SimulationSnapshot
 * @brief Captures train state at a moment in time
 */
struct SimulationSnapshot {
    Time time;
    std::string startNode;
    std::string endNode;
    double distanceRemaining;
    std::string action;
    double progressPercent;
    double railLength;
    std::vector<double> otherTrainPositions;
    
    SimulationSnapshot() : distanceRemaining(0), progressPercent(0), railLength(0) {}
};

/**
 * @class OutputWriter
 * @brief Writes simulation results to output files
 * 
 * Implements Observer Pattern to record simulation events.
 * SOLID: Single Responsibility - handles output only
 */
class OutputWriter : public IObserver {
private:
    Train* _train;
    std::string _filename;
    std::vector<SimulationSnapshot> _snapshots;
    Time _estimatedTime;

public:
    OutputWriter(Train* train);
    ~OutputWriter();
    
    void addSnapshot(const SimulationSnapshot& snapshot);
    void setEstimatedTime(const Time& time);
    void writeToFile();
    
    // IObserver implementation
    virtual void onNotify(const std::string& event);
    
private:
    std::string generateVisualGraph(const SimulationSnapshot& snapshot) const;
    std::string formatNode(const std::string& nodeName) const;
};

#endif // OUTPUTWRITER_HPP
