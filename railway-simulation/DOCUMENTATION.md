# Documentazione Tecnica - Railway Simulation

## Indice

1. [Architettura del Sistema](#architettura-del-sistema)
2. [Design Patterns](#design-patterns)
3. [Principi SOLID](#principi-solid)
4. [Componenti Principali](#componenti-principali)
5. [Algoritmi](#algoritmi)
6. [Fisica della Simulazione](#fisica-della-simulazione)

---

## Architettura del Sistema

### Panoramica

Il sistema è strutturato in 6 layer principali:

```
┌─────────────────────────────────────┐
│     Main Application Layer          │
├─────────────────────────────────────┤
│     I/O Layer (Parser, Writer)      │
├─────────────────────────────────────┤
│  Simulation Management (Singleton)  │
├─────────────────────────────────────┤
│  Business Logic (Pathfinding, etc.) │
├─────────────────────────────────────┤
│     Core Models (Train, Rail...)    │
├─────────────────────────────────────┤
│     Base Types & Interfaces         │
└─────────────────────────────────────┘
```

### Separazione delle Responsabilità

- **Models**: Rappresentano le entità del dominio
- **Strategies**: Implementano algoritmi intercambiabili
- **Observers**: Gestiscono notifiche ed eventi
- **Factories**: Creano oggetti complessi
- **Managers**: Coordinano le operazioni

---

## Design Patterns

### 1. Singleton Pattern

**Classe**: `SimulationManager`

**Problema Risolto**: Necessità di un punto di controllo centralizzato per l'intera simulazione.

**Implementazione**:
```cpp
class SimulationManager {
private:
    static SimulationManager* _instance;
    SimulationManager();  // Costruttore privato
    
public:
    static SimulationManager* getInstance();
    static void destroyInstance();
};
```

**Vantaggi**:
- Unica istanza garantita
- Accesso globale controllato
- Inizializzazione lazy

**Uso nel Progetto**:
```cpp
SimulationManager* sim = SimulationManager::getInstance();
sim->setNetwork(network);
sim->run();
SimulationManager::destroyInstance();
```

---

### 2. Strategy Pattern

**Interfaccia**: `IPathfindingStrategy`

**Problema Risolto**: Necessità di algoritmi di pathfinding intercambiabili.

**Implementazione**:
```cpp
class IPathfindingStrategy {
public:
    virtual ~IPathfindingStrategy() {}
    virtual std::vector<Node*> findPath(Node* start, Node* end) = 0;
};

class DijkstraPathfinding : public IPathfindingStrategy {
public:
    virtual std::vector<Node*> findPath(Node* start, Node* end);
};
```

**Vantaggi**:
- Algoritmi intercambiabili a runtime
- Facile aggiungere nuovi algoritmi (A*, BFS, etc.)
- Open/Closed Principle

**Uso nel Progetto**:
```cpp
sim->setPathfindingStrategy(new DijkstraPathfinding());
// Facilmente sostituibile con:
// sim->setPathfindingStrategy(new AStarPathfinding());
```

---

### 3. Observer Pattern

**Interfacce**: `IObserver`, `ISubject`

**Problema Risolto**: Notificare componenti interessati agli eventi della simulazione.

**Implementazione**:
```cpp
class IObserver {
public:
    virtual void onNotify(const std::string& event) = 0;
};

class ISubject {
protected:
    std::vector<IObserver*> _observers;
public:
    void attach(IObserver* observer);
    void notify(const std::string& event);
};
```

**Vantaggi**:
- Accoppiamento ridotto
- Facile aggiungere nuovi observers
- Notifiche automatiche

**Uso nel Progetto**:
```cpp
OutputWriter* writer = new OutputWriter(train);
sim->attach(writer);  // Writer riceve notifiche automaticamente
```

---

### 4. Factory Pattern

**Classe**: `EventFactory`

**Problema Risolto**: Creazione centralizzata di eventi casuali.

**Implementazione**:
```cpp
class EventFactory {
public:
    static IEvent* createRandomEvent(Train* train);
    static IEvent* createRandomEvent(Rail* rail);
};
```

**Vantaggi**:
- Creazione centralizzata
- Facile aggiungere nuovi tipi di eventi
- Incapsulamento della logica di creazione

**Tipi di Eventi**:
- `DelayEvent`: Ritarda un treno
- `SpeedReductionEvent`: Riduce velocità su un binario

---

## Principi SOLID

### Single Responsibility Principle (SRP)

Ogni classe ha una singola responsabilità:

- `Node`: Gestisce solo informazioni sul nodo
- `Rail`: Gestisce solo informazioni sul binario
- `Train`: Gestisce solo stato e comportamento del treno
- `RailwayNetwork`: Gestisce solo struttura della rete
- `SimulationManager`: Coordina solo la simulazione
- `InputParser`: Si occupa solo del parsing
- `OutputWriter`: Si occupa solo dell'output

### Open/Closed Principle (OCP)

Il sistema è aperto all'estensione ma chiuso alle modifiche:

```cpp
// Nuovo algoritmo pathfinding senza modificare codice esistente
class AStarPathfinding : public IPathfindingStrategy {
    virtual std::vector<Node*> findPath(Node* start, Node* end);
};

// Nuovo tipo di evento senza modificare EventFactory
class MaintenanceEvent : public IEvent {
    virtual void execute();
};
```

### Liskov Substitution Principle (LSP)

Le implementazioni sono sostituibili con le interfacce:

```cpp
IPathfindingStrategy* pathfinder = new DijkstraPathfinding();
// Sostituibile con qualsiasi altra implementazione
pathfinder = new AStarPathfinding();
```

### Interface Segregation Principle (ISP)

Interfacce specifiche e mirate:

- `IPathfindingStrategy`: Solo pathfinding
- `IObserver`: Solo notifiche
- `IEvent`: Solo eventi

Non esiste un'interfaccia "monolitica" che forza implementazioni inutili.

### Dependency Inversion Principle (DIP)

Dipendenze verso astrazioni:

```cpp
// SimulationManager dipende dall'interfaccia, non dall'implementazione
class SimulationManager {
    IPathfindingStrategy* _pathfinder;  // Interfaccia!
    // Non: DijkstraPathfinding* _pathfinder;
};
```

---

## Componenti Principali

### Node (Nodo)

**Responsabilità**: Rappresenta un punto nella rete (città o giunzione)

**Attributi Chiave**:
- `_name`: Nome identificativo
- `_connectedRails`: Binari collegati
- `_isCity`: Flag città/giunzione

**Metodi Principali**:
- `getRailTo()`: Trova binario verso destinazione
- `addRail()`: Aggiunge binario collegato

### Rail (Binario)

**Responsabilità**: Rappresenta un segmento ferroviario tra due nodi

**Attributi Chiave**:
- `_length`: Lunghezza in km
- `_speedLimit`: Limite di velocità in km/h
- `_occupyingTrains`: Treni sul binario

**Metodi Principali**:
- `getTrainAhead()`: Trova treno davanti
- `addTrain()`/`removeTrain()`: Gestione occupazione

### Train (Treno)

**Responsabilità**: Rappresenta un treno con proprietà fisiche e stato

**Attributi Fisici**:
- `_weight`: Peso in tonnellate
- `_frictionCoeff`: Coefficiente d'attrito
- `_maxAccelForce`: Forza massima accelerazione (kN)
- `_maxBrakeForce`: Forza massima frenata (kN)

**Attributi di Stato**:
- `_state`: Stato corrente (fermo, accelerando, ecc.)
- `_currentSpeed`: Velocità attuale (km/h)
- `_position`: Posizione sulla rete

**Metodi Fisici**:
- `calculateAcceleration()`: Calcola accelerazione
- `calculateBraking()`: Calcola decelerazione
- `updatePosition()`: Aggiorna posizione

### RailwayNetwork (Rete Ferroviaria)

**Responsabilità**: Gestisce struttura della rete a grafo

**Struttura Dati**:
- `std::map<string, Node*>`: Accesso O(log n) ai nodi
- `std::vector<Rail*>`: Lista binari

**Metodi**:
- `addNode()`: Aggiunge nodo
- `addRail()`: Aggiunge binario
- `getNode()`: Recupera nodo per nome

---

## Algoritmi

### Algoritmo di Dijkstra

**Scopo**: Trovare il percorso più veloce tra due nodi

**Complessità**: O((V + E) log V) dove V=nodi, E=binari

**Funzione Costo**:
```cpp
cost = distance / speedLimit  // Tempo = Distanza / Velocità
```

**Processo**:
1. Inizializza distanze (∞ per tutti tranne start=0)
2. Mantieni set di nodi non visitati
3. Per nodo corrente, esamina vicini
4. Aggiorna distanze se percorso più breve trovato
5. Ripeti fino a raggiungere destinazione

**Ottimizzazioni**:
- Usa mappa per O(log n) lookup
- Considera sia distanza che velocità
- Percorso ottimale basato sul tempo, non solo distanza

### Collision Detection

**Algoritmo**:
```
Per ogni coppia di treni (i, j):
    Se treni sullo stesso binario:
        Calcola distanza = |pos_i - pos_j|
        Se distanza < SAFETY_DISTANCE:
            COLLISIONE!
```

**Distanza di Sicurezza**: 2 km (configurabile)

### Collision Avoidance

**Strategia**:
1. Cerca treno davanti sullo stesso binario
2. Se distanza < soglia sicurezza:
   - Cambia stato in BRAKING
   - Riduci velocità
3. Altrimenti:
   - Accelera fino a limite velocità

**Formula Distanza Arresto**:
```
d_stop = v² / (2 * deceleration)
```

---

## Fisica della Simulazione

### Modello Fisico

La simulazione usa fisica newtoniana semplificata:

**Forze Applicate**:

1. **Forza di Trazione (F_traction)**:
   - Controllata da `_maxAccelForce`
   - Applicata durante accelerazione

2. **Forza di Attrito (F_friction)**:
   ```
   F_friction = μ * m * g
   ```
   Dove:
   - μ = coefficiente d'attrito (0.05 tipico)
   - m = massa treno (tonnellate)
   - g = 9.81 m/s²

3. **Forza di Frenata (F_brake)**:
   - Controllata da `_maxBrakeForce`
   - Applicata durante frenata

**Equazione del Moto**:
```
F_net = F_traction - F_friction (accelerazione)
F_net = -F_brake (frenata)

a = F_net / m

v(t+Δt) = v(t) + a * Δt
s(t+Δt) = s(t) + v * Δt
```

### Time Steps

La simulazione avanza in passi discreti:

- **Δt default**: 5 minuti
- **Configurabile** via `setTimeStepMinutes()`
- Compromesso tra precisione e performance

### Stati del Treno

```
STOPPED ──────> ACCELERATING ──────> MAINTAINING
   ^                 │                     │
   │                 │                     │
   └─────────────────┴────── BRAKING <────┘
```

**Transizioni di Stato**:

- `STOPPED → ACCELERATING`: All'ora di partenza
- `ACCELERATING → MAINTAINING`: Raggiunta velocità limite
- `MAINTAINING → BRAKING`: Treno davanti o fine binario
- `BRAKING → STOPPED`: Velocità = 0

### Calcolo Tempo di Viaggio

**Stima Iniziale**:
```cpp
for each rail in path:
    time += rail.length / min(train.maxSpeed, rail.speedLimit)
```

**Tempo Reale**:
- Considera accelerazione/frenata
- Include fermate alle stazioni
- Tiene conto di rallentamenti per collisioni

---

## Gestione Errori

### Validazione Input

**Network File**:
- ✓ Formato corretto (Node/Rail)
- ✓ Nodi referenziati esistono
- ✓ Valori numerici validi (> 0)
- ✓ Nomi nodi validi (no spazi)

**Trains File**:
- ✓ 9 parametri per riga
- ✓ Peso, forze > 0
- ✓ Coefficiente attrito ≥ 0
- ✓ Nodi partenza/arrivo esistono
- ✓ Formato orario corretto (HHhMM)

**Gestione Errori**:
```cpp
try {
    // Parsing e validazione
} catch (const std::exception& e) {
    cerr << "ERROR at line " << lineNum << ": " << e.what();
    cerr << "Line: " << line << endl;
    // Cleanup e exit
}
```

---

## Performance

### Complessità Computazionale

| Operazione | Complessità | Note |
|------------|-------------|------|
| Pathfinding (Dijkstra) | O((V+E) log V) | V=nodi, E=binari |
| Train Update | O(n) | n=numero treni |
| Collision Check | O(n²) | Può essere ottimizzato |
| Position Update | O(1) | Per singolo treno |

### Ottimizzazioni Possibili

1. **Spatial Partitioning**: Dividere rete in regioni
2. **Collision Detection Ottimizzata**: Usa solo binari occupati
3. **Pathfinding Cache**: Memorizza percorsi calcolati
4. **Event-Driven**: Aggiorna solo quando necessario

---

## Estensibilità

### Aggiungere Nuovi Algoritmi di Pathfinding

```cpp
class AStarPathfinding : public IPathfindingStrategy {
public:
    virtual std::vector<Node*> findPath(Node* start, Node* end) {
        // Implementazione A*
    }
private:
    double heuristic(Node* a, Node* b);
};
```

### Aggiungere Nuovi Eventi

```cpp
class SignalFailureEvent : public IEvent {
private:
    Rail* _affectedRail;
    int _durationMinutes;
    
public:
    virtual void execute() {
        // Blocca binario temporaneamente
    }
    
    virtual std::string getDescription() const {
        return "Signal failure on rail";
    }
};
```

### Aggiungere Nuovi Observer

```cpp
class StatisticsCollector : public IObserver {
private:
    int _totalDelays;
    double _averageSpeed;
    
public:
    virtual void onNotify(const std::string& event) {
        // Raccogli statistiche
    }
    
    void generateReport();
};
```

---

## Best Practices Applicate

### Naming Conventions

- **Classi**: PascalCase (`Train`, `RailwayNetwork`)
- **Metodi**: camelCase (`updatePosition`, `findPath`)
- **Attributi privati**: `_camelCase` con underscore
- **Costanti**: UPPER_CASE
- **Interfacce**: Prefisso `I` (`IObserver`, `IEvent`)

### Incapsulamento

```cpp
class Train {
private:
    double _currentSpeed;  // Privato
    
public:
    double getCurrentSpeed() const { return _currentSpeed; }  // Getter
    void setCurrentSpeed(double speed) { _currentSpeed = speed; }  // Setter
};
```

### Const Correctness

```cpp
const std::string& getName() const { return _name; }  // Getter const
Node* getRailTo(Node* destination) const;  // Non modifica oggetto
```

### RAII (Resource Acquisition Is Initialization)

```cpp
// Costruttore acquisisce risorse
RailwayNetwork::RailwayNetwork() {
    // Inizializzazione
}

// Distruttore rilascia risorse
RailwayNetwork::~RailwayNetwork() {
    clear();  // Dealloca tutti i nodi e binari
}
```

---

## Testing e Debugging

### Unit Testing Suggerito

```cpp
// Test pathfinding
void testDijkstra() {
    RailwayNetwork net;
    net.addNode("A");
    net.addNode("B");
    net.addRail("A", "B", 10.0, 100.0);
    
    DijkstraPathfinding pf;
    vector<Node*> path = pf.findPath(net.getNode("A"), net.getNode("B"));
    
    assert(path.size() == 2);
    assert(path[0]->getName() == "A");
    assert(path[1]->getName() == "B");
}
```

### Memory Leak Detection

```bash
# Compilare con debug symbols
g++ -g -std=c++98 src/*.cpp -o railway_simulation

# Usare valgrind
valgrind --leak-check=full ./railway_simulation examples/network.txt examples/trains.txt
```

### Logging

Il sistema stampa:
- Caricamento rete e treni
- Progresso simulazione (ogni 100 step)
- Eventi importanti (collisioni, arrivi)
- File output generati

---

## Conclusioni

Questo progetto dimostra:

✅ **Architettura OOP solida** con design patterns appropriati  
✅ **Principi SOLID** applicati correttamente  
✅ **Incapsulamento** e information hiding  
✅ **Estensibilità** attraverso interfacce  
✅ **Fisica realistica** nella simulazione  
✅ **Gestione robusta degli errori**  
✅ **Conformità C++98** completa  
✅ **Documentazione completa** con UML  

Il codice è pronto per:
- Presentazione e valutazione
- Estensioni future
- Uso educativo
- Base per progetti più complessi
