#include <iostream>
#include <stack>
#include <memory>

#include "Graph.h"
#include "RoutePlanner.h"
#include "RouteStrategy.h"
#include "Command.h"

using namespace std;

void showMenu() {
    cout << "\n----------------------------------------\n";
    cout << "Choose an operation:\n";
    cout << "1. Find Shortest Route\n";
    cout << "2. Find Fastest Route\n";
    cout << "3. Find Cheapest Route\n";
    cout << "4. Set Traffic Delay\n";
    cout << "5. Block Road\n";
    cout << "6. Undo Last Action\n";
    cout << "7. Redo Last Action\n";
    cout << "8. Exit\n";
    cout << "----------------------------------------\n";
    cout << "Enter your choice: ";
}

int main() {
    Graph graph;
    RoutePlanner planner(graph);

    ShortestRoute shortest;
    FastestRoute fastest;
    CheapestRoute cheapest;

    stack<unique_ptr<Command>> undoStack;
    stack<unique_ptr<Command>> redoStack;

    cout << "========================================\n";
    cout << "     SMARTROUTE NAVIGATION SYSTEM\n";
    cout << "========================================\n";

    // ---------------- NODE ENTRY ----------------
    while (true) {
        string choice;
        cout << "\nDo you want to add a node? (yes/no): ";
        cin >> choice;

        if (choice != "yes")
            break;

        string node;
        cout << "Enter node name: ";
        cin >> node;

        graph.addNode(node);
        cout << "Node added successfully!\n";
    }

    // ---------------- EDGE ENTRY ----------------
    while (true) {
        string choice;
        cout << "\nDo you want to add a road between two nodes? (yes/no): ";
        cin >> choice;

        if (choice != "yes")
            break;

        string u, v;
        int dist, time, cost;

        cout << "Enter source node: ";
        cin >> u;

        cout << "Enter destination node: ";
        cin >> v;

        cout << "Enter distance (km): ";
        cin >> dist;

        cout << "Enter base travel time (minutes): ";
        cin >> time;

        cout << "Enter travel cost: ";
        cin >> cost;

        graph.addEdge(u, v, dist, time, cost);
        cout << "Road added successfully!\n";
    }

    // ---------------- MENU LOOP ----------------
    while (true) {
        showMenu();
        int option;
        cin >> option;

        if (option == 8) {
            cout << "Thank you for using SmartRoute Navigation System!\n";
            break;
        }

        string src, dst;
        int delay;

        switch (option) {

        case 1:
            cout << "Enter source node: ";
            cin >> src;
            cout << "Enter destination node: ";
            cin >> dst;
            planner.findRoute(src, dst, shortest);
            break;

        case 2:
            cout << "Enter source node: ";
            cin >> src;
            cout << "Enter destination node: ";
            cin >> dst;
            planner.findRoute(src, dst, fastest);
            break;

        case 3:
            cout << "Enter source node: ";
            cin >> src;
            cout << "Enter destination node: ";
            cin >> dst;
            planner.findRoute(src, dst, cheapest);
            break;

        case 4:
            cout << "Enter source node: ";
            cin >> src;
            cout << "Enter destination node: ";
            cin >> dst;
            cout << "Enter traffic delay (minutes): ";
            cin >> delay;

            {
                unique_ptr<Command> cmd(
                    new TrafficCommand(graph, src, dst, delay)
                );
                cmd->execute();
                undoStack.push(move(cmd));
                while (!redoStack.empty()) redoStack.pop();
            }
            break;

        case 5:
            cout << "Enter source node: ";
            cin >> src;
            cout << "Enter destination node: ";
            cin >> dst;

            {
                unique_ptr<Command> cmd(
                    new BlockCommand(graph, src, dst)
                );
                cmd->execute();
                undoStack.push(move(cmd));
                while (!redoStack.empty()) redoStack.pop();
            }
            break;

        case 6:
            if (!undoStack.empty()) {
                unique_ptr<Command> cmd = move(undoStack.top());
                undoStack.pop();
                cmd->undo();
                redoStack.push(move(cmd));
            } else {
                cout << "Nothing to undo!\n";
            }
            break;

        case 7:
            if (!redoStack.empty()) {
                unique_ptr<Command> cmd = move(redoStack.top());
                redoStack.pop();
                cmd->execute();
                undoStack.push(move(cmd));
            } else {
                cout << "Nothing to redo!\n";
            }
            break;

        default:
            cout << "Invalid option! Please try again.\n";
        }
    }

    return 0;
}
