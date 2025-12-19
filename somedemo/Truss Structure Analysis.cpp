// Truss Structure Analysis Program
// Calculates nodal displacements and member stresses in a 2D truss
// Based on the direct stiffness method
// Reference: Finite Element Analysis fundamentals

#include <iostream>
#include <cmath>

#define PI 3.14159265359

// Node structure containing coordinates
struct Node {
    double x, y;
};

// Member structure containing connectivity and properties
struct Member {
    int startNode;
    int endNode;
    double E;        // Young's modulus
    double A;        // Cross-sectional area
    double L;        // Length
    double angle;    // Orientation angle
};

int main() {
    // Material properties - 10 members
    double E1 = 2.0e11;    // Steel Young's modulus (Pa)
    double E2 = 2.0e11;
    double E3 = 2.0e11;
    double E4 = 2.0e11;
    double E5 = 2.0e11;
    double E6 = 2.0e11;
    double E7 = 2.0e11;
    double E8 = 2.0e11;
    double E9 = 2.0e11;
    double E10 = 2.0e11;
    
    // Cross-sectional areas (m^2)
    double A1 = 0.001;
    double A2 = 0.001;
    double A3 = 0.001;
    double A4 = 0.0015;
    double A5 = 0.0015;
    double A6 = 0.001;
    double A7 = 0.001;
    double A8 = 0.001;
    double A9 = 0.001;
    double A10 = 0.001;
    
    // Nodal coordinates (m)
    double x1 = 0.0, y1 = 0.0;
    double x2 = 4.0, y2 = 0.0;
    double x3 = 8.0, y3 = 0.0;
    double x4 = 12.0, y4 = 0.0;
    double x5 = 2.0, y5 = 3.0;
    double x6 = 6.0, y6 = 3.0;
    double x7 = 10.0, y7 = 3.0;
    double x8 = 0.0, y8 = 6.0;
    double x9 = 4.0, y9 = 6.0;
    double x10 = 8.0, y10 = 6.0;
    
    // External forces (N)
    double Fx5 = 0.0, Fy5 = -50000.0;
    double Fx6 = 0.0, Fy6 = -50000.0;
    double Fx7 = 0.0, Fy7 = -50000.0;
    
    // Support reactions will be calculated
    double Rx1, Ry1, Rx4, Ry4;
    
    // Calculate member lengths and angles
    double L1 = sqrt((x5-x1)*(x5-x1) + (y5-y1)*(y5-y1));
    double L2 = sqrt((x5-x2)*(x5-x2) + (y5-y2)*(y5-y2));
    double L3 = sqrt((x6-x2)*(x6-x2) + (y6-y2)*(y6-y2));
    double L4 = sqrt((x6-x3)*(x6-x3) + (y6-y3)*(y6-y3));
    double L5 = sqrt((x7-x3)*(x7-x3) + (y7-y3)*(y7-y3));
    double L6 = sqrt((x7-x4)*(x7-x4) + (y7-y4)*(y7-y4));
    double L7 = sqrt((x8-x1)*(x8-x1) + (y8-y1)*(y8-y1));
    double L8 = sqrt((x8-x5)*(x8-x5) + (y8-y5)*(y8-y5));
    double L9 = sqrt((x9-x5)*(x9-x5) + (y9-y5)*(y9-y5));
    double L10 = sqrt((x9-x6)*(x9-x6) + (y9-y6)*(y9-y6));
    
    // Member orientation angles (radians)
    double angle1 = atan2(y5-y1, x5-x1);
    double angle2 = atan2(y5-y2, x5-x2);
    double angle3 = atan2(y6-y2, x6-x2);
    double angle4 = atan2(y6-y3, x6-x3);
    double angle5 = atan2(y7-y3, x7-x3);
    double angle6 = atan2(y7-y4, x7-x4);
    double angle7 = atan2(y8-y1, x8-x1);
    double angle8 = atan2(y8-y5, x8-x5);
    double angle9 = atan2(y9-y5, x9-x5);
    double angle10 = atan2(y9-y6, x9-x6);
    
    // Direction cosines
    double cos1 = cos(angle1), sin1 = sin(angle1);
    double cos2 = cos(angle2), sin2 = sin(angle2);
    double cos3 = cos(angle3), sin3 = sin(angle3);
    double cos4 = cos(angle4), sin4 = sin(angle4);
    double cos5 = cos(angle5), sin5 = sin(angle5);
    double cos6 = cos(angle6), sin6 = sin(angle6);
    double cos7 = cos(angle7), sin7 = sin(angle7);
    double cos8 = cos(angle8), sin8 = sin(angle8);
    double cos9 = cos(angle9), sin9 = sin(angle9);
    double cos10 = cos(angle10), sin10 = sin(angle10);
    
    // Member stiffness values (EA/L)
    double k1 = E1 * A1 / L1;
    double k2 = E2 * A2 / L2;
    double k3 = E3 * A3 / L3;
    double k4 = E4 * A4 / L4;
    double k5 = E5 * A5 / L5;
    double k6 = E6 * A6 / L6;
    double k7 = E7 * A7 / L7;
    double k8 = E8 * A8 / L8;
    double k9 = E9 * A9 / L9;
    double k10 = E10 * A10 / L10;
    
    // Global stiffness matrix components (simplified for demonstration)
    // In practice, this would be a 20x20 matrix for 10 nodes with 2 DOF each
    
    // Calculate displacements at loaded nodes (simplified 2x2 system)
    double K55, K56, K65, K66;
    
    K55 = k1*sin1*sin1 + k2*sin2*sin2 + k8*sin8*sin8 + k9*sin9*sin9;
    K56 = k1*sin1*cos1 + k2*sin2*cos2 + k8*sin8*cos8 + k9*sin9*cos9;
    K65 = K56;
    K66 = k1*cos1*cos1 + k2*cos2*cos2 + k8*cos8*cos8 + k9*cos9*cos9;
    
    // Solve using Cramer's rule for demonstration
    double detK = K55 * K66 - K56 * K65;
    double u5 = (Fy5 * K66 - K56 * 0.0) / detK;  // Vertical displacement at node 5
    double v5 = (K55 * 0.0 - Fy5 * K65) / detK;  // Horizontal displacement at node 5
    
    // Calculate member forces
    double force1 = k1 * (u5 * sin1 + v5 * cos1);
    double force2 = k2 * (u5 * sin2 + v5 * cos2);
    double force8 = k8 * (u5 * sin8 + v5 * cos8);
    double force9 = k9 * (u5 * sin9 + v5 * cos9);
    
    // Calculate stresses (Pa)
    double stress1 = force1 / A1;
    double stress2 = force2 / A2;
    double stress8 = force8 / A8;
    double stress9 = force9 / A9;
    
    // Output results
    std::cout << "Node 5 Displacements:" << std::endl;
    std::cout << "Horizontal: " << v5 << " m" << std::endl;
    std::cout << "Vertical: " << u5 << " m" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Member Stresses:" << std::endl;
    std::cout << "Member 1: " << stress1/1e6 << " MPa" << std::endl;
    std::cout << "Member 2: " << stress2/1e6 << " MPa" << std::endl;
    std::cout << "Member 8: " << stress8/1e6 << " MPa" << std::endl;
    std::cout << "Member 9: " << stress9/1e6 << " MPa" << std::endl;
    
    return 0;
}
