//
// Created by marina on 27/09/23.
//
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "grid.hpp"

#ifndef ARQUITECTURA_BLOCK_HPP
  #define ARQUITECTURA_BLOCK_HPP

using namespace std;

namespace bloque {
  int num_bloques (vector<int> &num_bloques, double & h);
  //Funcion que calcula el tamaño de bloques
  int tam_bloques (vector<double> &tam_bloques,vector<int> &num_bloques);
  //Funciones que calculan las posiciones de las particulas en cada eje
  int loc_particula_x( int loc, double &pos, double &tam_bloques, int num_bloque);
  int loc_particula_y( int loc, double &pos, double &tam_bloques, int num_bloque);
  int loc_particula_z( int loc, double &pos, double &tam_bloques, int num_bloque);
  //Función que localiza todas las partículas
  int loc_particula (struct Particula & particulas, int nps,vector<double> &tam_bloques, vector<int> &num_bloques, vector<struct Bloque> & bloques);
  int loc_bloque(struct Particula & particulas, vector<struct Bloque> & bloques, int nps, int num_bloques);
  //int repos_particula()
  int total_bloques(vector<int> & num_bloques);
  int crear_bloques(vector<struct Bloque> & bloques, int total_bloques, vector<int> & num_bloques);
  int crear_auxiliar(vector<int> & num_bloques, struct Aux & auxiliar);
  struct Bloque {
      /*class attributes*/
      vector<int> bloque_contiguo;
      vector<int> lista_particulas;
  };
  struct Aux {
      /*class attributes*/
      vector<int> pos_x;
      vector<int> pos_y;
      vector<int> pos_z;
      /*class methods*/
      explicit Aux(int total_bloques) : pos_x(total_bloques), pos_y(total_bloques),
          pos_z(total_bloques){};
  };
}

#endif //ARQUITECTURA_BLOCK_HPP