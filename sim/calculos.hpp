//
// Created by marina on 30/09/23.
//

#include <vector>
#include <numbers>
#include <cmath>
#include "grid.hpp"
#include "constants.hpp"
#include "block.hpp"

#ifndef AC3_CALCULOS_HPP
  #define AC3_CALCULOS_HPP

using namespace std;

namespace fisica {
  int calcular_operandos(double & masa,double & h, vector<double> & operandos);
  int inicializar_dens_acelera(struct Particula & part, int id_p);
  void incremento_densidades(struct Particula & part, double & operandos, int id_i, int id_j);
  double trans_densidad(double & incremento, double & operando_1, double & operando_2);
  void trans_acele(struct Particula & part, const vector<int>  & id_p, vector<double> & operandos, double & h );
  int mov_part(struct Particula & part, int id_p);
  int col_x(struct Particula & part, int num_bloques, int id_p);
  int col_y(struct Particula & part, int num_bloques, int id_p);
  int col_z(struct Particula & part, int num_bloques, int id_p);
  int int_x(struct Particula & part, int num_bloques, int id_p);
  int int_y(struct Particula & part, int num_bloques, int id_p);
  int int_z(struct Particula & part, int num_bloques, int id_p);
  int col_mov(struct Particula & part, vector<int>const & num_bloques, int id_p);
  int interaccion(struct Particula & part, vector<int> const & num_bloques, int id_p);
  int main_loop(struct Particula & particula, struct Enclosure3D & malla, struct Constantes &constantes);
}

#endif //AC3_CALCULOS_HPP