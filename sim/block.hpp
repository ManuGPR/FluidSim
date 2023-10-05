//
// Created by marina on 27/09/23.
//
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "grid.hpp"

#ifndef ARQUITECTURA_BLOCK_HPP
#define ARQUITECTURA_BLOCK_HPP

using namespace std;

namespace bloque {
    //Funcion que calcula el numero de bloques
    int num_bloques (vector<double> lim_sup, vector<double> lim_inf, double h, vector<int> & result);
    //Funcion que calcula el tamaño de bloques
    int tam_bloques (vector<double> lim_sup, vector<double> lim_inf, vector<int> num_bloques, vector<double> & result);
    //Funciones que calculan las posiciones de las particulas en cada eje
    int pos_particula_x (double pos_x, double xmin, double tam_bloque_x);
    int pos_particula_y (double pos_y, double ymin, double tam_bloque_y);
    int pos_particula_z (double pos_z, double zmin, double tam_bloque_z);
    //Función que localiza todas las partículas
    int loc_particula (struct Particula particula, int np, vector<double> lim_inferior, vector<double> tam_bloque);
    //int repos_particula()
}

#endif //ARQUITECTURA_BLOCK_HPP
