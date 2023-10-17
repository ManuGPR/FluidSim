//
// Created by marina on 30/09/23.
//

#include <vector>
#include <numbers>
#include <cmath>
#include "grid.hpp"
#include "constants.hpp"


#ifndef AC3_CALCULOS_HPP
#define AC3_CALCULOS_HPP

using namespace std;

namespace fisica {
    int calcular_operandos(double m, double h);
    int inicializar_dens_acelera(struct Particula & part, int id_p);
    void incremento_densidades(struct Particula & part, vector<int> id_p);
    double trans_densidad(double incremento);
    void trans_acele(struct Particula & part, vector<int> id_p, double h);
    int mov_part(struct Particula & part, int id_p);
    int col_x(struct Particula & part, vector<int> num_bloques, int id_p);
    int col_y(struct Particula & part, vector<int> num_bloques, int id_p);
    int col_z(struct Particula & part, vector<int> num_bloques, int id_p);
    int int_x(struct Particula & part, vector<int> num_bloques, int id_p);
    int int_y(struct Particula & part, vector<int> num_bloques, int id_p);
    int int_z(struct Particula & part, vector<int> num_bloques, int id_p);
    int col_mov(struct Particula & part, vector<int>const & num_bloques, int id_p);
    int interaccion(struct Particula & part, vector<int> const & num_bloques, int id_p);
}

#endif //AC3_CALCULOS_HPP