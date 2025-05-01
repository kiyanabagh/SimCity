#include "Residential.h"
#include <vector>
#include <iostream>

using namespace std;

// Check if a cell is within bounds
bool Residential::isValid(int x, int y, int maxX, int maxY) {
    return x >= 0 && y >= 0 && x < maxX && y < maxY;
}

// Count adjacent cells with minimum population
int Residential::countAdjacentWithMinPopulation(int x, int y, int minPop,
    const vector<vector<int>>& popMap, const vector<vector<char>>& zoneMap) {

    int count = 0;
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int rows = popMap.size(), cols = popMap[0].size();

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (isValid(nx, ny, rows, cols)) {
            if (zoneMap[nx][ny] == 'R' && popMap[nx][ny] >= minPop) {
                count++;
            }
        }
    }
    return count;
}

void Residential::simulate(
    const vector<vector<char>>& zoneMap,
    vector<vector<int>>& popMap,
    int& availableWorkers
) {
    int rows = zoneMap.size();
    int cols = zoneMap[0].size();
    vector<vector<int>> newPopMap = popMap;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (zoneMap[i][j] == 'R') {
                int pop = popMap[i][j];
                int adj;

                if (pop == 0) {
                    // Rule 1: Adjacent to powerline
                    adj = countAdjacentWithMinPopulation(i, j, 1, popMap, zoneMap);
                    if (adj > 0 || isPowered(i, j, zoneMap)) {
                        newPopMap[i][j]++;
                        availableWorkers++;
                    }
                } else if (pop == 1 && countAdjacentWithMinPopulation(i, j, 1, popMap, zoneMap) >= 2) {
                    newPopMap[i][j]++;
                    availableWorkers++;
                } else if (pop == 2 && countAdjacentWithMinPopulation(i, j, 2, popMap, zoneMap) >= 4) {
                    newPopMap[i][j]++;
                    availableWorkers++;
                } else if (pop == 3 && countAdjacentWithMinPopulation(i, j, 3, popMap, zoneMap) >= 6) {
                    newPopMap[i][j]++;
                    availableWorkers++;
                } else if (pop == 4 && countAdjacentWithMinPopulation(i, j, 4, popMap, zoneMap) >= 8) {
                    newPopMap[i][j]++;
                    availableWorkers++;
                }
            }
        }
    }

    popMap = newPopMap;
}

// Check if cell is adjacent to powerline
bool Residential::isPowered(int x, int y, const vector<vector<char>>& zoneMap) {
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int rows = zoneMap.size();
    int cols = zoneMap[0].size();

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (isValid(nx, ny, rows, cols)) {
            if (zoneMap[nx][ny] == 'T' || zoneMap[nx][ny] == '#') {
                return true;
            }
        }
    }
    return false;
}
