//
// Created by marina on 27/09/23.
//

#include <cmath>
#include "grid.hpp"

//NOTA; quizás se pueden meter vectores en los parámetros para evitar hacer tres funciones por eje

namespace malla {
    int num_bloques (vector<double> lim_sup, vector<double> lim_inf, double h, vector<int> result) {
        result[0] = floor((lim_sup[0] - lim_inf[0]) / h);
        result[1] = floor((lim_sup[1] - lim_inf[1]) / h);
        result[2] = floor((lim_sup[2] - lim_inf[2]) / h);
        return 0;
    }

    int tam_bloques (vector<double> lim_sup, vector<double> lim_inf, vector<int> num_bloques, vector<double> result){
        result[0] = (lim_sup[0] - lim_inf[0]) / num_bloques[0];
        result[1] = (lim_sup[1] - lim_inf[1]) / num_bloques[1];
        result[2] = (lim_sup[2] - lim_inf[2]) / num_bloques[2];
        return 0;
    }

    int pos_particula_x (double pos_x, double xmin, double tam_bloque_x) {
        return floor((pos_x - xmin) / tam_bloque_x);
    }
    int pos_particula_y(double pos_y, double ymin, double tam_bloque_y) {
        return floor((pos_y - ymin) / tam_bloque_y);
    }
    int pos_particula_z(double pos_z, double zmin, double tam_bloque_z) {
        return floor((pos_z - zmin) / tam_bloque_z);
    }
}