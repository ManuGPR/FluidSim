//
// Created by marina on 27/09/23.
//
#include "grid.hpp"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#ifndef ARQUITECTURA_BLOCK_HPP
  #define ARQUITECTURA_BLOCK_HPP

using namespace std;

namespace bloque {
  // Función que calcula el número de bloques
  int num_bloques(vector<int> & num_bloques, double & h);
  // Funcion que calcula el tamaño de bloques
  int tam_bloques(vector<double> & tam_bloques, vector<int> & num_bloques);
  // Funciones que calculan las posiciones de las particulas en cada eje
  int loc_particula_x(int loc, double & pos, double & tam_bloques, int num_bloque);
  int loc_particula_y(int loc, double & pos, double & tam_bloques, int num_bloque);
  int loc_particula_z(int loc, double & pos, double & tam_bloques, int num_bloque);
  // Función que localiza todas las partículas
  int loc_particula_bucle(struct Particula & particulas, struct Enclosure3D & malla,
                          vector<int> & num_bloques, vector<struct Bloque> & bloques);
  // Función auxiliar que devuelve el total de bloques
  int total_bloques(vector<int> & num_bloques);
  // Función que crea los bloques
  int crear_bloques(vector<struct Bloque> & bloques, int total_bloques, vector<int> & num_bloques);
  // Función que crea la struct auxiliar
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