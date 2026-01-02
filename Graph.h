#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>
#include "Road.h"

using namespace std;

class Graph {
    unordered_map<string, vector<Road>> adj;

public:
    void addNode(const string& node);
    void addEdge(const string& u, const string& v, int dist, int time, int cost);

    vector<Road>& getEdges(const string& node);
    bool hasNode(const string& node) const;

    void blockEdge(const string& u, const string& v);
    void unblockEdge(const string& u, const string& v);

    int getTrafficDelay(const string& u, const string& v);
    void setTraffic(const string& u, const string& v, int delay);
};

#endif
