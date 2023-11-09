#include "grid.hpp"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#ifndef ARQUITECTURA_BLOCK_HPP
  #define ARQUITECTURA_BLOCK_HPP

using namespace std;

namespace block {
  //@param1: número de bloques, @param2: longitud de suavizado
  int num_bloques(vector<int> & num_bloques, double & h);
  //@param1: tamaño de los bloques , @param2: número de bloques
  int tam_bloques(vector<double> & tam_bloques, vector<int> & num_bloques);
  //@param1: posición de la partícula, @param2: tamaño de los bloques, @param3: número de bloques
  int loc_particula_x(double & pos, double & tam_bloques, int num_bloque);
  int loc_particula_y(double & pos, double & tam_bloques, int num_bloque);
  int loc_particula_z(double & pos, double & tam_bloques, int num_bloque);
  //@param1: partículas, @param2: malla, @param3: número de bloques, @param4: bloques
  int loc_particula_bucle(struct Particula & particulas, struct Enclosure3D & malla,
                          vector<int> & num_bloques, vector<struct Bloque> & bloques);
  //@param1: número de bloques
  int total_bloques(vector<int> & num_bloques);
  //@param1: bloques, @param2: número total de bloques, @param3: número de bloques
  int crear_bloques(vector<struct Bloque> & bloques, int total_bloques, vector<int> & num_bloques);
  //@param1: número de bloques, @param2: estructura a
  int crear_auxiliar(vector<int> & num_bloques, struct Aux & auxiliar);

  // Estructura que define los bloques
  struct Bloque {
      /*class attributes*/
      vector<int> bloque_contiguo;
      vector<int> lista_particulas;
  };

  // Estrcutura que define una struct auxiliar
  struct Aux {
      /*class attributes*/
      vector<int> pos_x;
      vector<int> pos_y;
      vector<int> pos_z;
      /*class methods*/
      explicit Aux(int total_bloques)
        : pos_x(total_bloques), pos_y(total_bloques), pos_z(total_bloques){};
  };
}  // namespace bloque

#endif  // ARQUITECTURA_BLOCK_HPP