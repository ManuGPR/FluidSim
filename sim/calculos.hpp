#include "block.hpp"
#include "constants.hpp"
#include "grid.hpp"

#include <cmath>
#include <numbers>
#include <vector>

#ifndef AC3_CALCULOS_HPP
  #define AC3_CALCULOS_HPP

using namespace std;

namespace calc {
  //@param1: masa de la partícula, @param2: longitud de suavizado, @param3: vector de operandos
  int calcular_operandos(double & masa, double & h, vector<double> & operandos);
  //@param1: partículas, @param2: id de la partícula
  int inicializar_dens_acel(Particula & part, int id_p);
  //@param1: partículas, @param2: operando para el cálculo, @param3: id's de las partículas,
  //@param4:diferencia de las posiciones
  [[maybe_unused]] void incremento_densidades(Particula & part, double const & operandos,
                                              vector<int> const & id_i, double & diferencia);
  //@param1: incremento para la función, @param2: primero operando, @param3: segundo operando
  double trans_densidad(double & incremento, double & operando_1, double & operando_2);
  //@param1: partículas, @param2: id de las partículas, @param3: constantes, @param4: diferencias
  void trans_acele(Particula & part, vector<int> const & id_p, Constantes & constantes,
                   double const & diferencia);
  //@param1: particulas, @param2: id de la partícula
  int mov_part(Particula & part, int id_p);
  //@param1: particulas, @param2: id de la partícula
  int col_x(Particula & part, int id_p);
  int col_y(Particula & part, int id_p);
  int col_z(Particula & part, int id_p);
  //@param1: particulas, @param2: id de la partícula
  int int_x(Particula & part, int id_p);
  int int_y(Particula & part, int id_p);
  int int_z(Particula & part, int id_p);
  //@param1: particulas, @param2: número de bloques, @param3: id de la partícula
  int col_mov(Particula & part, vector<int> const & num_bloques, int id_p);
  //@param1: partículas, @param2: número de bloques, @param3: id de la partícula
  int interaccion(Particula & part, vector<int> const & num_bloques, int id_p);
  //@param1: partículas, @param2: malla, @param3: constantes, @param4: bloques
  int main_loop(Particula & particula, Enclosure3D & malla, Constantes & constantes,
                vector<block::Bloque> & bloques);
  //@param1: partículas, @param2: constantes, @param3: bloques, @param4: número de iteraciones
  int bucle_trans(Particula & particulas, Constantes & constantes, vector<block::Bloque> & bloques,
                  int it_bloque);
  //@param1: partículas, @param2: constantes, @param3: bloques, @param4: número de iteraciones
  int bucle_incremento_densidades(Particula & particulas, Constantes & constantes,
                                  vector<block::Bloque> & bloques, int it_bloque);
}  // namespace calc

#endif  // AC3_CALCULOS_HPP
