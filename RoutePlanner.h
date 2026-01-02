#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include "Graph.h"
#include "RouteStrategy.h"

class RoutePlanner {
    Graph& graph;

public:
    RoutePlanner(Graph& g);
    bool findRoute(const string& src, const string& dst,
                   const RouteStrategy& strategy);
};

#endif
