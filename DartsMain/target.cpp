#include "target.h"


bool Target::isInCircle(int x, int y, int radius) {
    int dx = x - width / 2;
    int dy = y - height / 2;
    return (dx * dx + dy * dy) <= (radius * radius - 1);
}

double Target::getDistance(int x, int y) {
    return sqrt(pow(width / 2 - x, 2) + pow(height / 2 - y, 2));
}

bool Target::isDoubleBull(int x, int y, int radius) {
    double DoubleBullRadius = ratioBullsEye * radius;
    return isInCircle(x, y, DoubleBullRadius);
}

bool Target::isSingleBull(int x, int y, int radius) {
    double SingleBullRadius = ratioBullsEye * 2 * radius;
    return isInCircle(x, y, SingleBullRadius);
}

bool Target::isTreble(int x, int y, int radius) {
    double trebleStart = radius * 0.559;
    double trebleEnd = radius * 0.606;

    double distance = getDistance(x, y);

    return (distance >= trebleStart && distance <= trebleEnd - 1);
}

bool Target::isDouble(int x, int y, int radius) {
    double doubleStart = radius * 0.924;

    double distance = getDistance(x, y);

    return (distance >= doubleStart && distance <= radius);
}

bool Target::isEvenSector(int angle) {
    for (int i = 0; i < 21; i++) {
        if (angle >= angles[i].first.first && angle <= angles[i].first.second) {
            return (i % 2 == 0);
        }
    }
}

void Target::draw() {
    int centerX = width / 2 + 1;
    int centerY = height / 2 + 1;
    int radius = width / 2;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (isInCircle(x, y, radius))
            {
                if (isDoubleBull(x, y, radius))
                {
                    target[x][y] = '0';
                }
                else if (isSingleBull(x, y, radius) && !isDoubleBull(x, y, radius))
                {
                    target[x][y] = '&';
                }
                else
                {
                    int ang = calculateAngle(x, y);
                    bool fl = isEvenSector(ang);
                    if (fl)
                    {
                        target[x][y] = '*';
                        if (isTreble(x, y, radius)) {
                            target[x][y] = '0';
                        }
                        if (isDouble(x, y, radius)) {
                            target[x][y] = '0';
                        }
                    }
                    else
                    {
                        target[x][y] = '+';
                        if (isTreble(x, y, radius)) {
                            target[x][y] = '&';
                        }
                        if (isDouble(x, y, radius)) {
                            target[x][y] = '&';
                        }
                    }
                }
            }
        }
    }
}


char Target::at(int x, int y) const {
    return target[x][y];
}

void Target::targetChange(vector<pair<int, int>> scopeCoord) {
    for (int i = 0; i < 5; i++) {
        console::setCursorAbsolutePosition(scopeCoord[i].first, scopeCoord[i].second);
        if (target[scopeCoord[i].first - 1][scopeCoord[i].second - 1] == '0') {
            console::setConsoleTextColor("red");
            console::setFoneColor("red");
            cout << target[scopeCoord[i].first - 1][scopeCoord[i].second - 1];
            console::resetConsoleColor();
        }
        else if (target[scopeCoord[i].first - 1][scopeCoord[i].second - 1] == '&') {
            console::setConsoleTextColor("green");
            console::setFoneColor("green");
            cout << target[scopeCoord[i].first - 1][scopeCoord[i].second - 1];
            
        }
        else if (target[scopeCoord[i].first - 1][scopeCoord[i].second - 1] == '+') {
            console::setConsoleTextColor("white");
            console::setFoneColor("white");
            cout << target[scopeCoord[i].first - 1][scopeCoord[i].second - 1];

        }
        else if (target[scopeCoord[i].first - 1][scopeCoord[i].second - 1] == '*') {
            console::setConsoleTextColor("black");
            cout << target[scopeCoord[i].first - 1][scopeCoord[i].second - 1];
            console::setConsoleTextColor("white");
        }
    }
}

Target::Target(int w, int h) : width(w), height(h), target(h, vector<char>(w, ' ')) { draw(); }

int Target::calculateAngle(int x, int y) {
    int dx = x - width / 2;
    int dy = y - height / 2;
    double angleRadians = atan2(dy, dx);
    double angleDegrees = angleRadians * (180.0 / acos(-1));

    angleDegrees = 360 - angleDegrees;

    if (angleDegrees >= 360) {
        angleDegrees -= 360;
    }
    else if (angleDegrees <= 0) {
        angleDegrees += 360;
    }

    return angleDegrees;
}

int Target::getScore(int x, int y) {
    int score = -1;
    int angle = calculateAngle(x, y);
    for (const auto& range : this->angles) {
        if (angle >= range.first.first && angle <= range.first.second) {
            if (isSingleBull(x, y, 151) && !isDoubleBull(x, y, 151)) { score = 25; }
            else if (isDoubleBull(x, y, 151)) { score = 50; }
            else if (isDouble(x, y, 151)) { score = range.second * 2; }
            else if (isTreble(x, y, 151)) { score = range.second * 3; }
            else score = range.second;
        }
    }
    return score;
}

pair<int, int> Target::getCenterCoordinates() { return { width / 2 + 1, height / 2 + 1 }; }

void Target::print() const {
    for (const auto& row : target) {
        for (const auto& ell : row) {
            if (ell == '0') {
                console::setConsoleTextColor("red");
                console::setFoneColor("red");
                cout << ell;
                console::setConsoleTextColor("black");
                console::setFoneColor("black");
            }
            else if (ell == '&') {
                console::setConsoleTextColor("green");
                console::setFoneColor("green");
                cout << ell;
                console::setConsoleTextColor("black");
                console::setFoneColor("black");
            }
            else if (ell == '+') {
                console::setConsoleTextColor("white");
                console::setFoneColor("white");
                cout << ell;
                console::setConsoleTextColor("black");
                console::setFoneColor("black");
            }
            else if (ell == '*') {
                console::setConsoleTextColor("black");
                cout << ell;
                console::setConsoleTextColor("white");
            }
            else
            {
                cout << ell;
            }
        }
        cout << std::endl;
    }
    console::setConsoleTextColor("white");
    console::setFoneColor("black");
}