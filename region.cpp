#include "region.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Reads and stores region layout from a CSV file
void RegionLayout::getRegionLayout(string fileName) {
    ifstream regionFile(fileName);
    string line;
    regionLayout.clear();

    if (regionFile.is_open()) {
        while (getline(regionFile, line)) {
            stringstream lineStream(line);
            string cell;
            vector<string> row;

            while (getline(lineStream, cell, ',')) {
                row.push_back(cell);
            }

            regionLayout.push_back(row);
        }
        regionFile.close();
    } else {
        cout << "Error: Failed to open region file." << endl;
        return;
    }

    cout << "\nRegion Layout:\n";
    displayRegion(regionLayout);

    //Convert regionLayout to regionMap (vector<vector<char>>)
    regionMap.clear();
    for (const auto& row : regionLayout) {
        vector<char> charRow;
        for (const auto& cell : row) {
            if (!cell.empty()) charRow.push_back(cell[0]);
        }
        regionMap.push_back(charRow);
    }

    createRegionsMap(regionLayout);
}

// Displays the region map for visual debugging
void RegionLayout::displayRegion(const vector<vector<string>>& regionMap) {
    for (const auto& row : regionMap) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// Categorizes the zones and stores their positions in separate maps
void RegionLayout::createRegionsMap(const vector<vector<string>>& regionMap) {
    int rows = regionMap.size();
    int cols = regionMap[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            string value = regionMap[i][j];

            if (value == "C") {
                commercialZoneMap.insert({i, j});
            } else if (value == "R") {
                residentialZoneMap.insert({i, j});
            } else if (value == "I") {
                industrialZoneMap.insert({i, j});
            } else if (value == "-" || value == "#") {
                roadMap.insert({i, j});
            }
            if (value == "T" || value == "#") {
                powerLinesMap.insert({i, j});
            }
        }
    }
}

// Returns the region map as a vector of characters
vector<vector<char>> RegionLayout::getCharMap() const {
    return regionMap;
}
