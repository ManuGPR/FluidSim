//
// Created by marina on 30/09/23.
//

#include <vector>
#include "grid.hpp"

#ifndef AC3_CALCULOS_HPP
#define AC3_CALCULOS_HPP

using namespace std;

namespace fisica {
    int inicia_aceleracion (struct Particula part, int id_p, vector<double> aceleracion);
    int incremento_densidades(struct Particula part, vector<int> id_p, double h, double m);
    int trans_densidad(struct Particula part, int id_p, double h, double m);
    int trans_acele(struct Particula part, vector<int> id_p, double h, double m);
    int mov_part(struct Particula part, int id_p);
    int col_x(vector<double> particula, vector<double> malla);
    int col_y(vector<double> particula, vector<double> malla);
    int col_z(vector<double> particula, vector<double> malla);
    int int_x(vector<double> particula, vector<double> malla);
    int int_y(vector<double> particula, vector<double> malla);
    int int_z(vector<double> particula, vector<double> malla);
}

#endif //AC3_CALCULOS_HPP