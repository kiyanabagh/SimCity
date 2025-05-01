#ifndef REGION_H
#define REGION_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Struct to hold population and zone type for each cell
struct regionConverter {
    int population;
    string zoneType;
};

class RegionLayout {
private:
    vector<vector<string>> regionLayout;
    vector<vector<char>> regionMap;

    // Maps to store the coordinates of each zone type
    multimap<int, int> commercialZoneMap;
    multimap<int, int> residentialZoneMap;
    multimap<int, int> industrialZoneMap;
    multimap<int, int> roadMap;
    multimap<int, int> powerLinesMap;


public:
    // Reads the region layout from file and builds the maps
    void getRegionLayout(string fileName);
    void createRegionsMap(const vector<vector<string>>& regionMap);
    void displayRegion(const vector<vector<string>>& regionMap);
    


    // Getter functions to access the zone maps
    multimap<int, int> getCommercialZones() const { return commercialZoneMap; }
    multimap<int, int> getResidentialZones() const { return residentialZoneMap; }
    multimap<int, int> getIndustrialZones() const { return industrialZoneMap; }
    multimap<int, int> getRoadMap() const { return roadMap; }
    multimap<int, int> getPowerLinesMap() const { return powerLinesMap; }

    // Optional: Getter for full region layout if needed elsewhere
    vector<vector<string>> getZoneLayout() const { return regionLayout; }
    vector<vector<char>> getCharMap() const; // <-- Add this

};

#endif
