#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>

using namespace std;

struct Edge {
    int target;
    int weight;
};

struct Node {
    int id;
    int g; // cost from start to current node
    int h; // heuristic cost to target
    int f; // total cost (g + h)
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

int heuristic(int current, int goal) {
    // Example heuristic: Manhattan distance
    // Assuming the nodes are represented as 2D grid positions (x, y)
    int x1 = current / 10, y1 = current % 10;
    int x2 = goal / 10, y2 = goal % 10;
    return abs(x1 - x2) + abs(y1 - y2);
}

vector<int> aStar(int start, int goal, const unordered_map<int, vector<Edge>>& graph) {
    unordered_map<int, int> gScore; // Cost from start to each node
    unordered_map<int, int> cameFrom; // To reconstruct the path
    priority_queue<Node, vector<Node>, greater<Node>> openSet;

    for (const auto& entry : graph) {
        gScore[entry.first] = INT_MAX;
    }
    gScore[start] = 0;
    openSet.push({start, 0, heuristic(start, goal), heuristic(start, goal)});

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.id == goal) {
            vector<int> path;
            int temp = goal;
            while (cameFrom.find(temp) != cameFrom.end()) {
                path.push_back(temp);
                temp = cameFrom[temp];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (const Edge& edge : graph.at(current.id)) {
            int tentative_gScore = gScore[current.id] + edge.weight;
            if (tentative_gScore < gScore[edge.target]) {
                cameFrom[edge.target] = current.id;
                gScore[edge.target] = tentative_gScore;
                int fScore = tentative_gScore + heuristic(edge.target, goal);
                openSet.push({edge.target, tentative_gScore, heuristic(edge.target, goal), fScore});
            }
        }
    }

    return {}; // Return empty path if no path is found
}

int main() {
    unordered_map<int, vector<Edge>> graph = {
        {0, {{1, 4}, {2, 1}}},
        {1, {{3, 1}}},
        {2, {{1, 2}, {3, 5}}},
        {3, {}}
    };
    
    int start = 0;
    int goal = 3;
    
    vector<int> path = aStar(start, goal, graph);
    
    cout << "Path from node " << start << " to node " << goal << ": ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
    
    return 0;
}
