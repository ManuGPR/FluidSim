//
// Created by manu on 5/10/23.
//

#include "block.hpp"
#include "constants.hpp"
#include "grid.hpp"
#include "progargs.hpp"

#include <cstring>
#include <fstream>
#include <tuple>
#include <typeinfo>

#ifndef AC3_FILE_HPP
  #define AC3_FILE_HPP
using namespace std;

namespace ficheros {
  // Función que se encarga de leer la cabecera
  tuple<int, double> lectura_cabecera(ifstream & file_in);
  // Función que se encarga de leer un objeto del fichero, hacer el cast a double y devolverlo
  double lectura_float_to_double(ifstream & fichero);
  // Función que se encarga de leer el fichero
  int lectura_file(ifstream & file_in, int np, struct Particula & particulas);
  // Función que se encarga de la escritura del fichero de salida
  int escritura_salida(ofstream & file_out, const struct Particula & particulas, double & ppm,
                       int np);
  // Función que escribe un fichero de salida de comprobación
  int escritura_comp();
  // Función que castea un entero a un char*
  char const * to_str(int & parameter);
  // Función que castea un doble a un char*
  char const * to_str(float & parameter);
  int lectura_salida(ifstream & file_in, ifstream & file_corect);
  int modificar_fichero(string & file_name, int nps_mod);
  int trazas(ifstream & fichero_comp, Particula & particula);
}  // namespace ficheros

#endif  // AC3_FILE_HPP