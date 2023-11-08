//
// Created by marina on 30/09/23.
//

#include "block.hpp"
#include "constants.hpp"
#include "grid.hpp"

#include <cmath>
#include <numbers>
#include <vector>

#ifndef AC3_CALCULOS_HPP
  #define AC3_CALCULOS_HPP

using namespace std;

namespace fisica {
  // Función que calcula los operandos de las ecuaciones
  int calcular_operandos(double & masa, double & h, vector<double> & operandos);
  // Función que inicializa la densidad y la aceleración de las partículas (Paso 4.3.2.1)
  int inicializar_dens_acelera(struct Particula & part, int const & id_p);
  // Función que incrementa las densidades (Paso 4.3.2.2)
  void incremento_densidades(struct Particula & part, double const & operandos, int const & id_i,
                             int const & id_j, double & diferencia); //REFACTORIZAR
  // Función que realiza una transformación de las densidades (Paso 4.3.2.3)
  double trans_densidad(double & incremento, double & operando_1, double & operando_2);
  // Función que realiza la transferencia de aceleración (Paso 4.3.2.4)
  void trans_acele(struct Particula & part, vector<int> const & id_p, vector<double> & operandos,
                   double & h, double & diferencia);//REFACTORUZAE
  // Función que realiza la actualización de la vel, pos y hv (Paso 4.3.4)
  int mov_part(struct Particula & part, int const & id_p);
  // Funciones vectoriales que realizan la colisión entre partículas (Paso 4.3.3)
  int col_x(struct Particula & part, int const & id_p);
  int col_y(struct Particula & part, int const & id_p);
  int col_z(struct Particula & part, int const & id_p);
  // Funciones vectoriales que realizan la colisión entre partículas (Paso 4.3.5)
  int int_x(struct Particula & part, int const & id_p);
  int int_y(struct Particula & part, int const & id_p);
  int int_z(struct Particula & part, int const & id_p);
  // Función que llama a mov_part, col_x, col_y y col_z
  int col_mov(struct Particula & part, vector<int> const & num_bloques, int const & id_p);
  // Función grande que llama int_x, int_y e int_z
  int interaccion(Particula & part, vector<int> const & num_bloques, int const & id_p);
  // Main loop, se encarga de aplicar las funciones del procesamiento de la simulación (Paso 4.3)
  int main_loop(struct Particula & particula, struct Enclosure3D & malla,
                struct Constantes & constantes, vector<struct bloque::Bloque> & bloques);
}  // namespace fisica

#endif  // AC3_CALCULOS_HPP
