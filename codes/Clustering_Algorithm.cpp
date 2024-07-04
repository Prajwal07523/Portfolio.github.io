#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <limits>

using namespace std;

struct Point {
    double x, y;
};

double distance(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

vector<int> kMeans(const vector<Point>& points, int k) {
    int n = points.size();
    vector<Point> centroids(k);
    vector<int> labels(n);

    // Initialize centroids randomly
    for (int i = 0; i < k; ++i) {
        centroids[i] = points[rand() % n];
    }

    bool changed;
    do {
        changed = false;

        // Assign points to nearest centroid
        for (int i = 0; i < n; ++i) {
            double minDist = numeric_limits<double>::max();
            int label = 0;
            for (int j = 0; j < k; ++j) {
                double dist = distance(points[i], centroids[j]);
                if (dist < minDist) {
                    minDist = dist;
                    label = j;
                }
            }
            if (labels[i] != label) {
                labels[i] = label;
                changed = true;
            }
        }

        // Update centroids
        vector<Point> newCentroids(k, {0, 0});
        vector<int> count(k, 0);
        for (int i = 0; i < n; ++i) {
            newCentroids[labels[i]].x += points[i].x;
            newCentroids[labels[i]].y += points[i].y;
            ++count[labels[i]];
        }
        for (int j = 0; j < k; ++j) {
            if (count[j] > 0) {
                centroids[j].x = newCentroids[j].x / count[j];
                centroids[j].y = newCentroids[j].y / count[j];
            }
        }
    } while (changed);

    return labels;
}

int main() {
    vector<Point> customers = {{2, 3}, {3, 3}, {8, 8}, {7, 8}, {2, 2}, {8, 9}};
    int k = 2;
    vector<int> labels = kMeans(customers, k);

    cout << "Cluster assignments:\n";
    for (int i = 0; i < customers.size(); ++i) {
        cout << "Customer " << i << " is in cluster " << labels[i] << endl;
    }

    return 0;
}
