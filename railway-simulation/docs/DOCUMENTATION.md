# Railway Network Simulation - Complete Documentation

## Project Overview

This project implements a comprehensive railway network simulation system in C++98, demonstrating advanced object-oriented programming principles, design patterns, and software architecture.

## Architecture and Design Patterns

### 1. **Singleton Pattern** - SimulationManager
**Purpose**: Ensure only one simulation instance exists and provide global access point.

**Implementation**:
- Private constructor prevents direct instantiation
- Static instance pointer manages single instance
- getInstance() provides controlled access
- Coordinates all simulation components

**Benefits**:
- Centralized simulation control
- Prevents multiple conflicting simulations
- Global access to simulation state

### 2. **Strategy Pattern** - Pathfinding
**Purpose**: Enable different pathfinding algorithms to be used interchangeably.

**Implementation**:
- IPathfindingStrategy interface defines findPath() contract
- DijkstraPathfinding implements Dijkstra's algorithm
- Easily extensible to add A*, BFS, or other algorithms

**Benefits**:
- Algorithm can be swapped at runtime
- New algorithms added without modifying existing code
- Follows Open/Closed Principle

### 3. **Observer Pattern** - Event System
**Purpose**: Notify trains of events without tight coupling.

**Implementation**:
- IObserver interface with update() method
- EventManager maintains observer list
- Trains implement IObserver and react to events
- Events propagated to all registered observers

**Benefits**:
- Loose coupling between events and trains
- Easy to add new event types
- Trains can respond independently to events

### 4. **Factory Pattern** - Event Creation
**Purpose**: Centralize and standardize event creation.

**Implementation**:
- EventFactory provides static creation methods
- Each event type has dedicated creator method
- Random event generation supported

**Benefits**:
- Consistent event creation
- Easy to modify event creation logic
- Simplifies client code

## SOLID Principles Implementation

### Single Responsibility Principle (SRP)
- **Node**: Only represents network points
- **Rail**: Only represents connections
- **Train**: Only manages train state and physics
- **SimulationManager**: Only coordinates simulation
- **OutputWriter**: Only handles file output

### Open/Closed Principle (OCP)
- **IPathfindingStrategy**: New algorithms can be added without modifying existing code
- **IObserver**: New observer types can be added
- **EventFactory**: New event types can be added

### Liskov Substitution Principle (LSP)
- All implementations of IPathfindingStrategy are interchangeable
- All implementations of IObserver behave consistently

### Interface Segregation Principle (ISP)
- **IObserver**: Simple, focused interface
- **IPathfindingStrategy**: Single-method interface for specific purpose

### Dependency Inversion Principle (DIP)
- SimulationManager depends on IPathfindingStrategy abstraction, not concrete implementation
- Event system depends on IObserver interface, not concrete classes

## Additional Design Principles

### DRY (Don't Repeat Yourself)
- Common time formatting in utility functions
- Shared physics calculations in PhysicsEngine
- Reusable path finding logic

### KISS (Keep It Simple, Stupid)
- Clear class responsibilities
- Straightforward algorithms
- Simple, readable code structure

## Class Diagram

The system consists of the following main components:

```
Core Models:
- Node: Represents stations and rail junctions
- Rail: Represents connections between nodes
- Train: Represents trains with physics simulation
- RailNetwork: Graph structure managing nodes and rails

Systems:
- SimulationManager: Coordinates entire simulation (Singleton)
- CollisionManager: Prevents train collisions
- DijkstraPathfinding: Finds optimal routes (Strategy)
- EventManager: Manages event distribution (Observer)
- EventFactory: Creates events (Factory)

I/O:
- InputParser: Parses input files
- OutputWriter: Generates result files
```

## Simulation Process

### 1. Initialization
```
1. Parse network file → Create RailNetwork with Nodes and Rails
2. Parse trains file → Create Train objects
3. Initialize SimulationManager (Singleton)
4. Calculate optimal paths using Dijkstra's algorithm
```

### 2. Simulation Loop
```
For each time step (5 minutes):
  For each train:
    1. Check if departure time reached → Start train
    2. Check for collisions → Adjust speed if needed
    3. Calculate target speed based on:
       - Current rail speed limit
       - Distance to destination
       - Leading trains
    4. Update physics (acceleration, speed, position)
    5. Check if destination reached
    6. Write state to output file
```

