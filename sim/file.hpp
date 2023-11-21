#include "block.hpp"
#include "constants.hpp"
#include "grid.hpp"
#include "progargs.hpp"

#include <filesystem>
#include <cstring>
#include <fstream>
#include <tuple>
#include <typeinfo>

#ifndef AC3_FILE_HPP
  #define AC3_FILE_HPP
using namespace std;

namespace ficheros {
  //@param1: fichero de entrada para leer
  tuple<int, double> lectura_cabecera(ifstream & file_in);
  //@param1: fichero que se lee
  double lectura_float_to_double(ifstream & fichero);
  //@param1: fichero de entrada, @param2: número de partículas, @param3: partículas
  int lectura_file(ifstream & file_in, int np, struct Particula & particulas);
  //@param1: fichero de salida de la simulación, @param2: partículas, @param3: partículas por metro
  //@param4: número de partículas
  int escritura_salida(ofstream & file_out, const struct Particula & particulas, double & ppm, int np);
  //@param1: parametro a castear a char*
  char const * to_str(int & parameter);
  //@param1: parametro a castear a char*
  char const * to_str(float & parameter);
  //FUNCIONES PARA LOS TEST
  //@param1: fichero de entrada, @param2: fichero con el que corregir
  int comparar_ficheros(ifstream & file_in, ifstream & file_corect);
  vector<float> vector_creacion();
  void archivo_creacion();
  //@param1: número de partículas del fichero nuevo
  void archivo_creacion_entero(int nps_in) ;
}  // namespace ficheros

#endif  // AC3_FILE_HPP