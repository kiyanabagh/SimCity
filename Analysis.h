#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Analysis {
public:
    // Displays the final map after simulation
    void printFinalMap(const vector<vector<char>>& cityMap);

    // Calculates total zones of each type
    void summarizeZones(const vector<vector<char>>& cityMap);

    void printInitialMap(const vector<vector<char>>& cityMap);

    void printMapWithPopulation(const vector<vector<char>>&, const vector<vector<int>>&);

    void printNoChangeMessage(int timestep);

    int totalPopulation(const vector<vector<int>>& popMap);

    void analyzeArea(
        const std::vector<std::vector<char>>& zoneMap,
        const std::vector<std::vector<int>>& popMap,
        const std::vector<std::vector<int>>& pollutionMap);

    void printStepInfo(int timestep, int workers, int goods);

    void summarizePopulation(const vector<vector<int>>&, const vector<vector<char>>&);
    void summarizePollution(const vector<vector<int>>&);

};

#endif // ANALYSIS_H
