#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    int id;
    int x, y; // Coordinates
    vector<pair<int, double>> neighbors; // Pair of neighbor node index and edge weight
};

struct Order {
    int orderID;
    int startNode, endNode;
};

vector<Node> graph;

// Heuristic function for A* (Euclidean distance)
double heuristic(int start, int end) {
    return sqrt(pow(graph[start].x - graph[end].x, 2) + pow(graph[start].y - graph[end].y, 2));
}

// A* algorithm to find the shortest path
vector<int> aStar(int start, int end) {
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> openSet;
    unordered_map<int, double> gScore, fScore;
    unordered_map<int, int> cameFrom;

    gScore[start] = 0;
    fScore[start] = heuristic(start, end);
    openSet.push({fScore[start], start});

    while (!openSet.empty()) {
        int current = openSet.top().second;
        openSet.pop();

        if (current == end) {
            // Reconstruct path
            vector<int> path;
            while (current != start) {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto& neighbor : graph[current].neighbors) {
            int neighborIndex = neighbor.first;
            double tentative_gScore = gScore[current] + neighbor.second;

            if (!gScore.count(neighborIndex) || tentative_gScore < gScore[neighborIndex]) {
                cameFrom[neighborIndex] = current;
                gScore[neighborIndex] = tentative_gScore;
                fScore[neighborIndex] = gScore[neighborIndex] + heuristic(neighborIndex, end);
                openSet.push({fScore[neighborIndex], neighborIndex});
            }
        }
    }

    return {}; // Return empty path if no path is found
}

int main() {
    // Example graph with 4 nodes
    graph = {
        {0, 0, 0, {{1, 1.0}, {2, 2.5}}},  // Node 0
        {1, 1, 1, {{0, 1.0}, {2, 1.5}, {3, 2.0}}}, // Node 1
        {2, 2, 2, {{0, 2.5}, {1, 1.5}, {3, 1.0}}}, // Node 2
        {3, 3, 3, {{1, 2.0}, {2, 1.0}}}  // Node 3
    };

    // Example order
    Order order = {1, 0, 3};

    // Find shortest path using A* algorithm
    vector<int> path = aStar(order.startNode, order.endNode);

    // Output the path
    cout << "Shortest path for order " << order.orderID << ": ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
