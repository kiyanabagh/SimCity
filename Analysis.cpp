#include "Analysis.h"
#include <limits> // for numeric_limits

// Print the initial city map (time step 0)
void Analysis::printInitialMap(const vector<vector<char>>& cityMap) {
    cout << "Initial Region State (Time Step 0):\n";
    for (const auto& row : cityMap) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// Print time step information (except for time step 0)
void Analysis::printStepInfo(int timestep, int workers, int goods) {
    cout << "Time Step: " << timestep << " | "
         << "Available Workers: " << workers << " | "
         << "Available Goods: " << goods << endl;
}

// Print the final city map
void Analysis::printFinalMap(const vector<vector<char>>& cityMap) {
    cout << "\nFinal City Map:\n";
    for (const auto& row : cityMap) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// Displays the city map using population values for residential zones
void Analysis::printMapWithPopulation(
  const vector<vector<char>>& zoneMap,
  const vector<vector<int>>& popMap)
{
  cout << "\nCity Map (With Population):\n";
  for (size_t i = 0; i < zoneMap.size(); ++i) {
      for (size_t j = 0; j < zoneMap[i].size(); ++j) {
          if (zoneMap[i][j] == 'R') {
              cout << popMap[i][j] << " "; // show population
          } else {
              cout << zoneMap[i][j] << " "; // show zone letter
          }
      }
      cout << endl;
  }
}

void Analysis::printNoChangeMessage(int timestep) {
  cout << "Simulation ended early at timestep " << timestep
       << " due to no changes in the region.\n";
}



// Count and display summary of zones by type
void Analysis::summarizeZones(const vector<vector<char>>& cityMap) {
    int industrial = 0, residential = 0, commercial = 0, polluted = 0, empty = 0;

    for (const auto& row : cityMap) {
        for (char cell : row) {
            switch (cell) {
                case 'I': industrial++; break;
                case 'R': residential++; break;
                case 'C': commercial++; break;
                case 'P': polluted++; break;
                case '-': empty++; break;
            }
        }
    }

    cout << "\nZone Summary:\n";
    cout << "Industrial Zones: " << industrial << endl;
    cout << "Residential Zones: " << residential << endl;
    cout << "Commercial Zones: " << commercial << endl;
    cout << "Polluted Zones: " << polluted << endl;
    cout << "Empty Zones: " << empty << endl;
}

void Analysis::analyzeArea(
    const vector<vector<char>>& zoneMap,
    const vector<vector<int>>& popMap,
    const vector<vector<int>>& pollutionMap)
{
    int rows = zoneMap.size();
    int cols = zoneMap[0].size();
    int x1, y1, x2, y2;

    // Prompt for valid coordinates
    while (true) {
        cout << "\nEnter top-left and bottom-right coordinates of area to analyze (format: x1 y1 x2 y2): ";
        cin >> x1 >> y1 >> x2 >> y2;

        if (cin.fail() || x1 < 0 || y1 < 0 || x2 >= cols || y2 >= rows || x1 > x2 || y1 > y2) {
            cout << "Invalid input. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    // Totals
    int resPop = 0, indPop = 0, comPop = 0, totalPollution = 0;

    for (int i = y1; i <= y2; ++i) {
        for (int j = x1; j <= x2; ++j) {
            switch (zoneMap[i][j]) {
                case 'R': resPop += popMap[i][j]; break;
                case 'I': indPop += popMap[i][j]; break;
                case 'C': comPop += popMap[i][j]; break;
            }
            totalPollution += pollutionMap[i][j];
        }
    }

    cout << "\n--- Regional Analysis (" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ") ---\n";
    cout << "Residential Population: " << resPop << endl;
    cout << "Industrial Population:  " << indPop << endl;
    cout << "Commercial Population:  " << comPop << endl;
    cout << "Total Pollution:        " << totalPollution << endl;
}

int Analysis::totalPopulation(const vector<vector<int>>& popMap) {
    int total = 0;
    for (const auto& row : popMap) {
        for (int val : row) {
            total += val;
        }
    }
    return total;
}
void Analysis::summarizePopulation(const vector<vector<int>>& popMap, const vector<vector<char>>& zoneMap) {
    int res = 0, ind = 0, com = 0;
    for (size_t i = 0; i < popMap.size(); ++i) {
        for (size_t j = 0; j < popMap[i].size(); ++j) {
            switch (zoneMap[i][j]) {
                case 'R': res += popMap[i][j]; break;
                case 'I': ind += popMap[i][j]; break;
                case 'C': com += popMap[i][j]; break;
            }
        }
    }
    cout << "\nTotal Population by Zone:\n";
    cout << "Residential: " << res << endl;
    cout << "Industrial:  " << ind << endl;
    cout << "Commercial:  " << com << endl;
}

void Analysis::summarizePollution(const vector<vector<int>>& pollutionMap) {
    int total = 0;
    for (const auto& row : pollutionMap) {
        for (int val : row) {
            total += val;
        }
    }
    cout << "Total Pollution in Region: " << total << endl;
}