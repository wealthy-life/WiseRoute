#ifndef ROUTESTRATEGY_H
#define ROUTESTRATEGY_H

#include "Road.h"

class RouteStrategy {
public:
    virtual int weight(const Road& r) const = 0;
    virtual ~RouteStrategy() {}
};

class ShortestRoute : public RouteStrategy {
public:
    int weight(const Road& r) const override {
        return r.distance;
    }
};

class FastestRoute : public RouteStrategy {
public:
    int weight(const Road& r) const override {
        return r.getTime();
    }
};

class CheapestRoute : public RouteStrategy {
public:
    int weight(const Road& r) const override {
        return r.cost;
    }
};

#endif
