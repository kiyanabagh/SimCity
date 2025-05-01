#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include <vector>

class Residential {
public:
    void simulate(const std::vector<std::vector<char>>& zoneMap,
                  std::vector<std::vector<int>>& popMap,
                  int& availableWorkers);

private:
    bool isValid(int x, int y, int maxX, int maxY);
    bool isPowered(int x, int y, const std::vector<std::vector<char>>& zoneMap);
    int countAdjacentWithMinPopulation(int x, int y, int minPop,
        const std::vector<std::vector<int>>& popMap,
        const std::vector<std::vector<char>>& zoneMap);
};

#endif
