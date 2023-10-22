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

const std::vector<double> acel_ex = {0.0, -9.8, 0.0};
const std::vector<double> limite_sup_recinto = {0.065, 0.1, 0.065};
const std::vector<double> limite_inf_recinto = {-0.065, -0.08, -0.065};


#endif //AC3_CONSTANTS_HPP
