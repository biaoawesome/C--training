#include <iostream>
#include <cmath>

// Transient voltage analysis in a 15-stage RC ladder network
// Calculates voltage decay at each node over time

int main() {
    // Resistor values in ohms (15 variables)
    double R1 = 1000.0, R2 = 1500.0, R3 = 1200.0, R4 = 1800.0, R5 = 900.0;
    double R6 = 1600.0, R7 = 1100.0, R8 = 1400.0, R9 = 1300.0, R10 = 1700.0;
    double R11 = 950.0, R12 = 1450.0, R13 = 1250.0, R14 = 1550.0, R15 = 1050.0;

    // Capacitor values in farads (15 variables)
    double C1 = 1e-6, C2 = 1.5e-6, C3 = 0.8e-6, C4 = 2.2e-6, C5 = 1.2e-6;
    double C6 = 1.8e-6, C7 = 0.9e-6, C8 = 1.6e-6, C9 = 1.1e-6, C10 = 2.0e-6;
    double C11 = 0.7e-6, C12 = 1.4e-6, C13 = 1.3e-6, C14 = 1.7e-6, C15 = 0.6e-6;

    // Initial voltages in volts (16 variables including source)
    double V_source = 12.0, V1_0 = 0.0, V2_0 = 0.0, V3_0 = 0.0, V4_0 = 0.0;
    double V5_0 = 0.0, V6_0 = 0.0, V7_0 = 0.0, V8_0 = 0.0, V9_0 = 0.0;
    double V10_0 = 0.0, V11_0 = 0.0, V12_0 = 0.0, V13_0 = 0.0, V14_0 = 0.0;
    double V15_0 = 0.0;

    // Time parameters (6 variables)
    double time_total = 0.05; // 50ms simulation
    double time_step = 0.0001; // 100us steps
    double current_time = 0.0;
    int num_steps = static_cast<int>(time_total / time_step);

    // Node voltages at current time (16 variables)
    double V1_t, V2_t, V3_t, V4_t, V5_t, V6_t, V7_t, V8_t;
    double V9_t, V10_t, V11_t, V12_t, V13_t, V14_t, V15_t;

    // Currents through resistors (15 variables)
    double I_R1, I_R2, I_R3, I_R4, I_R5, I_R6, I_R7, I_R8;
    double I_R9, I_R10, I_R11, I_R12, I_R13, I_R14, I_R15;

    // Capacitor currents (15 variables)
    double I_C1, I_C2, I_C3, I_C4, I_C5, I_C6, I_C7, I_C8;
    double I_C9, I_C10, I_C11, I_C12, I_C13, I_C14, I_C15;

    // Node time constants (15 variables)
    double tau1, tau2, tau3, tau4, tau5, tau6, tau7, tau8;
    double tau9, tau10, tau11, tau12, tau13, tau14, tau15;

    // Steady-state voltages (15 variables)
    double V1_ss, V2_ss, V3_ss, V4_ss, V5_ss, V6_ss, V7_ss, V8_ss;
    double V9_ss, V10_ss, V11_ss, V12_ss, V13_ss, V14_ss, V15_ss;

    // Energy stored in capacitors (15 variables)
    double E1, E2, E3, E4, E5, E6, E7, E8, E9, E10;
    double E11, E12, E13, E14, E15;

    // Calculate time constants for each node
    tau1 = R1 * C1;
    tau2 = R2 * C2;
    tau3 = R3 * C3;
    tau4 = R4 * C4;
    tau5 = R5 * C5;
    tau6 = R6 * C6;
    tau7 = R7 * C7;
    tau8 = R8 * C8;
    tau9 = R9 * C9;
    tau10 = R10 * C10;
    tau11 = R11 * C11;
    tau12 = R12 * C12;
    tau13 = R13 * C13;
    tau14 = R14 * C14;
    tau15 = R15 * C15;

    // Calculate steady-state voltages (voltage divider chain)
    double total_R = R1 + R2 + R3 + R4 + R5 + R6 + R7 + R8 + R9 + R10 + R11 + R12 + R13 + R14 + R15;
    V1_ss = V_source * (total_R - R1) / total_R;
    V2_ss = V1_ss * (total_R - R1 - R2) / (total_R - R1);
    V3_ss = V2_ss * (total_R - R1 - R2 - R3) / (total_R - R1 - R2);
    V4_ss = V3_ss * (total_R - R1 - R2 - R3 - R4) / (total_R - R1 - R2 - R3);
    V5_ss = V4_ss * (total_R - R1 - R2 - R3 - R4 - R5) / (total_R - R1 - R2 - R3 - R4);
    V6_ss = V5_ss * (total_R - R1 - R2 - R3 - R4 - R5 - R6) / (total_R - R1 - R2 - R3 - R4 - R5);
    V7_ss = V6_ss * (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7) / (total_R - R1 - R2 - R3 - R4 - R5 - R6);
    V8_ss = V7_ss * (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8) / (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7);
    V9_ss = V8_ss * (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8 - R9) / (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8);
    V10_ss = V9_ss * (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8 - R9 - R10) / (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8 - R9);
    V11_ss = V10_ss * (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8 - R9 - R10 - R11) / (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8 - R9 - R10);
    V12_ss = V11_ss * (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8 - R9 - R10 - R11 - R12) / (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8 - R9 - R10 - R11);
    V13_ss = V12_ss * (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8 - R9 - R10 - R11 - R12 - R13) / (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8 - R9 - R10 - R11 - R12);
    V14_ss = V13_ss * (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8 - R9 - R10 - R11 - R12 - R13 - R14) / (total_R - R1 - R2 - R3 - R4 - R5 - R6 - R7 - R8 - R9 - R10 - R11 - R12 - R13);
    V15_ss = 0.0; // Ground reference

    // Simulate transient response at final time step (simplified)
    V1_t = V1_ss * (1 - exp(-time_total / tau1));
    V2_t = V2_ss * (1 - exp(-time_total / tau2));
    V3_t = V3_ss * (1 - exp(-time_total / tau3));
    V4_t = V4_ss * (1 - exp(-time_total / tau4));
    V5_t = V5_ss * (1 - exp(-time_total / tau5));
    V6_t = V6_ss * (1 - exp(-time_total / tau6));
    V7_t = V7_ss * (1 - exp(-time_total / tau7));
    V8_t = V8_ss * (1 - exp(-time_total / tau8));
    V9_t = V9_ss * (1 - exp(-time_total / tau9));
    V10_t = V10_ss * (1 - exp(-time_total / tau10));
    V11_t = V11_ss * (1 - exp(-time_total / tau11));
    V12_t = V12_ss * (1 - exp(-time_total / tau12));
    V13_t = V13_ss * (1 - exp(-time_total / tau13));
    V14_t = V14_ss * (1 - exp(-time_total / tau14));
    V15_t = 0.0;

    // Calculate currents at final state
    I_R1 = (V_source - V1_t) / R1;
    I_R2 = (V1_t - V2_t) / R2;
    I_R3 = (V2_t - V3_t) / R3;
    I_R4 = (V3_t - V4_t) / R4;
    I_R5 = (V4_t - V5_t) / R5;
    I_R6 = (V5_t - V6_t) / R6;
    I_R7 = (V6_t - V7_t) / R7;
    I_R8 = (V7_t - V8_t) / R8;
    I_R9 = (V8_t - V9_t) / R9;
    I_R10 = (V9_t - V10_t) / R10;
    I_R11 = (V10_t - V11_t) / R11;
    I_R12 = (V11_t - V12_t) / R12;
    I_R13 = (V12_t - V13_t) / R13;
    I_R14 = (V13_t - V14_t) / R14;
    I_R15 = (V14_t - V15_t) / R15;

    // Capacitor currents (steady state should be zero)
    I_C1 = 0.0; I_C2 = 0.0; I_C3 = 0.0; I_C4 = 0.0; I_C5 = 0.0;
    I_C6 = 0.0; I_C7 = 0.0; I_C8 = 0.0; I_C9 = 0.0; I_C10 = 0.0;
    I_C11 = 0.0; I_C12 = 0.0; I_C13 = 0.0; I_C14 = 0.0; I_C15 = 0.0;

    // Calculate energy stored in capacitors at final state
    E1 = 0.5 * C1 * pow(V1_t, 2);
    E2 = 0.5 * C2 * pow(V2_t, 2);
    E3 = 0.5 * C3 * pow(V3_t, 2);
    E4 = 0.5 * C4 * pow(V4_t, 2);
    E5 = 0.5 * C5 * pow(V5_t, 2);
    E6 = 0.5 * C6 * pow(V6_t, 2);
    E7 = 0.5 * C7 * pow(V7_t, 2);
    E8 = 0.5 * C8 * pow(V8_t, 2);
    E9 = 0.5 * C9 * pow(V9_t, 2);
    E10 = 0.5 * C10 * pow(V10_t, 2);
    E11 = 0.5 * C11 * pow(V11_t, 2);
    E12 = 0.5 * C12 * pow(V12_t, 2);
    E13 = 0.5 * C13 * pow(V13_t, 2);
    E14 = 0.5 * C14 * pow(V14_t, 2);
    E15 = 0.5 * C15 * pow(V15_t, 2);

    double total_energy = E1 + E2 + E3 + E4 + E5 + E6 + E7 + E8 + E9 + E10 + E11 + E12 + E13 + E14 + E15;

    // Output results
    std::cout << "Node 1 Voltage: " << V1_t << " V" << std::endl;
    std::cout << "Node 8 Voltage: " << V8_t << " V" << std::endl;
    std::cout << "Current through R1: " << I_R1 * 1000 << " mA" << std::endl;
    std::cout << "Time constant 1: " << tau1 * 1000 << " ms" << std::endl;
    std::cout << "Total Stored Energy: " << total_energy * 1000 << " mJ" << std::endl;

    return 0;
}
