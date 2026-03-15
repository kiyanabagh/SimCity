# SimCity Simulation

A C++ simulation of city region growth modeled as a cellular automaton. Zones grow
based on proximity to other zone types and available resources, while pollution spreads
from industrial zones and affects surrounding cells. Built as a group project for
CSCE 2110 (Data Structures) at the University of North Texas.

**Team:** Elisa Arbaiza, Kiyana Baghbadrani, Nikki Black, Shinji Kato

---

## Overview

The simulation reads a city layout from a CSV file and a configuration file specifying
simulation parameters. Each cell in the grid represents a zone type: Residential (R),
Commercial (C), Industrial (I), Road (-), Powerline (T/P), or empty space.

Each time step, zones grow according to adjacency rules:
- Residential zones grow when near populated cells or powerlines
- Commercial zones grow when near populated residential zones
- Industrial zones grow when near populated commercial zones
- Pollution spreads outward from industrial zones and degrades surrounding cells

At the end of the simulation, the program outputs the final region state and a full
analysis including population totals per zone type and pollution levels per cell.

---

## Project Structure

| File(s) | Responsibility |
|---|---|
| `main.cpp` | Entry point, config parsing, simulation loop |
| `region.cpp / .h` | Grid representation and cell access |
| `residential.cpp / .h` | Residential zone growth rules |
| `Industrial.cpp / .h` | Industrial zone growth rules |
| `commercial.cpp / .h` | Commercial zone growth rules |
| `pollution.cpp / .h` | Pollution spread logic |
| `Analysis.cpp / .h` | Final population and pollution reporting |
| `Configuration.txt` | Sample simulation config file |
| `RegionState.csv` | Sample city layout grid |

---

## Compile and Run
```bash
g++ -std=c++11 -o simulation main.cpp Analysis.cpp residential.cpp \
    Industrial.cpp commercial.cpp region.cpp pollution.cpp

./simulation
# When prompted:
# Enter the configuration file name: Configuration.txt
```

---

## Input Format

**Configuration.txt** specifies:
- Region file name (CSV)
- Time limit for the simulation
- Refresh rate for intermediate output
- Available workers and goods

**RegionState.csv** is a grid where each cell contains a zone symbol:
`R` (residential), `C` (commercial), `I` (industrial), `-` (road),
`T` / `P` (powerline), or a space (open land).

---

## Requirements

- C++11 or later
- g++ (GCC)
