#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include <vector>
using namespace std;

class Commercial {
public:
    void simulate(vector<vector<char>>& zoneMap,
                  vector<vector<int>>& popMap,
                  int& availableWorkers,
                  int& availableGoods);

private:
    bool isValid(int x, int y, int rows, int cols);
    bool isPowered(int x, int y, const vector<vector<char>>& zoneMap);
    int countAdjacentWithMinPopulation(int x, int y, int minPop,
        const vector<vector<int>>& popMap,
        const vector<vector<char>>& zoneMap);
};

#endif
