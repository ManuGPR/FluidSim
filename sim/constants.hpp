#include <cmath>
#include <numbers>
#include <vector>

#ifndef AC3_CONSTANTS_HPP
  #define AC3_CONSTANTS_HPP

// Constantes de la simulación
constexpr double radio              = 1.695;
constexpr int densidad_de_fluido    = 1000;
constexpr double presion_de_rigidez = 3.0;
constexpr int s_c                   = 30000;
constexpr double d_v                = 128.0;
constexpr double viscosidad         = 0.4;
constexpr double tamano_particulas  = 2e-4;
constexpr double paso_tiempo        = 1e-3;
constexpr double distancia_minima   = 1e-10;

// Constantes vectoriales de la simulación
constexpr double lim_inf_x = -0.065, lim_sup_x = 0.065;
constexpr double lim_inf_y = -0.08, lim_sup_y = 0.1;
constexpr double lim_inf_z = -0.065, lim_sup_z = 0.065;
constexpr double gravedad_x = 0.0, gravedad_y = -9.8, gravedad_z = 0.0;

// Constantes para evitar el error del magic_number de clang_tidy
constexpr double cubo = 3.0;

// Estructura que define las constantes
struct Constantes {
    // Constantes de la simulación
    std::vector<double> operandos;
    double h    = 0.0;
    double masa = 0.0;
    int nts     = 0;

    explicit Constantes(int num_time_steps, double ppm)
      : h(radio / ppm), masa((densidad_de_fluido) / (pow(ppm, cubo))), nts(num_time_steps) { }
};

#endif  // AC3_CONSTANTS_HPP