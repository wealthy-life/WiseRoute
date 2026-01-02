#include "Graph.h"

void Graph::addNode(const string& node) {
    adj[node];
}

void Graph::addEdge(const string& u, const string& v, int dist, int time, int cost) {
    adj[u].emplace_back(v, dist, time, cost);
    adj[v].emplace_back(u, dist, time, cost);
}

vector<Road>& Graph::getEdges(const string& node) {
    return adj[node];
}

bool Graph::hasNode(const string& node) const {
    return adj.count(node);
}

void Graph::blockEdge(const string& u, const string& v) {
    for (auto& r : adj[u]) if (r.to == v) r.blocked = true;
    for (auto& r : adj[v]) if (r.to == u) r.blocked = true;
}

void Graph::unblockEdge(const string& u, const string& v) {
    for (auto& r : adj[u]) if (r.to == v) r.blocked = false;
    for (auto& r : adj[v]) if (r.to == u) r.blocked = false;
}

int Graph::getTrafficDelay(const string& u, const string& v) {
    for (auto& r : adj[u])
        if (r.to == v) return r.trafficDelay;
    return 0;
}

void Graph::setTraffic(const string& u, const string& v, int delay) {
    for (auto& r : adj[u]) if (r.to == v) r.trafficDelay = delay;
    for (auto& r : adj[v]) if (r.to == u) r.trafficDelay = delay;
}