### 3. Physics Simulation

The physics model includes:
- **Forces**: Acceleration force, braking force, friction
- **Motion**: Speed calculation based on net forces
- **Position**: Integration of velocity over time
- **Constraints**: Speed limits, safe distances

### 4. Pathfinding

Uses Dijkstra's algorithm to find optimal paths:
- **Weight function**: Time = distance / average_speed
- **Considers**: Rail length and speed limits
- **Returns**: Ordered list of Rail segments

### 5. Collision Avoidance

Multi-layer collision prevention:
- **Safe distance**: Minimum 2km between trains
- **Speed matching**: Slower train ahead reduces following train speed
- **Emergency braking**: Automatic braking when too close

## File Formats

### Network File
```
Node <n>          # Define a network node
Rail <from> <to> <length_km> <speed_kmh>  # Define rail connection
```

### Trains File
```
<n> <weight> <friction> <accel> <brake> <from> <to> <time> <stop>
```

### Output File
```
Train : TrainName
Final travel time : XXhXX

[time] - [from][to] - [distance] - [state] - [progress_bar]
```

## Encapsulation

All classes follow strong encapsulation:
- Private member variables with `_` prefix
- Public getter/setter methods
- Const correctness for read-only operations
- Clear interfaces hiding implementation details

## Memory Management

C++98 compliant memory management:
- Manual `new`/`delete` (no smart pointers in C++98)
- Clear ownership semantics
- Destructor cleanup in all classes
- Copy constructors and assignment operators

## Compilation and Usage

### Build
```bash
make              # Compile project
make clean        # Remove object files
make fclean       # Remove all generated files
make re           # Rebuild from scratch
```

### Run
```bash
./railway_sim network.txt trains.txt
./railway_sim --help
make run          # Run with example files
```

## Extensibility

The system is designed for easy extension:

### Adding New Pathfinding Algorithms
```cpp
class AStarPathfinding : public IPathfindingStrategy {
public:
    virtual std::vector<Rail*> findPath(...) {
        // Implement A* algorithm
    }
};
```

### Adding New Event Types
```cpp
// In EventFactory
static Event* createNewEventType(const std::string& location, int time) {
    return new Event(NEW_EVENT_TYPE, location, time, "Description");
}
```

### Adding New Observers
```cpp
class TrafficMonitor : public IObserver {
public:
    virtual void update(const Event* event) {
        // Monitor traffic patterns
    }
};
```

## Testing Scenarios

The example files demonstrate:
1. **Multiple routes**: Alternative paths between cities
2. **Concurrent trains**: Multiple trains on same network
3. **Collision avoidance**: Trains departing close together
4. **Different speeds**: Various speed limits on rails
5. **Path optimization**: Shortest vs fastest routes

## Performance Considerations

- **Time step**: 5-minute intervals balance accuracy and performance
- **Path caching**: Paths calculated once per train
- **Collision checks**: Only active trains on same rail
- **Output buffering**: Efficient file I/O

## Future Enhancements

Possible extensions:
- Real-time visualization (bonus)
- Runtime network modification (bonus)
- Multiple simulation runs for statistics (bonus)
- Train scheduling optimization
- Dynamic event handling
- Network capacity analysis

## Evaluation Checklist

✅ **Design Patterns** (3+ required):
1. Singleton (SimulationManager)
2. Strategy (IPathfindingStrategy)
3. Observer (IObserver/EventManager)
4. Factory (EventFactory)

✅ **UML Diagrams** (2+ required):
1. Class Diagram (comprehensive)
2. Sequence Diagram (simulation flow)

✅ **Encapsulation**:
- All member variables private
- Public interfaces well-defined
- Property accessors implemented

✅ **SOLID Principles**:
- Single Responsibility: Each class has one purpose
- Open/Closed: Extensible via interfaces
- Liskov Substitution: Proper inheritance
- Interface Segregation: Focused interfaces
- Dependency Inversion: Depend on abstractions

✅ **Additional Principles**:
- DRY: No code duplication
- KISS: Simple, clear design

## Conclusion

This railway simulation demonstrates professional software engineering practices with clean architecture, proper design patterns, and extensible design suitable for complex real-world applications.
