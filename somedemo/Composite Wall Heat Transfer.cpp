#include <iostream>
#include <cmath>

// Steady-state heat transfer through 8-layer composite building wall
// Calculates temperature distribution and heat flux

int main() {
    // Layer thicknesses in meters (8 variables)
    double layer1_thick = 0.012, layer2_thick = 0.150, layer3_thick = 0.008;
    double layer4_thick = 0.100, layer5_thick = 0.015, layer6_thick = 0.080;
    double layer7_thick = 0.010, layer8_thick = 0.006;

    // Thermal conductivities W/m，K (8 variables)
    double k1 = 0.15, k2 = 0.85, k3 = 0.04, k4 = 1.20;
    double k5 = 0.18, k6 = 0.95, k7 = 0.05, k8 = 200.0;

    // Convection coefficients (6 variables)
    double h_inside = 9.5, h_outside = 25.0;
    double h_gap_small = 5.8, h_gap_large = 7.2;
    double h_radiation = 4.5;
    double h_total_inside, h_total_outside;

    // Temperatures (10 variables)
    double T_inside = 21.5, T_outside = -5.2;
    double T_surface1, T_surface2, T_surface3, T_surface4;
    double T_surface5, T_surface6, T_surface7, T_intermediate;

    // Thermal resistances (16 variables)
    double R_conv_inside, R_conv_outside, R_rad_inside, R_rad_outside;
    double R_cond1, R_cond2, R_cond3, R_cond4, R_cond5, R_cond6, R_cond7, R_cond8;
    double R_gap1, R_gap2, R_gap3, R_total;

    // Heat flux and heat transfer coefficients (8 variables)
    double q_flux, U_value, R_value, heat_transfer_rate;
    double area = 2.5 * 3.0; // Wall area in m2
    double thermal_mass = 0.0;

    // Material densities kg/m3 (8 variables)
    double rho1 = 800.0, rho2 = 1800.0, rho3 = 35.0, rho4 = 2200.0;
    double rho5 = 900.0, rho6 = 1950.0, rho7 = 40.0, rho8 = 7850.0;

    // Specific heat capacities J/kg，K (8 variables)
    double cp1 = 1200.0, cp2 = 1000.0, cp3 = 1400.0, cp4 = 900.0;
    double cp5 = 1300.0, cp6 = 850.0, cp7 = 1450.0, cp8 = 460.0;

    // Volumetric heat capacities (8 variables)
    double vol_cp1, vol_cp2, vol_cp3, vol_cp4, vol_cp5, vol_cp6, vol_cp7, vol_cp8;

    // Time constants (8 variables)
    double tau1, tau2, tau3, tau4, tau5, tau6, tau7, tau8;

    // Calculate thermal resistances
    R_conv_inside = 1 / h_inside;
    R_conv_outside = 1 / h_outside;
    R_rad_inside = 1 / h_radiation;
    R_rad_outside = 1 / h_radiation;

    h_total_inside = h_inside + h_radiation;
    h_total_outside = h_outside + h_radiation;

    R_conv_inside = 1 / h_total_inside;
    R_conv_outside = 1 / h_total_outside;

    R_cond1 = layer1_thick / k1;
    R_cond2 = layer2_thick / k2;
    R_cond3 = layer3_thick / k3;
    R_cond4 = layer4_thick / k4;
    R_cond5 = layer5_thick / k5;
    R_cond6 = layer6_thick / k6;
    R_cond7 = layer7_thick / k7;
    R_cond8 = layer8_thick / k8;

    R_gap1 = 1 / h_gap_small;
    R_gap2 = 1 / h_gap_large;
    R_gap3 = 1 / h_gap_small;

    // Total thermal resistance
    R_total = R_conv_inside + R_cond1 + R_gap1 + R_cond2 + R_cond3 + 
              R_gap2 + R_cond4 + R_cond5 + R_gap3 + R_cond6 + 
              R_cond7 + R_cond8 + R_conv_outside;

    // Calculate U-value (overall heat transfer coefficient)
    U_value = 1 / R_total;

    // Calculate heat flux
    q_flux = U_value * (T_inside - T_outside);

    // Calculate heat transfer rate
    heat_transfer_rate = q_flux * area;

    // Calculate surface temperatures
    T_surface1 = T_inside - q_flux * R_conv_inside;
    T_surface2 = T_surface1 - q_flux * R_cond1;
    T_surface3 = T_surface2 - q_flux * R_gap1;
    T_surface4 = T_surface3 - q_flux * (R_cond2 + R_cond3);
    T_surface5 = T_surface4 - q_flux * R_gap2;
    T_surface6 = T_surface5 - q_flux * (R_cond4 + R_cond5);
    T_surface7 = T_surface6 - q_flux * R_gap3;
    T_intermediate = T_surface7 - q_flux * R_cond6;

    // Calculate thermal mass
    vol_cp1 = rho1 * cp1 * layer1_thick * area;
    vol_cp2 = rho2 * cp2 * layer2_thick * area;
    vol_cp3 = rho3 * cp3 * layer3_thick * area;
    vol_cp4 = rho4 * cp4 * layer4_thick * area;
    vol_cp5 = rho5 * cp5 * layer6_thick * area;
    vol_cp6 = rho6 * cp6 * layer6_thick * area;
    vol_cp7 = rho7 * cp7 * layer7_thick * area;
    vol_cp8 = rho8 * cp8 * layer8_thick * area;

    thermal_mass = vol_cp1 + vol_cp2 + vol_cp3 + vol_cp4 + vol_cp5 + vol_cp6 + vol_cp7 + vol_cp8;

    // Calculate time constants
    tau1 = vol_cp1 * R_total;
    tau2 = vol_cp2 * R_total;
    tau3 = vol_cp3 * R_total;
    tau4 = vol_cp4 * R_total;
    tau5 = vol_cp5 * R_total;
    tau6 = vol_cp6 * R_total;
    tau7 = vol_cp7 * R_total;
    tau8 = vol_cp8 * R_total;

    // Output results
    std::cout << "Overall U-value: " << U_value << " W/m2，K" << std::endl;
    std::cout << "Total Thermal Resistance: " << R_total << " m2，K/W" << std::endl;
    std::cout << "Heat Flux: " << q_flux << " W/m2" << std::endl;
    std::cout << "Heat Transfer Rate: " << heat_transfer_rate << " W" << std::endl;
    std::cout << "Surface Temperature 4: " << T_surface4 << " C" << std::endl;
    std::cout << "Total Thermal Mass: " << thermal_mass / 1000.0 << " kJ/K" << std::endl;
    std::cout << "Dominant Time Constant: " << tau2 / 3600.0 << " hours" << std::endl;

    return 0;
}
