// Multi-Degree-of-Freedom Spring-Mass-Damper System
// Calculates dynamic response of a 5-mass system under harmonic excitation
// Application: Mechanical vibration analysis

#include <iostream>
#include <cmath>

#define MASS 10.0     // kg
#define STIFFNESS 4000.0  // N/m
#define DAMPING_RATIO 0.05

int main() {
    // System parameters - 5 masses
    double m1 = MASS, m2 = MASS, m3 = MASS, m4 = MASS, m5 = MASS;
    
    // Spring constants - 6 springs (including ground)
    double k1 = STIFFNESS, k2 = STIFFNESS, k3 = STIFFNESS;
    double k4 = STIFFNESS, k5 = STIFFNESS, k6 = STIFFNESS;
    
    // Damping coefficients (proportional to critical damping)
    double zeta1 = DAMPING_RATIO, zeta2 = DAMPING_RATIO, zeta3 = DAMPING_RATIO;
    double zeta4 = DAMPING_RATIO, zeta5 = DAMPING_RATIO, zeta6 = DAMPING_RATIO;
    
    // Calculate damping coefficients c = 2*zeta*sqrt(k*m)
    double c1 = 2.0 * zeta1 * sqrt(k1 * m1);
    double c2 = 2.0 * zeta2 * sqrt(k2 * m2);
    double c3 = 2.0 * zeta3 * sqrt(k3 * m3);
    double c4 = 2.0 * zeta4 * sqrt(k4 * m4);
    double c5 = 2.0 * zeta5 * sqrt(k5 * m5);
    double c6 = 2.0 * zeta6 * sqrt(k6 * 5.0*MASS);  // Ground connection
    
    // Mass matrix (diagonal)
    double M11 = m1, M22 = m2, M33 = m3, M44 = m4, M55 = m5;
    double M12 = 0.0, M13 = 0.0, M14 = 0.0, M15 = 0.0;
    double M21 = 0.0, M23 = 0.0, M24 = 0.0, M25 = 0.0;
    double M31 = 0.0, M32 = 0.0, M34 = 0.0, M35 = 0.0;
    double M41 = 0.0, M42 = 0.0, M43 = 0.0, M45 = 0.0;
    double M51 = 0.0, M52 = 0.0, M53 = 0.0, M54 = 0.0;
    
    // Stiffness matrix - symmetric
    double K11 = k1 + k2, K12 = -k2, K13 = 0.0, K14 = 0.0, K15 = 0.0;
    double K22 = k2 + k3, K23 = -k3, K24 = 0.0, K25 = 0.0;
    double K33 = k3 + k4, K34 = -k4, K35 = 0.0;
    double K44 = k4 + k5, K45 = -k5;
    double K55 = k5 + k6;
    
    // Make symmetric
    double K21 = K12, K31 = K13, K32 = K23, K41 = K14, K42 = K24, K43 = K34;
    double K51 = K15, K52 = K25, K53 = K35, K54 = K45;
    
    // Damping matrix (proportional damping: C = alpha*M + beta*K)
    double alpha = 0.1, beta = 0.001;
    double C11 = alpha*M11 + beta*K11, C12 = beta*K12, C13 = 0.0, C14 = 0.0, C15 = 0.0;
    double C22 = alpha*M22 + beta*K22, C23 = beta*K23, C24 = 0.0, C25 = 0.0;
    double C33 = alpha*M33 + beta*K33, C34 = beta*K34, C35 = 0.0;
    double C44 = alpha*M44 + beta*K44, C45 = beta*K45;
    double C55 = alpha*M55 + beta*K55;
    
    // Make symmetric
    double C21 = C12, C31 = C13, C32 = C23, C41 = C14, C42 = C24, C43 = C34;
    double C51 = C15, C52 = C25, C53 = C35, C54 = C45;
    
    // External harmonic forces at frequency omega
    double omega = 25.0;  // rad/s - forcing frequency
    double F0 = 100.0;    // N - force amplitude
    
    // Force vector (harmonic excitation on mass 3)
    double F1_real = 0.0, F1_imag = 0.0;
    double F2_real = 0.0, F2_imag = 0.0;
    double F3_real = F0, F3_imag = 0.0;
    double F4_real = 0.0, F4_imag = 0.0;
    double F5_real = 0.0, F5_imag = 0.0;
    
    // Dynamic stiffness matrix: Z = K - omega^2*M + i*omega*C
    double omega_sq = omega * omega;
    
    // Real part of Z
    double Z11_real = K11 - omega_sq*M11, Z12_real = K12, Z13_real = K13, Z14_real = K14, Z15_real = K15;
    double Z22_real = K22 - omega_sq*M22, Z23_real = K23, Z24_real = K24, Z25_real = K25;
    double Z33_real = K33 - omega_sq*M33, Z34_real = K34, Z35_real = K35;
    double Z44_real = K44 - omega_sq*M44, Z45_real = K45;
    double Z55_real = K55 - omega_sq*M55;
    
    // Make symmetric
    double Z21_real = Z12_real, Z31_real = Z13_real, Z32_real = Z23_real;
    double Z41_real = Z14_real, Z42_real = Z24_real, Z43_real = Z34_real;
    double Z51_real = Z15_real, Z52_real = Z25_real, Z53_real = Z35_real, Z54_real = Z45_real;
    
    // Imaginary part of Z
    double Z11_imag = omega*C11, Z12_imag = omega*C12, Z13_imag = omega*C13, Z14_imag = omega*C14, Z15_imag = omega*C15;
    double Z22_imag = omega*C22, Z23_imag = omega*C23, Z24_imag = omega*C24, Z25_imag = omega*C25;
    double Z33_imag = omega*C33, Z34_imag = omega*C34, Z35_imag = omega*C35;
    double Z44_imag = omega*C44, Z45_imag = omega*C45;
    double Z55_imag = omega*C55;
    
    // Make symmetric
    double Z21_imag = Z12_imag, Z31_imag = Z13_imag, Z32_imag = Z23_imag;
    double Z41_imag = Z14_imag, Z42_imag = Z24_imag, Z43_imag = Z34_imag;
    double Z51_imag = Z15_imag, Z52_imag = Z25_imag, Z53_imag = Z35_imag, Z54_imag = Z45_imag;
    
    // Solve using simplified approach (neglecting off-diagonal coupling for demonstration)
    // In practice, this would require complex matrix inversion
    
    // Approximate solution: decoupled system
    double H11 = Z11_real*Z11_real + Z11_imag*Z11_imag;
    double H22 = Z22_real*Z22_real + Z22_imag*Z22_imag;
    double H33 = Z33_real*Z33_real + Z33_imag*Z33_imag;
    double H44 = Z44_real*Z44_real + Z44_imag*Z44_imag;
    double H55 = Z55_real*Z55_real + Z55_imag*Z55_imag;
    
    // Displacement amplitudes (real and imaginary parts)
    double X1_real = (F1_real*Z11_real + F1_imag*Z11_imag) / H11;
    double X1_imag = (F1_imag*Z11_real - F1_real*Z11_imag) / H11;
    
    double X2_real = (F2_real*Z22_real + F2_imag*Z22_imag) / H22;
    double X2_imag = (F2_imag*Z22_real - F2_real*Z22_imag) / H22;
    
    double X3_real = (F3_real*Z33_real + F3_imag*Z33_imag) / H33;
    double X3_imag = (F3_imag*Z33_real - F3_real*Z33_imag) / H33;
    
    double X4_real = (F4_real*Z44_real + F4_imag*Z44_imag) / H44;
    double X4_imag = (F4_imag*Z44_real - F4_real*Z44_imag) / H44;
    
    double X5_real = (F5_real*Z55_real + F5_imag*Z55_imag) / H55;
    double X5_imag = (F5_imag*Z55_real - F5_real*Z55_imag) / H55;
    
    // Magnitude and phase of displacements
    double X1_mag = sqrt(X1_real*X1_real + X1_imag*X1_imag);
    double X1_phase = atan2(X1_imag, X1_real) * 180.0 / M_PI;
    
    double X2_mag = sqrt(X2_real*X2_real + X2_imag*X2_imag);
    double X2_phase = atan2(X2_imag, X2_real) * 180.0 / M_PI;
    
    double X3_mag = sqrt(X3_real*X3_real + X3_imag*X3_imag);
    double X3_phase = atan2(X3_imag, X3_real) * 180.0 / M_PI;
    
    double X4_mag = sqrt(X4_real*X4_real + X4_imag*X4_imag);
    double X4_phase = atan2(X4_imag, X4_real) * 180.0 / M_PI;
    
    double X5_mag = sqrt(X5_real*X5_real + X5_imag*X5_imag);
    double X5_phase = atan2(X5_imag, X5_real) * 180.0 / M_PI;
    
    // Spring forces
    double spring1_force = k1 * X1_mag;
    double spring2_force = k2 * (X2_mag - X1_mag);
    double spring3_force = k3 * (X3_mag - X2_mag);
    double spring4_force = k4 * (X4_mag - X3_mag);
    double spring5_force = k5 * (X5_mag - X4_mag);
    double spring6_force = k6 * X5_mag;
    
    // Damping forces
    double damper1_force = c1 * omega * X1_mag;
    double damper2_force = c2 * omega * (X2_mag - X1_mag);
    double damper3_force = c3 * omega * (X3_mag - X2_mag);
    double damper4_force = c4 * omega * (X4_mag - X3_mag);
    double damper5_force = c5 * omega * (X5_mag - X4_mag);
    double damper6_force = c6 * omega * X5_mag;
    
    // Output results
    std::cout << "=== 5-DOF Spring-Mass-Damper System ===" << std::endl;
    std::cout << "Forcing Frequency: " << omega << " rad/s" << std::endl;
    std::cout << "Force Amplitude on Mass 3: " << F0 << " N" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Mass Displacements:" << std::endl;
    std::cout << "Mass 1 - Magnitude: " << X1_mag << " m, Phase: " << X1_phase << " deg" << std::endl;
    std::cout << "Mass 2 - Magnitude: " << X2_mag << " m, Phase: " << X2_phase << " deg" << std::endl;
    std::cout << "Mass 3 - Magnitude: " << X3_mag << " m, Phase: " << X3_phase << " deg" << std::endl;
    std::cout << "Mass 4 - Magnitude: " << X4_mag << " m, Phase: " << X4_phase << " deg" << std::endl;
    std::cout << "Mass 5 - Magnitude: " << X5_mag << " m, Phase: " << X5_phase << " deg" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Spring Forces:" << std::endl;
    std::cout << "Spring 1: " << spring1_force << " N" << std::endl;
    std::cout << "Spring 2: " << spring2_force << " N" << std::endl;
    std::cout << "Spring 3: " << spring3_force << " N" << std::endl;
    std::cout << "Spring 4: " << spring4_force << " N" << std::endl;
    std::cout << "Spring 5: " << spring5_force << " N" << std::endl;
    std::cout << "Spring 6: " << spring6_force << " N" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Damping Forces:" << std::endl;
    std::cout << "Damper 1: " << damper1_force << " N" << std::endl;
    std::cout << "Damper 2: " << damper2_force << " N" << std::endl;
    std::cout << "Damper 3: " << damper3_force << " N" << std::endl;
    std::cout << "Damper 4: " << damper4_force << " N" << std::endl;
    std::cout << "Damper 5: " << damper5_force << " N" << std::endl;
    std::cout << "Damper 6: " << damper6_force << " N" << std::endl;
    
    return 0;
}
