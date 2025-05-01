#ifndef POLLUTION_H
#define POLLUTION_H

#include <vector>
#include <map>
using namespace std;

class Pollution {
public:
void spreadPollution(const vector<pair<int, int>>& industrialZones,
    vector<vector<int>>& popMap,
    vector<vector<int>>& pollutionMap);

};

#endif
