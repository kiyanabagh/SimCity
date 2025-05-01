#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "Industrial.h"
#include "pollution.h"
#include "commercial.h"
#include "Analysis.h"
#include "Residential.h"
#include "region.h"

using namespace std;

int getTimeStep(const vector<string>& contents) {
    return stoi(contents[1].substr(contents[1].find(":" ) + 1));
}

int getRefreshRate(const vector<string>& contents) {
    return stoi(contents[2].substr(contents[2].find(":" ) + 1));
}

string readConfig(const string& fileName, int& timeStep, int& refreshRate) {
    vector<string> fileContents;
    ifstream file(fileName);
    string line, regionFile;

    if (file.is_open()) {
        while (getline(file, line)) {
            fileContents.push_back(line);
        }
        file.close();
    } else {
        cout << "Error: Configuration file failed to open." << endl;
        exit(1);
    }

    regionFile = fileContents[0];
    timeStep = getTimeStep(fileContents);
    refreshRate = getRefreshRate(fileContents);
    return regionFile;
}

int main() {
    RegionLayout region;
    Industrial industrial;
    Pollution pollution;
    Commercial commercial;
    Analysis analysis;
    Residential residential;

    vector<vector<char>> zoneMap;
    vector<vector<int>> popMap;
    vector<vector<int>> pollutionMap;
    int timeStep = 0, refreshRate = 1;
    string configFile;

    cout << "Enter the configuration file name: ";
    cin >> configFile;

    string regionFile = readConfig(configFile, timeStep, refreshRate);
    region.getRegionLayout(regionFile);
    zoneMap = region.getCharMap();
    popMap.resize(zoneMap.size(), vector<int>(zoneMap[0].size(), 0));
    pollutionMap.resize(zoneMap.size(), vector<int>(zoneMap[0].size(), 0));

    analysis.printInitialMap(zoneMap);

    int currentWorkers = 0;
    int currentGoods = 0;
    bool changed = true;

    for (int t = 1; t <= timeStep && changed; ++t) {
        int prevPop = analysis.totalPopulation(popMap);

        residential.simulate(zoneMap, popMap, currentWorkers);
        industrial.simulate(zoneMap, popMap, currentWorkers, pollutionMap, currentGoods);
        commercial.simulate(zoneMap, popMap, currentWorkers, currentGoods);

        pollution.spreadPollution(industrial.getIndustrialZones(), popMap, pollutionMap);

        analysis.printStepInfo(t, currentWorkers, currentGoods);

        if (t % refreshRate == 0) {
            analysis.printMapWithPopulation(zoneMap, popMap);
        }

        int newPop = analysis.totalPopulation(popMap);
        changed = (newPop != prevPop);
        if (!changed) {
            analysis.printNoChangeMessage(t);
            break;
        }
    }

    analysis.printFinalMap(zoneMap);
    analysis.summarizeZones(zoneMap);
    analysis.summarizePopulation(popMap, zoneMap);
    analysis.summarizePollution(pollutionMap);
    analysis.analyzeArea(zoneMap, popMap, pollutionMap);

    return 0;
}
