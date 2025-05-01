#include "Industrial.h"
#include <vector>

using namespace std;

bool Industrial::isValid(int x, int y, int rows, int cols) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

bool Industrial::isPowered(int x, int y, const vector<vector<char>>& zoneMap) {
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int rows = zoneMap.size(), cols = zoneMap[0].size();
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (isValid(nx, ny, rows, cols)) {
            if (zoneMap[nx][ny] == 'T' || zoneMap[nx][ny] == '#') return true;
        }
    }
    return false;
}

int Industrial::countAdjacentWithMinPopulation(int x, int y, int minPop,
    const vector<vector<int>>& popMap, const vector<vector<char>>& zoneMap) {
    int count = 0;
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int rows = popMap.size(), cols = popMap[0].size();
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (isValid(nx, ny, rows, cols)) {
            if (zoneMap[nx][ny] == 'I' && popMap[nx][ny] >= minPop) count++;
        }
    }
    return count;
}

void Industrial::simulate(const vector<vector<char>>& zoneMap,
                          vector<vector<int>>& popMap,
                          int& availableWorkers,
                          vector<vector<int>>& pollutionMap,
                          int& availableGoods) {
    int rows = zoneMap.size();
    int cols = zoneMap[0].size();
    vector<vector<int>> newPopMap = popMap;
    industrialZones.clear();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (zoneMap[i][j] != 'I') continue;

            int pop = popMap[i][j];
            bool powered = isPowered(i, j, zoneMap);
            bool canGrow = false;

            if (pop == 0 && powered && availableWorkers >= 2) canGrow = true;
            else if (pop == 0 && countAdjacentWithMinPopulation(i, j, 1, popMap, zoneMap) >= 1 && availableWorkers >= 2) canGrow = true;
            else if (pop == 1 && countAdjacentWithMinPopulation(i, j, 1, popMap, zoneMap) >= 2 && availableWorkers >= 2) canGrow = true;
            else if (pop == 2 && countAdjacentWithMinPopulation(i, j, 2, popMap, zoneMap) >= 4 && availableWorkers >= 2) canGrow = true;

            if (canGrow && pop < 3) {
                newPopMap[i][j]++;
                availableWorkers -= 2;
            }

            availableGoods += newPopMap[i][j];
            industrialZones.push_back({i, j});
        }
    }

    popMap = newPopMap;
}

vector<pair<int, int>> Industrial::getIndustrialZones() const {
    return industrialZones;
}
