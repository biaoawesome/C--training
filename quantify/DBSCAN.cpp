#include <iostream>
#include <cmath>

using namespace std;

// Maximum number of data points
const int MAX_POINTS = 100;

// Maximum number of neighbors per point
const int MAX_NEIGHBORS = 100;

// Structure to represent a 2D point
typedef struct {
    double x;
    double y;
} Point;

// Global parameters
double epsilon = 2.0;                     // Radius for neighborhood
int minPts = 3;                           // Minimum number of points to form a cluster
bool visited[MAX_POINTS] = { false };     // Track visited points
int labels[MAX_POINTS];                   // Cluster labels (-1 for noise)

// Calculate Euclidean distance between two points
double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Find all points within epsilon distance from point at index
int regionQuery(int index, Point points[], int n, int neighbors[]) {
    int count = 0;
    for (int j = 0; j < n; ++j) {
        if (index != j && distance(points[index], points[j]) <= epsilon) {
            if (count < MAX_NEIGHBORS) {
                neighbors[count++] = j;
            }
        }
    }
    return count;
}

// Expand cluster using BFS-like approach
void expandCluster(int index, int neighbors[], int neighborCount, int clusterId,
                   Point points[], int n) {
    labels[index] = clusterId;

    int queue[MAX_POINTS];  // Simulate queue using array
    int front = 0, rear = 0;

    // Add all neighbors to queue
    for (int i = 0; i < neighborCount; ++i) {
        queue[rear++] = neighbors[i];
    }

    while (front < rear) {
        int pointIndex = queue[front++];

        if (!visited[pointIndex]) {
            visited[pointIndex] = true;

            // Query neighbors of this point
            int newNeighbors[MAX_NEIGHBORS];
            int newNeighborCount = regionQuery(pointIndex, points, n, newNeighbors);

            if (newNeighborCount >= minPts) {
                // Add new neighbors to queue if not already added
                for (int i = 0; i < newNeighborCount; ++i) {
                    bool exists = false;
                    for (int j = 0; j < rear; ++j) {
                        if (queue[j] == newNeighbors[i]) {
                            exists = true;
                            break;
                        }
                    }
                    if (!exists && rear < MAX_POINTS) {
                        queue[rear++] = newNeighbors[i];
                    }
                }
            }
        }

        // Assign cluster ID if previously marked as noise
        if (labels[pointIndex] == -1) {
            labels[pointIndex] = clusterId;
        }
    }
}

// Main DBSCAN clustering function
void fit(Point points[], int n) {
    int clusterId = 0;

    for (int i = 0; i < n; ++i) {
        if (visited[i]) continue;
        visited[i] = true;

        int neighbors[MAX_NEIGHBORS];
        int neighborCount = regionQuery(i, points, n, neighbors);

        if (neighborCount < minPts) {
            labels[i] = -1;  // Mark as noise
        } else {
            expandCluster(i, neighbors, neighborCount, clusterId, points, n);
            clusterId++;
        }
    }
}

// Main function to run DBSCAN
int main() {
    // Sample 2D points
    Point points[] = {
        {1.0, 2.0}, {2.0, 2.0}, {2.0, 3.0},
        {8.0, 7.0}, {8.0, 8.0},
        {25.0, 80.0}, {24.0, 80.0}, {25.0, 81.0}
    };
    int n = sizeof(points) / sizeof(points[0]);

    // Initialize all labels to -1 (unclassified)
    for (int i = 0; i < n; ++i) {
        labels[i] = -1;
    }

    // Run DBSCAN
    fit(points, n);

    // Output clustering result
    for (int i = 0; i < n; ++i) {
        cout << "Point " << i << " label: " << labels[i] << endl;
    }

    return 0;
}
