#pragma once
#include <vector>
#include <iostream>
#include "ConsoleCon.h"
#include <cmath>

using namespace std;

class Target {
    const double ratioBullsEye = 0.0375;
    int width, height;
    vector<vector<char>> target;
    double getDistance(int x, int y);
    bool isDoubleBull(int x, int y, int radius);
    bool isSingleBull(int x, int y, int radius);
    bool isTreble(int x, int y, int radius);
    bool isDouble(int x, int y, int radius);
    bool isEvenSector(int angle);
    void draw();
    vector<pair<pair<int, int>, int>> angles =
    { {{0, 9}, 6}, {{10, 27}, 13},{{28, 45}, 4},
      {{46, 63}, 18},{{64, 81}, 1},{{82, 99}, 20},
      {{100, 117}, 5},{{118, 135}, 12},{{136, 153}, 9},
      {{154, 171}, 14},{{172, 189}, 11}, {{190, 207}, 8},
      {{208, 225}, 16}, {{226, 243}, 7}, {{244, 261}, 19},
      {{262, 279}, 3}, {{280, 297}, 17}, {{298, 315}, 2},
      {{316, 333}, 15}, {{334, 351}, 10}, {{352, 360}, 6}
    };

public:
    Target(int w, int h);
    bool isInCircle(int x, int y, int radius);
    char at(int x, int y) const;
    void targetChange(vector<pair<int, int>> scoopeCoord);
    int calculateAngle(int x, int y);
    int getScore(int x, int y);
    pair<int, int> getCenterCoordinates();
    void print() const;
};
