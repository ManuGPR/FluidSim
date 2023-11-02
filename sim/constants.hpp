//
// Created by manu on 8/10/23.
//

#include <vector>
#include <numbers>
#include <cmath>

#ifndef AC3_CONSTANTS_HPP
  #define AC3_CONSTANTS_HPP

constexpr double RADIO = 1.695;
constexpr int DENSIDAD_DE_FLUIDO = 1000;
constexpr double PRESION_DE_RIGIDEZ = 3.0;
constexpr int S_C = 30000;
constexpr double D_V = 128.0;
constexpr double VISCOSIDAD = 0.4;
constexpr double TAMANO_PARTICULAS = 2e-4;
constexpr double PASO_TIEMPO = 1e-3;
constexpr double PI_CONST = std::numbers::pi;

constexpr double lim_inf_x = -0.065, lim_sup_x = 0.065;
constexpr double lim_inf_y = -0.08, lim_sup_y = 0.1;
constexpr double lim_inf_z = -0.065, lim_sup_z = 0.065;
constexpr double gravedad_x = 0.0, gravedad_y = -9.8, gravedad_z = 0.0;
constexpr double cubo = 3.0;

struct Constantes {
    std::vector<double> operandos;
    double h = 0.0;
    double masa = 0.0;
    double nts = 0.0;
    explicit Constantes(double num_time_steps,double ppm) : h(RADIO / ppm), masa((DENSIDAD_DE_FLUIDO) / (pow(ppm, cubo))), nts(num_time_steps) {}
    };

#endif //AC3_CONSTANTS_HPP