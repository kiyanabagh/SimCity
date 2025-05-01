#include "commercial.h"
#include <vector>
using namespace std;

bool Commercial::isValid(int x, int y, int rows, int cols) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

bool Commercial::isPowered(int x, int y, const vector<vector<char>>& zoneMap) {
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

int Commercial::countAdjacentWithMinPopulation(int x, int y, int minPop,
    const vector<vector<int>>& popMap, const vector<vector<char>>& zoneMap) {
    int count = 0;
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int rows = popMap.size(), cols = popMap[0].size();
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (isValid(nx, ny, rows, cols)) {
            if (zoneMap[nx][ny] == 'C' && popMap[nx][ny] >= minPop) count++;
        }
    }
    return count;
}

void Commercial::simulate(vector<vector<char>>& zoneMap,
                          vector<vector<int>>& popMap,
                          int& availableWorkers,
                          int& availableGoods) {
    int rows = zoneMap.size(), cols = zoneMap[0].size();
    vector<vector<int>> newPopMap = popMap;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (zoneMap[i][j] != 'C') continue;
            int pop = popMap[i][j];

            bool canGrow = false;
            if (availableWorkers < 1 || availableGoods < 1) continue;

            if (pop == 0 && (isPowered(i, j, zoneMap) || countAdjacentWithMinPopulation(i, j, 1, popMap, zoneMap) >= 1)) {
                canGrow = true;
            } else if (pop == 1 && countAdjacentWithMinPopulation(i, j, 1, popMap, zoneMap) >= 2) {
                canGrow = true;
            }

            if (canGrow) {
                newPopMap[i][j]++;
                availableWorkers--;
                availableGoods--;
            }
        }
    }

    popMap = newPopMap;
}
