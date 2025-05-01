#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H

#include <vector>
using namespace std;

class Industrial {
public:
    void simulate(const vector<vector<char>>& zoneMap,
                  vector<vector<int>>& popMap,
                  int& availableWorkers,
                  vector<vector<int>>& pollutionMap,
                  int& availableGoods);

    vector<pair<int, int>> getIndustrialZones() const;


private:
    bool isValid(int x, int y, int rows, int cols);
    bool isPowered(int x, int y, const vector<vector<char>>& zoneMap);
    int countAdjacentWithMinPopulation(int x, int y, int minPop,
        const vector<vector<int>>& popMap,
        const vector<vector<char>>& zoneMap);

    vector<pair<int, int>> industrialZones;
};

#endif
