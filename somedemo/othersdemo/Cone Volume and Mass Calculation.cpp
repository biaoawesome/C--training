#include <iostream>
#define PI 3.141592653589793
using namespace std;

int main() {
    double radius = 5.0;         // Base radius in meters
    double height = 10.0;        // Height in meters
    double density = 7850.0;     // Material density kg/m3
    
    // Calculate volume and mass
    double volume = (1.0/3.0) * PI * radius * radius * height;
    double mass = volume * density;
    double surfaceArea = PI * radius * (radius + sqrt(height*height + radius*radius));
    
    cout << "Cone Properties:" << endl;
    cout << "Volume: " << volume << " m3" << endl;
    cout << "Mass: " << mass << " kg" << endl;
    cout << "Surface Area: " << surfaceArea << " m2" << endl;
    return 0;
}
