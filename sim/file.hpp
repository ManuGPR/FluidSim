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
  //@param1: fichero de entrada para leer
  tuple<int, double> lectura_cabecera(ifstream & file_in);
  //@param1: fichero que se lee
  double lectura_float_to_double(ifstream & fichero);
  //@param1: fichero de entrada, @param2: número de partículas, @param3: partículas
  int lectura_file(ifstream & file_in, int np, struct Particula & particulas);
  //@param1: fichero de salida de la simulación, @param2: partículas, @param3: partículas por metro
  //@param4: número de partículas
  int escritura_salida(ofstream & file_out, const struct Particula & particulas, double & ppm, int np);
  [[maybe_unused]] int escritura_comp();
  [[maybe_unused]] void loop_escritura_comp(long int & num_p, ifstream & fichero_comp, ofstream & fichero_comp_salida);
  //@param1: parametro a castear a char*
  char const * to_str(int & parameter);
  //@param1: parametro a castear a char*
  char const * to_str(float & parameter);
  //@param1: fichero de entrada, @param2: fichero con el que corregir
  int comparar_ficheros(ifstream & file_in, ifstream & file_corect);
  //@param1: string con el nombre del fichero que modificar, @param2: número por el que cambiar nps
  int modificar_fichero(string & file_name, int nps_mod);
  //@param1: fichero con el que comparar, @param2: partículas con las que comparar
  int trazas(ifstream & fichero_comp, Particula & particula);
  int read_pos_xyz (ifstream & fichero_comp, Particula & particulas);
  int read_hv_xyz (ifstream & fichero_comp, Particula & particulas);
  int read_vel_xyz (ifstream & fichero_comp, Particula & particulas);
  int read_acel_xyz (ifstream & fichero_comp, Particula & particulas);
  void vector_creacion(vector<float> &parametros);
  ifstream archivo_creacion();
  vector<double> comprobacion_lectura1(ifstream &fichero_comprobacion);
  int comprobacion_lectura2(ifstream &fichero_comprobacion);
}  // namespace ficheros

#endif  // AC3_FILE_HPP