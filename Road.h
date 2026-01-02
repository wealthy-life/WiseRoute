#ifndef ROAD_H
#define ROAD_H

#include <string>
using namespace std;

struct Road {
    string to;
    int distance;
    int baseTime;
    int trafficDelay;
    int cost;
    bool blocked;

    Road(string t, int d, int bt, int c)
        : to(t), distance(d), baseTime(bt),
          trafficDelay(0), cost(c), blocked(false) {}

    int getTime() const {
        return baseTime + trafficDelay;
    }
};

#endif
