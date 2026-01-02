#include "RoutePlanner.h"
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

RoutePlanner::RoutePlanner(Graph& g) : graph(g) {}

bool RoutePlanner::findRoute(const string& src,
                             const string& dst,
                             const RouteStrategy& strategy) {

    unordered_map<string, int> dist;
    unordered_map<string, string> parent;

    // Min-heap: (cost, node)
    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>
    > pq;

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        pair<int, string> top = pq.top();
        pq.pop();

        int cost = top.first;
        string node = top.second;

        if (node == dst)
            break;

        vector<Road>& edges = graph.getEdges(node);

        for (size_t i = 0; i < edges.size(); i++) {
            Road& road = edges[i];
            if (road.blocked)
                continue;

            int newCost = cost + strategy.weight(road);

            if (!dist.count(road.to) || newCost < dist[road.to]) {
                dist[road.to] = newCost;
                parent[road.to] = node;
                pq.push(make_pair(newCost, road.to));
            }
        }
    }

    if (!dist.count(dst)) {
        cout << "No route available\n";
        return false;
    }

    vector<string> path;
    string cur = dst;
    while (cur != src) {
        path.push_back(cur);
        cur = parent[cur];
    }
    path.push_back(src);

    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i + 1 < path.size())
            cout << " -> ";
    }

    cout << "\nTotal Cost: " << dist[dst] << endl;
    return true;
}
