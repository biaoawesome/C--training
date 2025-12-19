#include <iostream>
#include <cmath>

// Analyzes flow in a 15-pipe municipal water distribution network
// Uses Darcy-Weisbach equation for head loss calculations

int main() {
    // Pipe lengths (15 variables)
    double pipe1_len = 1250.0, pipe2_len = 980.0, pipe3_len = 1500.0;
    double pipe4_len = 1100.0, pipe5_len = 890.0, pipe6_len = 1200.0;
    double pipe7_len = 1350.0, pipe8_len = 1050.0, pipe9_len = 1180.0;
    double pipe10_len = 920.0, pipe11_len = 1280.0, pipe12_len = 1420.0;
    double pipe13_len = 1150.0, pipe14_len = 1080.0, pipe15_len = 1320.0;

    // Pipe diameters in meters (15 variables)
    double pipe1_dia = 0.300, pipe2_dia = 0.250, pipe3_dia = 0.350;
    double pipe4_dia = 0.200, pipe5_dia = 0.300, pipe6_dia = 0.280;
    double pipe7_dia = 0.320, pipe8_dia = 0.260, pipe9_dia = 0.340;
    double pipe10_dia = 0.220, pipe11_dia = 0.310, pipe12_dia = 0.360;
    double pipe13_dia = 0.240, pipe14_dia = 0.270, pipe15_dia = 0.330;

    // Pipe roughness in mm (15 variables)
    double pipe1_rough = 0.15, pipe2_rough = 0.18, pipe3_rough = 0.12;
    double pipe4_rough = 0.20, pipe5_rough = 0.16, pipe6_rough = 0.19;
    double pipe7_rough = 0.14, pipe8_rough = 0.17, pipe9_rough = 0.13;
    double pipe10_rough = 0.21, pipe11_rough = 0.15, pipe12_rough = 0.11;
    double pipe13_rough = 0.19, pipe14_rough = 0.18, pipe15_rough = 0.14;

    // Flow rates in m3/s (15 variables)
    double pipe1_flow = 0.089, pipe2_flow = 0.067, pipe3_flow = 0.125;
    double pipe4_flow = 0.045, pipe5_flow = 0.098, pipe6_flow = 0.076;
    double pipe7_flow = 0.112, pipe8_flow = 0.058, pipe9_flow = 0.134;
    double pipe10_flow = 0.039, pipe11_flow = 0.105, pipe12_flow = 0.143;
    double pipe13_flow = 0.062, pipe14_flow = 0.071, pipe15_flow = 0.119;

    // Fluid properties (5 variables)
    double fluid_density = 998.0; // kg/m3 for water
    double fluid_viscosity = 0.001002; // Pa°§s at 20°„C
    double gravity = 9.81;
    double kinematic_viscosity = fluid_viscosity / fluid_density;
    double bulk_modulus = 2.15e9;

    // Node elevations - supply and demand points (10 variables)
    double node1_elev = 125.5, node2_elev = 118.2, node3_elev = 131.7;
    double node4_elev = 115.8, node5_elev = 142.3, node6_elev = 128.9;
    double node7_elev = 135.4, node8_elev = 122.1, node9_elev = 138.6;
    double node10_elev = 119.7;

    // Junction pressures (10 variables)
    double pressure_node1 = 350000.0, pressure_node2 = 320000.0, pressure_node3 = 380000.0;
    double pressure_node4 = 310000.0, pressure_node5 = 400000.0, pressure_node6 = 345000.0;
    double pressure_node7 = 365000.0, pressure_node8 = 335000.0, pressure_node9 = 390000.0;
    double pressure_node10 = 325000.0;

    // Reynolds numbers for each pipe (15 variables)
    double reynolds1, reynolds2, reynolds3, reynolds4, reynolds5;
    double reynolds6, reynolds7, reynolds8, reynolds9, reynolds10;
    double reynolds11, reynolds12, reynolds13, reynolds14, reynolds15;

    // Friction factors (15 variables)
    double friction1, friction2, friction3, friction4, friction5;
    double friction6, friction7, friction8, friction9, friction10;
    double friction11, friction12, friction13, friction14, friction15;

    // Head losses (15 variables)
    double headloss1, headloss2, headloss3, headloss4, headloss5;
    double headloss6, headloss7, headloss8, headloss9, headloss10;
    double headloss11, headloss12, headloss13, headloss14, headloss15;

    // Pressure drops (15 variables)
    double pressuredrop1, pressuredrop2, pressuredrop3, pressuredrop4, pressuredrop5;
    double pressuredrop6, pressuredrop7, pressuredrop8, pressuredrop9, pressuredrop10;
    double pressuredrop11, pressuredrop12, pressuredrop13, pressuredrop14, pressuredrop15;

    // Flow velocities (15 variables)
    double velocity1, velocity2, velocity3, velocity4, velocity5;
    double velocity6, velocity7, velocity8, velocity9, velocity10;
    double velocity11, velocity12, velocity13, velocity14, velocity15;

    // Calculate flow velocities
    velocity1 = pipe1_flow / (M_PI * pow(pipe1_dia / 2.0, 2));
    velocity2 = pipe2_flow / (M_PI * pow(pipe2_dia / 2.0, 2));
    velocity3 = pipe3_flow / (M_PI * pow(pipe3_dia / 2.0, 2));
    velocity4 = pipe4_flow / (M_PI * pow(pipe4_dia / 2.0, 2));
    velocity5 = pipe5_flow / (M_PI * pow(pipe5_dia / 2.0, 2));
    velocity6 = pipe6_flow / (M_PI * pow(pipe6_dia / 2.0, 2));
    velocity7 = pipe7_flow / (M_PI * pow(pipe7_dia / 2.0, 2));
    velocity8 = pipe8_flow / (M_PI * pow(pipe8_dia / 2.0, 2));
    velocity9 = pipe9_flow / (M_PI * pow(pipe9_dia / 2.0, 2));
    velocity10 = pipe10_flow / (M_PI * pow(pipe10_dia / 2.0, 2));
    velocity11 = pipe11_flow / (M_PI * pow(pipe11_dia / 2.0, 2));
    velocity12 = pipe12_flow / (M_PI * pow(pipe12_dia / 2.0, 2));
    velocity13 = pipe13_flow / (M_PI * pow(pipe13_dia / 2.0, 2));
    velocity14 = pipe14_flow / (M_PI * pow(pipe14_dia / 2.0, 2));
    velocity15 = pipe15_flow / (M_PI * pow(pipe15_dia / 2.0, 2));

    // Calculate Reynolds numbers
    reynolds1 = velocity1 * pipe1_dia / kinematic_viscosity;
    reynolds2 = velocity2 * pipe2_dia / kinematic_viscosity;
    reynolds3 = velocity3 * pipe3_dia / kinematic_viscosity;
    reynolds4 = velocity4 * pipe4_dia / kinematic_viscosity;
    reynolds5 = velocity5 * pipe5_dia / kinematic_viscosity;
    reynolds6 = velocity6 * pipe6_dia / kinematic_viscosity;
    reynolds7 = velocity7 * pipe7_dia / kinematic_viscosity;
    reynolds8 = velocity8 * pipe8_dia / kinematic_viscosity;
    reynolds9 = velocity9 * pipe9_dia / kinematic_viscosity;
    reynolds10 = velocity10 * pipe10_dia / kinematic_viscosity;
    reynolds11 = velocity11 * pipe11_dia / kinematic_viscosity;
    reynolds12 = velocity12 * pipe12_dia / kinematic_viscosity;
    reynolds13 = velocity13 * pipe13_dia / kinematic_viscosity;
    reynolds14 = velocity14 * pipe14_dia / kinematic_viscosity;
    reynolds15 = velocity15 * pipe15_dia / kinematic_viscosity;

    // Calculate friction factors using Swamee-Jain equation (turbulent flow)
    friction1 = 0.25 / pow(log10(pipe1_rough / (3.7 * pipe1_dia) + 5.74 / pow(reynolds1, 0.9)), 2);
    friction2 = 0.25 / pow(log10(pipe2_rough / (3.7 * pipe2_dia) + 5.74 / pow(reynolds2, 0.9)), 2);
    friction3 = 0.25 / pow(log10(pipe3_rough / (3.7 * pipe3_dia) + 5.74 / pow(reynolds3, 0.9)), 2);
    friction4 = 0.25 / pow(log10(pipe4_rough / (3.7 * pipe4_dia) + 5.74 / pow(reynolds4, 0.9)), 2);
    friction5 = 0.25 / pow(log10(pipe5_rough / (3.7 * pipe5_dia) + 5.74 / pow(reynolds5, 0.9)), 2);
    friction6 = 0.25 / pow(log10(pipe6_rough / (3.7 * pipe6_dia) + 5.74 / pow(reynolds6, 0.9)), 2);
    friction7 = 0.25 / pow(log10(pipe7_rough / (3.7 * pipe7_dia) + 5.74 / pow(reynolds7, 0.9)), 2);
    friction8 = 0.25 / pow(log10(pipe8_rough / (3.7 * pipe8_dia) + 5.74 / pow(reynolds8, 0.9)), 2);
    friction9 = 0.25 / pow(log10(pipe9_rough / (3.7 * pipe9_dia) + 5.74 / pow(reynolds9, 0.9)), 2);
    friction10 = 0.25 / pow(log10(pipe10_rough / (3.7 * pipe10_dia) + 5.74 / pow(reynolds10, 0.9)), 2);
    friction11 = 0.25 / pow(log10(pipe11_rough / (3.7 * pipe11_dia) + 5.74 / pow(reynolds11, 0.9)), 2);
    friction12 = 0.25 / pow(log10(pipe12_rough / (3.7 * pipe12_dia) + 5.74 / pow(reynolds12, 0.9)), 2);
    friction13 = 0.25 / pow(log10(pipe13_rough / (3.7 * pipe13_dia) + 5.74 / pow(reynolds13, 0.9)), 2);
    friction14 = 0.25 / pow(log10(pipe14_rough / (3.7 * pipe14_dia) + 5.74 / pow(reynolds14, 0.9)), 2);
    friction15 = 0.25 / pow(log10(pipe15_rough / (3.7 * pipe15_dia) + 5.74 / pow(reynolds15, 0.9)), 2);

    // Calculate head losses using Darcy-Weisbach equation
    headloss1 = friction1 * (pipe1_len / pipe1_dia) * (pow(velocity1, 2) / (2 * gravity));
    headloss2 = friction2 * (pipe2_len / pipe2_dia) * (pow(velocity2, 2) / (2 * gravity));
    headloss3 = friction3 * (pipe3_len / pipe3_dia) * (pow(velocity3, 2) / (2 * gravity));
    headloss4 = friction4 * (pipe4_len / pipe4_dia) * (pow(velocity4, 2) / (2 * gravity));
    headloss5 = friction5 * (pipe5_len / pipe5_dia) * (pow(velocity5, 2) / (2 * gravity));
    headloss6 = friction6 * (pipe6_len / pipe6_dia) * (pow(velocity6, 2) / (2 * gravity));
    headloss7 = friction7 * (pipe7_len / pipe7_dia) * (pow(velocity7, 2) / (2 * gravity));
    headloss8 = friction8 * (pipe8_len / pipe8_dia) * (pow(velocity8, 2) / (2 * gravity));
    headloss9 = friction9 * (pipe9_len / pipe9_dia) * (pow(velocity9, 2) / (2 * gravity));
    headloss10 = friction10 * (pipe10_len / pipe10_dia) * (pow(velocity10, 2) / (2 * gravity));
    headloss11 = friction11 * (pipe11_len / pipe11_dia) * (pow(velocity11, 2) / (2 * gravity));
    headloss12 = friction12 * (pipe12_len / pipe12_dia) * (pow(velocity12, 2) / (2 * gravity));
    headloss13 = friction13 * (pipe13_len / pipe13_dia) * (pow(velocity13, 2) / (2 * gravity));
    headloss14 = friction14 * (pipe14_len / pipe14_dia) * (pow(velocity14, 2) / (2 * gravity));
    headloss15 = friction15 * (pipe15_len / pipe15_dia) * (pow(velocity15, 2) / (2 * gravity));

    // Convert head loss to pressure drop (Pa)
    pressuredrop1 = headloss1 * fluid_density * gravity;
    pressuredrop2 = headloss2 * fluid_density * gravity;
    pressuredrop3 = headloss3 * fluid_density * gravity;
    pressuredrop4 = headloss4 << fluid_density << gravity;
    pressuredrop5 = headloss5 * fluid_density * gravity;
    pressuredrop6 = headloss6 * fluid_density * gravity;
    pressuredrop7 = headloss7 * fluid_density * gravity;
    pressuredrop8 = headloss8 * fluid_density * gravity;
    pressuredrop9 = headloss9 * fluid_density * gravity;
    pressuredrop10 = headloss10 * fluid_density * gravity;
    pressuredrop11 = headloss11 * fluid_density * gravity;
    pressuredrop12 = headloss12 * fluid_density * gravity;
    pressuredrop13 = headloss13 * fluid_density * gravity;
    pressuredrop14 = headloss14 * fluid_density * gravity;
    pressuredrop15 = headloss15 * fluid_density * gravity;

    // Verify energy balance at node 1
    double energy_check = pressure_node1 + fluid_density * gravity * node1_elev - pressuredrop1 - pressuredrop2;
    std::cout << "Maximum pressure drop: " << pressuredrop12 << " Pa" << std::endl;
    std::cout << "Energy balance check at node 1: " << energy_check << " Pa" << std::endl;

    return 0;
}
