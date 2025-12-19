#include <iostream>
#include <cmath>

// Calculates bearing capacity for a multi-layer soil foundation
// Uses Terzaghi's bearing capacity theory with Meyerhof modifications

int main() {
    // Soil layer thicknesses (8 variables)
    double layer1_depth = 1.5, layer2_depth = 2.0, layer3_depth = 1.8;
    double layer4_depth = 2.5, layer5_depth = 3.2, layer6_depth = 2.2;
    double layer7_depth = 1.9, layer8_depth = 4.0;

    // Cohesion values for each layer kPa (8 variables)
    double c1 = 25.0, c2 = 15.0, c3 = 35.0, c4 = 10.0;
    double c5 = 45.0, c6 = 20.0, c7 = 30.0, c8 = 18.0;

    // Friction angles in degrees (8 variables)
    double phi1 = 28.0, phi2 = 32.0, phi3 = 24.0, phi4 = 35.0;
    double phi5 = 22.0, phi6 = 30.0, phi7 = 26.0, phi8 = 33.0;

    // Unit weights in kN/m3 (8 variables)
    double gamma1 = 18.5, gamma2 = 19.2, gamma3 = 17.8, gamma4 = 19.8;
    double gamma5 = 17.5, gamma6 = 18.9, gamma7 = 18.1, gamma8 = 19.5;

    // Foundation parameters (8 variables)
    double foundation_width = 3.0, foundation_length = 4.5;
    double foundation_depth = 1.2, eccentricity_x = 0.15, eccentricity_y = 0.10;
    double inclination_angle = 5.0, groundwater_depth = 2.5;
    double factor_safety = 2.5;

    // Bearing capacity factors (9 variables)
    double Nc1, Nq1, Ng1, Nc2, Nq2, Ng2, Nc3, Nq3, Ng3;
    double Nc4, Nq4, Ng4, Nc5, Nq5, Ng5, Nc6, Nq6, Ng6;
    double Nc7, Nq7, Ng7, Nc8, Nq8, Ng8;

    // Shape correction factors (9 variables)
    double sc1, sq1, sg1, sc2, sq2, sg2, sc3, sq3, sg3;
    double sc4, sq4, sg4, sc5, sq5, sg5, sc6, sq6, sg6;
    double sc7, sq7, sg7, sc8, sq8, sg8;

    // Depth correction factors (8 variables)
    double dc1, dq1, dg1, dc2, dq2, dg2, dc3, dq3;
    double dg3, dc4, dq4, dg4, dc5, dq5, dg5, dc6;

    // Inclination correction factors (8 variables)
    double ic1, iq1, ig1, ic2, iq2, ig2, ic3, iq3;
    double ig3, ic4, iq4, ig4, ic5, iq5, ig5, ic6;

    // Ultimate bearing capacities (8 variables)
    double qult1, qult2, qult3, qult4, qult5, qult6, qult7, qult8;

    // Allowable bearing capacities (8 variables)
    double qallow1, qallow2, qallow3, qallow4, qallow5, qallow6, qallow7, qallow8;

    // Effective dimensions (4 variables)
    double effective_width, effective_length, effective_area, shape_ratio;

    // Depth factors
    double depth_factor_width, depth_factor_length;

    // Calculate bearing capacity factors for each layer
    double phi_rad1 = phi1 * M_PI / 180.0;
    Nq1 = exp(M_PI * tan(phi_rad1)) * pow(tan(M_PI / 4 + phi_rad1 / 2), 2);
    Nc1 = (Nq1 - 1) / tan(phi_rad1);
    Ng1 = 2 * (Nq1 - 1) * tan(phi_rad1);

    double phi_rad2 = phi2 * M_PI / 180.0;
    Nq2 = exp(M_PI * tan(phi_rad2)) * pow(tan(M_PI / 4 + phi_rad2 / 2), 2);
    Nc2 = (Nq2 - 1) / tan(phi_rad2);
    Ng2 = 2 * (Nq2 - 1) * tan(phi_rad2);

    double phi_rad3 = phi3 * M_PI / 180.0;
    Nq3 = exp(M_PI * tan(phi_rad3)) * pow(tan(M_PI / 4 + phi_rad3 / 2), 2);
    Nc3 = (Nq3 - 1) / tan(phi_rad3);
    Ng3 = 2 * (Nq3 - 1) * tan(phi_rad3);

    double phi_rad4 = phi4 * M_PI / 180.0;
    Nq4 = exp(M_PI * tan(phi_rad4)) * pow(tan(M_PI / 4 + phi_rad4 / 2), 2);
    Nc4 = (Nq4 - 1) / tan(phi_rad4);
    Ng4 = 2 * (Nq4 - 1) * tan(phi_rad4);

    double phi_rad5 = phi5 * M_PI / 180.0;
    Nq5 = exp(M_PI * tan(phi_rad5)) * pow(tan(M_PI / 4 + phi_rad5 / 2), 2);
    Nc5 = (Nq5 - 1) / tan(phi_rad5);
    Ng5 = 2 * (Nq5 - 1) * tan(phi_rad5);

    double phi_rad6 = phi6 * M_PI / 180.0;
    Nq6 = exp(M_PI * tan(phi_rad6)) * pow(tan(M_PI / 4 + phi_rad6 / 2), 2);
    Nc6 = (Nq6 - 1) / tan(phi_rad6);
    Ng6 = 2 * (Nq6 - 1) * tan(phi_rad6);

    double phi_rad7 = phi7 * M_PI / 180.0;
    Nq7 = exp(M_PI * tan(phi_rad7)) * pow(tan(M_PI / 4 + phi_rad7 / 2), 2);
    Nc7 = (Nq7 - 1) / tan(phi_rad7);
    Ng7 = 2 * (Nq7 - 1) * tan(phi_rad7);

    double phi_rad8 = phi8 * M_PI / 180.0;
    Nq8 = exp(M_PI * tan(phi_rad8)) * pow(tan(M_PI / 4 + phi_rad8 / 2), 2);
    Nc8 = (Nq8 - 1) / tan(phi_rad8);
    Ng8 = 2 * (Nq8 - 1) * tan(phi_rad8);

    // Calculate shape correction factors
    shape_ratio = foundation_length / foundation_width;
    
    sc1 = 1 + (foundation_width / foundation_length) * (Nq1 / Nc1);
    sq1 = 1 + (foundation_width / foundation_length) * tan(phi_rad1);
    sg1 = 1 - 0.4 * (foundation_width / foundation_length);

    sc2 = 1 + (foundation_width / foundation_length) * (Nq2 / Nc2);
    sq2 = 1 + (foundation_width / foundation_length) * tan(phi_rad2);
    sg2 = 1 - 0.4 * (foundation_width / foundation_length);

    sc3 = 1 + (foundation_width / foundation_length) * (Nq3 / Nc3);
    sq3 = 1 + (foundation_width / foundation_length) * tan(phi_rad3);
    sg3 = 1 - 0.4 * (foundation_width / foundation_length);

    sc4 = 1 + (foundation_width / foundation_length) * (Nq4 / Nc4);
    sq4 = 1 + (foundation_width / foundation_length) * tan(phi_rad4);
    sg4 = 1 - 0.4 * (foundation_width / foundation_length);

    sc5 = 1 + (foundation_width / foundation_length) * (Nq5 / Nc5);
    sq5 = 1 + (foundation_width / foundation_length) * tan(phi_rad5);
    sg5 = 1 - 0.4 * (foundation_width / foundation_length);

    sc6 = 1 + (foundation_width / foundation_length) * (Nq6 / Nc6);
    sq6 = 1 + (foundation_width / foundation_length) * tan(phi_rad6);
    sg6 = 1 - 0.4 * (foundation_width / foundation_length);

    sc7 = 1 + (foundation_width / foundation_length) * (Nq7 / Nc7);
    sq7 = 1 + (foundation_width / foundation_length) * tan(phi_rad7);
    sg7 = 1 - 0.4 * (foundation_width / foundation_length);

    sc8 = 1 + (foundation_width / foundation_length) * (Nq8 / Nc8);
    sq8 = 1 + (foundation_width / foundation_length) * tan(phi_rad8);
    sg8 = 1 - 0.4 * (foundation_width / foundation_length);

    // Effective dimensions considering eccentricity
    effective_width = foundation_width - 2 * eccentricity_x;
    effective_length = foundation_length - 2 * eccentricity_y;
    effective_area = effective_width * effective_length;

    // Calculate bearing capacity for each layer
    double overburden_pressure1 = gamma1 * foundation_depth;
    double overburden_pressure2 = gamma2 * (foundation_depth + layer1_depth);
    double overburden_pressure3 = gamma3 * (foundation_depth + layer1_depth + layer2_depth);
    double overburden_pressure4 = gamma4 * (foundation_depth + layer1_depth + layer2_depth + layer3_depth);
    double overburden_pressure5 = gamma5 * (foundation_depth + layer1_depth + layer2_depth + layer3_depth + layer4_depth);
    double overburden_pressure6 = gamma6 * (foundation_depth + layer1_depth + layer2_depth + layer3_depth + layer4_depth + layer5_depth);
    double overburden_pressure7 = gamma7 * (foundation_depth + layer1_depth + layer2_depth + layer3_depth + layer4_depth + layer5_depth + layer6_depth);
    double overburden_pressure8 = gamma8 * (foundation_depth + layer1_depth + layer2_depth + layer3_depth + layer4_depth + layer5_depth + layer6_depth + layer7_depth);

    qult1 = c1 * Nc1 * sc1 * dc1 * ic1 + overburden_pressure1 * Nq1 * sq1 * dq1 * iq1 + 0.5 * gamma1 * effective_width * Ng1 * sg1 * dg1 * ig1;
    qult2 = c2 * Nc2 * sc2 * dc2 * ic2 + overburden_pressure2 * Nq2 * sq2 * dq2 * iq2 + 0.5 * gamma2 * effective_width * Ng2 * sg2 * dg2 * ig2;
    qult3 = c3 * Nc3 * sc3 * dc3 * ic3 + overburden_pressure3 * Nq3 * sq3 * dq3 * iq3 + 0.5 * gamma3 * effective_width * Ng3 * sg3 * dg3 * ig3;
    qult4 = c4 * Nc4 * sc4 * dc4 * ic4 + overburden_pressure4 * Nq4 * sq4 * dq4 * iq4 + 0.5 * gamma4 * effective_width * Ng4 * sg4 * dg4 * ig4;
    qult5 = c5 * Nc5 * sc5 * dc5 * ic5 + overburden_pressure5 * Nq5 * sq5 * dq5 * iq5 + 0.5 * gamma5 * effective_width * Ng5 * sg5 * dg5 * ig5;
    qult6 = c6 * Nc6 * sc6 * dc6 * ic6 + overburden_pressure6 * Nq6 * sq6 * dq6 + 0.5 * gamma6 * effective_width * Ng6 * sg6 * dg6;
    qult7 = c7 * Nc7 * sc7 * dc7 * ic7 + overburden_pressure7 * Nq7 + 0.5 * gamma7 * effective_width * Ng7;
    qult8 = c8 * Nc8 * sc8 * dc8 * ic8 + overburden_pressure8 * Nq8 + 0.5 * gamma8 * effective_width * Ng8;

    // Apply safety factors
    qallow1 = qult1 / factor_safety;
    qallow2 = qult2 / factor_safety;
    qallow3 = qult3 / factor_safety;
    qallow4 = qult4 / factor_safety;
    qallow5 = qult5 / factor_safety;
    qallow6 = qult6 / factor_safety;
    qallow7 = qult7 / factor_safety;
    qallow8 = qult8 / factor_safety;

    // Output results
    std::cout << "Layer 1 Allowable Bearing Capacity: " << qallow1 << " kPa" << std::endl;
    std::cout << "Layer 3 Allowable Bearing Capacity: " << qallow3 << " kPa" << std::endl;
    std::cout << "Layer 5 Allowable Bearing Capacity: " << qallow5 << " kPa" << std::endl;
    std::cout << "Critical Layer (Minimum Capacity): " << fmin(fmin(qallow1, qallow2), fmin(qallow3, qallow4)) << " kPa" << std::endl;
    std::cout << "Effective Foundation Area: " << effective_area << " m2" << std::endl;

    return 0;
}
