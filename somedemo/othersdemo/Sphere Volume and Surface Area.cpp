#include <iostream>
#define PI 3.141592653589793
using namespace std;

int main() {
    double radiusMin = 1.0;     // cm
    double radiusMax = 10.0;    // cm
    double steps = 20.0;
    
    cout << "Radius(cm)\tVolume(cm3)\tSurface(cm2)" << endl;
    
    // Calculate properties for various radii
    for (double r = radiusMin; r <= radiusMax; r += (radiusMax-radiusMin)/steps) {
        double volume = (4.0/3.0) * PI * r * r * r;
        double surface = 4.0 * PI * r * r;
        cout << r << "\t\t" << volume << "\t\t" << surface << endl;
    }
    return 0;
}
