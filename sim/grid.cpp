//
// Created by marina on 27/09/23.
//

#include "grid.hpp"

//NOTA; quizás se pueden meter vectores en los parámetros para evitar hacer tres funciones por eje
namespace malla {
    int particula_contigua(struct Particula part, int id_i, int id_j){
        int suma_x = abs(part.loc_x[id_i] - part.loc_x[id_j]);
        if (suma_x > 1){return 0;}
        int suma_y = abs(part.loc_y[id_i] - part.loc_y[id_j]);
        if (suma_y > 1){return 0;}
        int suma_z = abs(part.loc_z[id_i] - part.loc_z[id_j]);
        if (suma_z > 1){return 0;}
        return 1;
    }
}