//
// Created by marina on 27/09/23.
//

#include <vector>

#ifndef ARQUITECTURA_GRID_HPP
#define ARQUITECTURA_GRID_HPP

using namespace std;

namespace malla {
    int num_bloques (vector<double> lim_sup, vector<double> lim_inf, double h, vector<int> result);
    int tam_bloques (vector<double> lim_sup, vector<double> lim_inf, vector<int> num_bloques, vector<double> result);
    int pos_particula_x (double pos_x, double xmin, double tam_bloque_x);
    int pos_particula_y (double pos_y, double ymin, double tam_bloque_y);
    int pos_particula_z (double pos_z, double zmin, double tam_bloque_z);
}

class grid {

};


#endif //ARQUITECTURA_GRID_HPP
