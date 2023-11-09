#include "constants.hpp"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#ifndef ARQUITECTURA_GRID_HPP
  #define ARQUITECTURA_GRID_HPP

using namespace std;

// Estructura que define la malla
struct Enclosure3D {
    // Argumentos de la malla
    std::vector<int> num_bloques;
    std::vector<double> tam_bloques;
    int nps = 0;

    // Constructor de la malla
    explicit Enclosure3D(int nps) : nps(nps) { }
};

// Estrucura que define las partículas
struct Particula {
    // Argumentos de las partículas
    vector<double> pos_x;
    vector<double> pos_y;
    vector<double> pos_z;
    vector<double> hv_x;
    vector<double> hv_y;
    vector<double> hv_z;
    vector<double> vel_x;
    vector<double> vel_y;
    vector<double> vel_z;
    vector<double> acel_x;
    vector<double> acel_y;
    vector<double> acel_z;
    vector<double> dens;
    vector<int> loc_x;
    vector<int> loc_y;
    vector<int> loc_z;
    vector<int> bloque;
    // Constructor de la partícula
    explicit Particula(int np)
      : pos_x(np, 0.0), pos_y(np, 0.0), pos_z(np, 0.0), hv_x(np, 0.0), hv_y(np, 0.0), hv_z(np, 0.0),
        vel_x(np, 0.0), vel_y(np, 0.0), vel_z(np, 0.0), acel_x(np, gravedad_x),
        acel_y(np, gravedad_y), acel_z(np, gravedad_z), dens(np, 0.0), loc_x(np, 0), loc_y(np, 0),
        loc_z(np, 0), bloque(np, 0){};
};
#endif  // ARQUITECTURA_GRID_HPP