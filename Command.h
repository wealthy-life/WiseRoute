#ifndef COMMAND_H
#define COMMAND_H

#include "Graph.h"
#include <iostream>

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

class BlockCommand : public Command {
    Graph& graph;
    string u, v;

public:
    BlockCommand(Graph& g, string a, string b)
        : graph(g), u(a), v(b) {}

    void execute() override {
        graph.blockEdge(u, v);
        cout << "Road " << u << " -> " << v << " blocked\n";
    }

    void undo() override {
        graph.unblockEdge(u, v);
        cout << "Undo: Road " << u << " -> " << v << " unblocked\n";
    }
};

class TrafficCommand : public Command {
    Graph& graph;
    string u, v;
    int oldDelay, newDelay;

public:
    TrafficCommand(Graph& g, string a, string b, int d)
        : graph(g), u(a), v(b), newDelay(d) {
        oldDelay = graph.getTrafficDelay(u, v);
    }

    void execute() override {
        graph.setTraffic(u, v, newDelay);
        cout << "Traffic updated on " << u << " -> " << v << "\n";
    }

    void undo() override {
        graph.setTraffic(u, v, oldDelay);
        cout << "Undo: Traffic reverted on " << u << " -> " << v << "\n";
    }
};

#endif
