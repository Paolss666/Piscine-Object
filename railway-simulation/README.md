# Railway Network Simulation - Simulazione Rete Ferroviaria

## Descrizione del Progetto

Questo progetto implementa una simulazione completa di una rete ferroviaria con più treni operanti simultaneamente, sviluppato in **C++98** seguendo i principi della programmazione orientata agli oggetti.

## Caratteristiche Principali

### ✅ Requisiti Implementati

1. **Rete Ferroviaria**
   - Definizione di nodi (città e giunzioni)
   - Segmenti ferroviari con lunghezza e limite di velocità
   - Struttura a grafo per la rete

2. **Simulazione Treni**
   - Caratteristiche fisiche (peso, coefficiente d'attrito, forze)
   - Stati del treno (fermo, accelerazione, mantenimento, frenata)
   - Fisica realistica con calcolo forze e accelerazioni

3. **Pathfinding**
   - Algoritmo di Dijkstra per trovare percorsi ottimali
   - Considera distanza e limiti di velocità
   - Calcolo del costo basato sul tempo di percorrenza

4. **Sistema di Prevenzione Collisioni**
   - Rilevamento treni sulla stessa binario
   - Distanza di sicurezza automatica
   - Frenata automatica quando necessario

5. **Sistema Eventi Casuali**
   - Ritardi dei treni
   - Riduzioni di velocità sui binari
   - Pattern Factory per la creazione eventi

6. **Output Dettagliato**
   - File di risultato per ogni treno
   - Rappresentazione grafica della posizione
   - Log completo del viaggio con timestamp

### 🎯 Design Patterns Implementati (4 patterns)

1. **Singleton Pattern** - `SimulationManager`
   - Garantisce una sola istanza del gestore simulazione
   - Controllo centralizzato della simulazione

2. **Strategy Pattern** - `IPathfindingStrategy`
   - Permette algoritmi di pathfinding intercambiabili
   - Implementazione: Dijkstra (facilmente estendibile con A*, ecc.)

3. **Observer Pattern** - `IObserver/ISubject`
   - Sistema di notifiche per eventi
   - OutputWriter osserva la simulazione

4. **Factory Pattern** - `EventFactory`
   - Creazione di diversi tipi di eventi
   - Eventi: Delay, SpeedReduction

### 📊 Diagrammi UML (2 diagrammi)

1. **Class Diagram** (`diagrams/class_diagram.puml`)
   - Mostra tutte le classi e le loro relazioni
   - Evidenzia i design patterns utilizzati
   - Diagramma completo dell'architettura

2. **Sequence Diagram** (`diagrams/sequence_diagram.puml`)
   - Flusso di esecuzione della simulazione
   - Interazioni tra componenti
   - Ciclo di vita di un treno

### 🏗️ Principi SOLID Applicati

- **S**ingle Responsibility: Ogni classe ha una singola responsabilità
- **O**pen/Closed: Estendibile senza modificare il codice esistente
- **L**iskov Substitution: Le interfacce sono sostituibili
- **I**nterface Segregation: Interfacce specifiche e mirate
- **D**ependency Inversion: Dipendenza da astrazioni, non da implementazioni

### 📦 Incapsulamento

- Tutti gli attributi privati con prefix `_`
- Getter/Setter appropriati
- Protezione dei dati interni
- Interfacce pubbliche ben definite

## Struttura del Progetto

```
railway-simulation/
├── include/              # File header (.hpp)
│   ├── Types.hpp
│   ├── Node.hpp
│   ├── Rail.hpp
│   ├── Train.hpp
│   ├── RailwayNetwork.hpp
│   ├── SimulationManager.hpp
│   ├── IPathfindingStrategy.hpp
│   ├── DijkstraPathfinding.hpp
│   ├── IObserver.hpp
│   ├── ISubject.hpp
│   ├── IEvent.hpp
│   ├── EventFactory.hpp
│   ├── InputParser.hpp
│   └── OutputWriter.hpp
│
├── src/                  # File sorgente (.cpp)
│   ├── main.cpp
│   ├── Types.cpp
│   ├── Node.cpp
│   ├── Rail.cpp
│   ├── Train.cpp
│   ├── RailwayNetwork.cpp
│   ├── SimulationManager.cpp
│   ├── SimulationManagerUpdate.cpp
│   ├── DijkstraPathfinding.cpp
│   ├── EventFactory.cpp
│   ├── InputParser.cpp
│   ├── InputParserHelp.cpp
│   └── OutputWriter.cpp
│
├── diagrams/             # Diagrammi UML
│   ├── class_diagram.puml
│   └── sequence_diagram.puml
│
├── examples/             # File di esempio
│   ├── network.txt
│   └── trains.txt
│
├── output/               # File di output (.result)
│
├── Makefile
├── README.md
└── DOCUMENTATION.md
```

## Compilazione ed Esecuzione

### Prerequisiti
- Compilatore C++ con supporto C++98 (g++, clang++)
- Make (opzionale ma consigliato)

### Compilazione

```bash
# Compilazione con Make
make

# Compilazione manuale
g++ -Wall -Wextra -Werror -std=c++98 -pedantic -I./include src/*.cpp -o railway_simulation
```

### Esecuzione

```bash
# Con file di esempio
./railway_simulation examples/network.txt examples/trains.txt

# Con file personalizzati
./railway_simulation <file_rete> <file_treni>

# Visualizzare aiuto
./railway_simulation --help
```

### Comandi Make Disponibili

```bash
make          # Compila il progetto
make clean    # Rimuove file oggetto e output
make fclean   # Pulizia completa
make re       # Ricompila tutto
make run      # Compila ed esegue con esempi
make help     # Mostra l'aiuto del programma
make test     # Esegue e verifica output
```

## Formato File di Input

### File Rete (network.txt)

```
# Definizione nodi
Node CityA
Node CityB
Node Junction1

# Definizione binari
# Rail <NodoInizio> <NodoFine> <Lunghezza_km> <LimiteVelocità_kmh>
Rail CityA Junction1 15.0 250.0
Rail Junction1 CityB 20.0 200.0
```

### File Treni (trains.txt)

```
# <Nome> <Peso_ton> <Attrito> <ForzaAccel_kN> <ForzaFreno_kN> <Partenza> <Arrivo> <OraPartenza> <DurataFermata>
TrainAB 80 0.05 356.0 30.0 CityA CityB 14h10 00h10
TrainAC 60 0.05 412.0 40.0 CityA CityC 14h20 00h10
```

## Formato File di Output

I file di output vengono creati nella directory `output/` con il nome `<NomeTreno>_<OraPartenza>.result`.

Esempio di output:
```
Train: TrainAB
Final travel time: 02h45m

[00h00] - [CityA     ][RailNodeA ] - [53.00km] - [Speed up] - [x][ ][ ][ ]...[ ][ ]
[00h05] - [CityA     ][RailNodeA ] - [52.50km] - [Maintain] - [x][ ][ ][ ]...[ ][ ]
...
[02h45] - [RailNodeC][CityB     ] - [00.00km] - [ Stopped] - [ ][ ][ ][ ][x]
```

Ogni riga contiene:
1. Tempo dall'inizio
2. Nodo di partenza del segmento
3. Nodo di arrivo del segmento
4. Distanza rimanente alla destinazione
5. Azione del treno (Speed up, Maintain, Braking, Stopped)
6. Grafico visuale della posizione sul binario

## Fisica della Simulazione

### Calcolo Forze

La simulazione implementa fisica realistica:

- **Forza netta di accelerazione**: F_net = F_accel - F_friction
- **Forza di attrito**: F_friction = μ * m * g
- **Accelerazione**: a = F/m
- **Velocità**: v(t+Δt) = v(t) + a*Δt

Dove:
- μ = coefficiente d'attrito
- m = massa del treno (tonnellate)
- g = accelerazione gravitazionale (9.81 m/s²)

### Frenata

Il sistema calcola la distanza di arresto e inizia la frenata automaticamente:
- Distanza di arresto = v² / (2 * decelerazione)
- Distanza di sicurezza tra treni: 2 km

## Validazione degli Input

Il programma valida:
- ✓ Formato dei file
- ✓ Esistenza dei nodi referenziati
- ✓ Valori numerici positivi
- ✓ Formato dell'orario (HHhMM)
- ✓ Nomi dei nodi validi

Errori vengono segnalati con:
- Numero di riga dell'errore
- Descrizione del problema
- Contenuto della riga problematica

## Possibili Estensioni (Bonus)

- [ ] Interfaccia grafica con rendering in tempo reale
- [ ] Ricaricamento runtime dei file di input
- [ ] Output grafico migliorato con curses/ASCII art
- [ ] Esecuzione multipla per calcolare tempi medi
- [ ] Supporto per eventi più complessi
- [ ] Sistema di segnalazione ferroviaria
- [ ] Supporto per più binari paralleli
- [ ] Statistiche avanzate (ritardi, efficienza, ecc.)

## Note Tecniche

### C++98 Compliance
- Nessun uso di C++11/14/17 features
- Compatible con standard più vecchi
- Usa `std::vector`, `std::map`, `std::string`
- Puntatori raw gestiti manualmente

### Gestione Memoria
- Allocazione/deallocazione esplicita
- No memory leaks (verificabile con valgrind)
- RAII pattern dove applicabile
- Ownership chiaro degli oggetti

## Documentazione Aggiuntiva

Per informazioni dettagliate sui design patterns e l'architettura, consultare:
- `DOCUMENTATION.md` - Documentazione completa dell'architettura
- `diagrams/` - Diagrammi UML in formato PlantUML

## Autore e Licenza

Progetto sviluppato per il modulo "Object Oriented Piscine - Module 05"

---

**Nota**: Questo progetto dimostra competenze avanzate in:
- Programmazione orientata agli oggetti
- Design patterns
- Algoritmi e strutture dati
- Fisica della simulazione
- Gestione di progetti C++ complessi
