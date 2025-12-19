#include <iostream>
using namespace std;

int main() {
    double celsiusStart = -20.0;     // Start temperature in Celsius
    double celsiusEnd = 40.0;        // End temperature in Celsius
    double step = 5.0;               // Temperature step
    
    cout << "Celsius\tFahrenheit\tKelvin" << endl;
    
    // Convert temperature range
    for (double c = celsiusStart; c <= celsiusEnd + 0.001; c += step) {
        double fahrenheit = c * 9.0/5.0 + 32.0;
        double kelvin = c + 273.15;
        cout << c << "\t" << fahrenheit << "\t\t" << kelvin << endl;
    }
    return 0;
}
