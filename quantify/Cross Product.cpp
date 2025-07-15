#include <iostream>
#include <cmath>

// Structure to represent a 3D vector
typedef struct {
    double x;
    double y;
    double z;
} Vector3;

// Add two vectors
Vector3 add(Vector3 a, Vector3 b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

// Subtract two vectors
Vector3 subtract(Vector3 a, Vector3 b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

// Compute the dot product of two vectors
double dotProduct(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Compute the cross product of two vectors
Vector3 crossProduct(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.y * b.z - a.z * b.y; // x component
    result.y = a.z * b.x - a.x * b.z; // y component
    result.z = a.x * b.y - a.y * b.x; // z component
    return result;
}

// Compute the magnitude (length) of a vector
double magnitude(Vector3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Print a vector in (x, y, z) format
void printVector(Vector3 v) {
    std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

// Main function to test vector operations
int main() {
    // Define two 3D vectors
    Vector3 A = {1.0, 2.0, 3.0};
    Vector3 B = {4.0, 5.0, 6.0};

    // Compute cross product
    Vector3 C = crossProduct(A, B);

    // Output results
    std::cout << "Vector A: ";
    printVector(A);
    std::cout << "\nVector B: ";
    printVector(B);
    std::cout << "\nA x B: ";
    printVector(C);
    std::cout << "\n|A x B|: " << magnitude(C) << std::endl;

    return 0;
}
