#include <iostream>
#include <cmath>

// Calculates wind loads on a 20-story building
// Based on ASCE 7-16 standards and logarithmic wind speed profile

int main() {
    // Building geometry parameters (20 variables)
    double floor1_height = 4.0, floor2_height = 4.0, floor3_height = 4.0;
    double floor4_height = 4.0, floor5_height = 4.0, floor6_height = 4.0;
    double floor7_height = 4.0, floor8_height = 4.0, floor9_height = 4.0;
    double floor10_height = 4.0, floor11_height = 4.0, floor12_height = 4.0;
    double floor13_height = 4.0, floor14_height = 4.0, floor15_height = 4.0;
    double floor16_height = 4.0, floor17_height = 4.0, floor18_height = 4.0;
    double floor19_height = 4.0, floor20_height = 4.0;

    double building_width = 30.0, building_depth = 20.0;
    double roof_height = 3.0, parapet_height = 1.5;

    // Wind parameters (15 variables)
    double wind_speed_10m = 45.0; // m/s at 10m height
    double terrain_roughness = 0.15; // m
    double air_density = 1.225; // kg/m3
    double exposure_category = 3.0;
    double gust_factor = 0.85;
    double importance_factor = 1.0;
    double wind_directionality = 0.85;
    double topographic_factor = 1.0;
    double enclosure_classification = 1.0;
    double internal_pressure_coef = 0.18;
    double external_pressure_coef_windward = 0.8;
    double external_pressure_coef_leeward = -0.5;
    double external_pressure_coef_side = -0.7;
    double velocity_pressure_exp_coeff = 1.0;
    double velocity_pressure_top_coeff = 1.0;

    // Floor elevations (20 variables)
    double elev_floor1, elev_floor2, elev_floor3, elev_floor4, elev_floor5;
    double elev_floor6, elev_floor7, elev_floor8, elev_floor9, elev_floor10;
    double elev_floor11, elev_floor12, elev_floor13, elev_floor14, elev_floor15;
    double elev_floor16, elev_floor17, elev_floor18, elev_floor19, elev_floor20;

    // Wind speeds at each floor (20 variables)
    double wind_floor1, wind_floor2, wind_floor3, wind_floor4, wind_floor5;
    double wind_floor6, wind_floor7, wind_floor8, wind_floor9, wind_floor10;
    double wind_floor11, wind_floor12, wind_floor13, wind_floor14, wind_floor15;
    double wind_floor16, wind_floor17, wind_floor18, wind_floor19, wind_floor20;

    // Pressure coefficients (20 variables)
    double pressure_coef_floor1, pressure_coef_floor2, pressure_coef_floor3;
    double pressure_coef_floor4, pressure_coef_floor5, pressure_coef_floor6;
    double pressure_coef_floor7, pressure_coef_floor8, pressure_coef_floor9;
    double pressure_coef_floor10, pressure_coef_floor11, pressure_coef_floor12;
    double pressure_coef_floor13, pressure_coef_floor14, pressure_coef_floor15;
    double pressure_coef_floor16, pressure_coef_floor17, pressure_coef_floor18;
    double pressure_coef_floor19, pressure_coef_floor20;

    // Wind pressures and forces (40 variables)
    double pressure_floor1, pressure_floor2, pressure_floor3, pressure_floor4;
    double pressure_floor5, pressure_floor6, pressure_floor7, pressure_floor8;
    double pressure_floor9, pressure_floor10, pressure_floor11, pressure_floor12;
    double pressure_floor13, pressure_floor14, pressure_floor15, pressure_floor16;
    double pressure_floor17, pressure_floor18, pressure_floor19, pressure_floor20;

    double force_floor1, force_floor2, force_floor3, force_floor4;
    double force_floor5, force_floor6, force_floor7, force_floor8;
    double force_floor9, force_floor10, force_floor11, force_floor12;
    double force_floor13, force_floor14, force_floor15, force_floor16;
    double force_floor17, force_floor18, force_floor19, force_floor20;

    // Calculate cumulative elevations
    elev_floor1 = floor1_height;
    elev_floor2 = elev_floor1 + floor2_height;
    elev_floor3 = elev_floor2 + floor3_height;
    elev_floor4 = elev_floor3 + floor4_height;
    elev_floor5 = elev_floor4 + floor5_height;
    elev_floor6 = elev_floor5 + floor6_height;
    elev_floor7 = elev_floor6 + floor7_height;
    elev_floor8 = elev_floor7 + floor8_height;
    elev_floor9 = elev_floor8 + floor9_height;
    elev_floor10 = elev_floor9 + floor10_height;
    elev_floor11 = elev_floor10 + floor11_height;
    elev_floor12 = elev_floor11 + floor12_height;
    elev_floor13 = elev_floor12 + floor13_height;
    elev_floor14 = elev_floor13 + floor14_height;
    elev_floor15 = elev_floor14 + floor15_height;
    elev_floor16 = elev_floor15 + floor16_height;
    elev_floor17 = elev_floor16 + floor17_height;
    elev_floor18 = elev_floor17 + floor18_height;
    elev_floor19 = elev_floor18 + floor19_height;
    elev_floor20 = elev_floor19 + floor20_height;

    // Calculate wind speeds at each floor using log law profile
    wind_floor1 = wind_speed_10m * log(elev_floor1 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor2 = wind_speed_10m * log(elev_floor2 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor3 = wind_speed_10m * log(elev_floor3 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor4 = wind_speed_10m * log(elev_floor4 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor5 = wind_speed_10m * log(elev_floor5 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor6 = wind_speed_10m * log(elev_floor6 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor7 = wind_speed_10m * log(elev_floor7 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor8 = wind_speed_10m * log(elev_floor8 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor9 = wind_speed_10m * log(elev_floor9 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor10 = wind_speed_10m * log(elev_floor10 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor11 = wind_speed_10m * log(elev_floor11 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor12 = wind_speed_10m * log(elev_floor12 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor13 = wind_speed_10m * log(elev_floor13 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor14 = wind_speed_10m * log(elev_floor14 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor15 = wind_speed_10m * log(elev_floor15 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor16 = wind_speed_10m * log(elev_floor16 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor17 = wind_speed_10m * log(elev_floor17 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor18 = wind_speed_10m * log(elev_floor18 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor19 = wind_speed_10m * log(elev_floor19 / terrain_roughness) / log(10.0 / terrain_roughness);
    wind_floor20 = wind_speed_10m * log(elev_floor20 / terrain_roughness) / log(10.0 / terrain_roughness);

    // Calculate pressure coefficients (simplified)
    pressure_coef_floor1 = external_pressure_coef_windward + internal_pressure_coef;
    pressure_coef_floor2 = external_pressure_coef_windward + internal_pressure_coef;
    pressure_coef_floor3 = external_pressure_coef_windward + internal_pressure_coef;
    pressure_coef_floor4 = external_pressure_coef_windward + internal_pressure_coef;
    pressure_coef_floor5 = external_pressure_coef_windward + internal_pressure_coef;
    pressure_coef_floor6 = external_pressure_coef_windward + internal_pressure_coef;
    pressure_coef_floor7 = external_pressure_coef_windward + internal_pressure_coef;
    pressure_coef_floor8 = external_pressure_coef_windward + internal_pressure_coef;
    pressure_coef_floor9 = external_pressure_coef_windward + internal_pressure_coef;
    pressure_coef_floor10 = external_pressure_coef_side + internal_pressure_coef;
    pressure_coef_floor11 = external_pressure_coef_side + internal_pressure_coef;
    pressure_coef_floor12 = external_pressure_coef_side + internal_pressure_coef;
    pressure_coef_floor13 = external_pressure_coef_side + internal_pressure_coef;
    pressure_coef_floor14 = external_pressure_coef_side + internal_pressure_coef;
    pressure_coef_floor15 = external_pressure_coef_leeward + internal_pressure_coef;
    pressure_coef_floor16 = external_pressure_coef_leeward + internal_pressure_coef;
    pressure_coef_floor17 = external_pressure_coef_leeward + internal_pressure_coef;
    pressure_coef_floor18 = external_pressure_coef_leeward + internal_pressure_coef;
    pressure_coef_floor19 = external_pressure_coef_leeward + internal_pressure_coef;
    pressure_coef_floor20 = external_pressure_coef_leeward + internal_pressure_coef;

    // Calculate wind pressures (kN/m2)
    pressure_floor1 = 0.5 * air_density * pow(wind_floor1, 2) * pressure_coef_floor1 / 1000.0;
    pressure_floor2 = 0.5 * air_density * pow(wind_floor2, 2) * pressure_coef_floor2 / 1000.0;
    pressure_floor3 = 0.5 * air_density * pow(wind_floor3, 2) * pressure_coef_floor3 / 1000.0;
    pressure_floor4 = 0.5 * air_density * pow(wind_floor4, 2) * pressure_coef_floor4 / 1000.0;
    pressure_floor5 = 0.5 * air_density * pow(wind_floor5, 2) * pressure_coef_floor5 / 1000.0;
    pressure_floor6 = 0.5 * air_density * pow(wind_floor6, 2) * pressure_coef_floor6 / 1000.0;
    pressure_floor7 = 0.5 * air_density * pow(wind_floor7, 2) * pressure_coef_floor7 / 1000.0;
    pressure_floor8 = 0.5 * air_density * pow(wind_floor8, 2) * pressure_coef_floor8 / 1000.0;
    pressure_floor9 = 0.5 * air_density * pow(wind_floor9, 2) * pressure_coef_floor9 / 1000.0;
    pressure_floor10 = 0.5 * air_density * pow(wind_floor10, 2) * pressure_coef_floor10 / 1000.0;
    pressure_floor11 = 0.5 * air_density * pow(wind_floor11, 2) * pressure_coef_floor11 / 1000.0;
    pressure_floor12 = 0.5 * air_density * pow(wind_floor12, 2) * pressure_coef_floor12 / 1000.0;
    pressure_floor13 = 0.5 * air_density * pow(wind_floor13, 2) * pressure_coef_floor13 / 1000.0;
    pressure_floor14 = 0.5 * air_density * pow(wind_floor14, 2) * pressure_coef_floor14 / 1000.0;
    pressure_floor15 = 0.5 * air_density * pow(wind_floor15, 2) * pressure_coef_floor15 / 1000.0;
    pressure_floor16 = 0.5 * air_density * pow(wind_floor16, 2) * pressure_coef_floor16 / 1000.0;
    pressure_floor17 = 0.5 * air_density * pow(wind_floor17, 2) * pressure_coef_floor17 / 1000.0;
    pressure_floor18 = 0.5 * air_density * pow(wind_floor18, 2) * pressure_coef_floor18 / 1000.0;
    pressure_floor19 = 0.5 * air_density * pow(wind_floor19, 2) * pressure_coef_floor19 / 1000.0;
    pressure_floor20 = 0.5 * air_density * pow(wind_floor20, 2) * pressure_coef_floor20 / 1000.0;

    // Calculate wind forces per floor (kN)
    double floor_area = building_width * floor1_height;
    force_floor1 = pressure_floor1 * floor_area;
    force_floor2 = pressure_floor2 * floor_area;
    force_floor3 = pressure_floor3 * floor_area;
    force_floor4 = pressure_floor4 * floor_area;
    force_floor5 = pressure_floor5 * floor_area;
    force_floor6 = pressure_floor6 * floor_area;
    force_floor7 = pressure_floor7 * floor_area;
    force_floor8 = pressure_floor8 * floor_area;
    force_floor9 = pressure_floor9 * floor_area;
    force_floor10 = pressure_floor10 * floor_area;
    force_floor11 = pressure_floor11 * floor_area;
    force_floor12 = pressure_floor12 * floor_area;
    force_floor13 = pressure_floor13 * floor_area;
    force_floor14 = pressure_floor14 * floor_area;
    force_floor15 = pressure_floor15 * floor_area;
    force_floor16 = pressure_floor16 * floor_area;
    force_floor17 = pressure_floor17 * floor_area;
    force_floor18 = pressure_floor18 * floor_area;
    force_floor19 = pressure_floor19 * floor_area;
    force_floor20 = pressure_floor20 * floor_area;

    // Output maximum wind force
    double max_force = force_floor20;
    std::cout << "Maximum wind force at top floor: " << max_force << " kN" << std::endl;
    std::cout << "Total wind base shear: " << force_floor1 + force_floor2 + force_floor3 + force_floor4 + force_floor5 << " kN" << std::endl;

    return 0;
}
