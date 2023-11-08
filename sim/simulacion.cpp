//
// Created by marina on 2/11/23
#include "../sim/block.hpp"
#include "../sim/calculos.hpp"
#include "../sim/constants.hpp"
#include "../sim/file.hpp"
#include "../sim/grid.hpp"
#include "../sim/progargs.hpp"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Función que se encarga de inicializar la simulación
int simulacion(std::vector<std::string> const & args_str) {
  int nps    = 0;  // Inicialización de parámetros
  double ppm = 0.0;
  ifstream file_in;
  ofstream file_out;
  int const nts = entry::check_param(args_str);  // Función de checkeo maestra
  if (nts < 0) { return nts; }                   // Si hay un error en la función se devuelve
  file_in.open(args_str[1], ios::binary);        // Apertura del fichero y cabecera
  tie(nps, ppm) = ficheros::lectura_cabecera(file_in);  // Guardas los valores de nps y ppm
  if (nps <= 0) { return nps; }  // Si hay un error en la lectura de la cabecera, lo devuelves
  struct Constantes constantes(nts, ppm);  // Creación de la malla y las constantes
  struct Enclosure3D malla(nps);
  fisica::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  bloque::num_bloques(malla.num_bloques, constantes.h);
  bloque::tam_bloques(malla.tam_bloques, malla.num_bloques);
  struct Particula particulas(nps);                  // Inicialización de las partículas
  ficheros::lectura_file(file_in, nps, particulas);  // Lectura del fichero
  int const total_bloques = bloque::total_bloques(malla.num_bloques);
  vector<struct bloque::Bloque> vector_bloques;  // Inicialización y creación de los bloques
  bloque::crear_bloques(vector_bloques, total_bloques, malla.num_bloques);
  fisica::main_loop(particulas, malla, constantes, vector_bloques);  // Llamada de main loop
  file_out.open(args_str[2], ios::binary); //Escritura del fichero de salida
  ficheros::escritura_salida(file_out, particulas, ppm, nps);
  return 0;
}