#include "pollution.h"
#include <iostream>

using namespace std;

// Function to spread pollution around each industrial zone
void Pollution::spreadPollution(const vector<pair<int, int>>& industrialZones, vector<vector<int>>& popMap, vector<vector<int>>& pollutionMap) {
    int rows = pollutionMap.size();
    int cols = pollutionMap[0].size();

    // Iterate through all industrial zone coordinates
    for (auto const& zone : industrialZones) {
        int i = zone.first;
        int j = zone.second;
        int pollution = popMap[i][j]; //pollution equals population of industrial zone

        // Check all 8 surrounding cells
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue; // Skip the center cell

                int ni = i + dx;
                int nj = j + dy;

                // Make sure the new coordinates are within bounds
                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                    // Spread pollution into empty cells only
                    int spreadAmount = pollution - (abs(dx) + abs(dy));
                    if (spreadAmount > 0) {
                        pollutionMap[ni][nj] += spreadAmount;
                    }
                }
            }
        }
    }

    // Output the updated map with pollution for verification
    cout << "\nMap After Pollution Spread:\n";
    for (const auto& row : pollutionMap) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}
