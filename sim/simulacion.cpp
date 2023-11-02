//
// Created by marina on 2/11/23
#include <iostream>
#include <fstream>
#include <vector>
#include "../sim/constants.hpp"
#include "../sim/progargs.hpp"
#include "../sim/grid.hpp"
#include "../sim/file.hpp"
#include "../sim/block.hpp"
#include "../sim/calculos.hpp"

using namespace std;

int simulation(const std::vector<std::string> & args_str) {
  int nps = 0; //nts = numero de pasos de tiempo, nps = numero de particulas
  double ppm = 0.0; //ppm = partículas por metro
  ifstream file_in; //file_in = fichero de entrada
  ofstream file_out; //file_out = fichero de salida
    const int nts = entry::check_param(args_str); //Función de checkeo maestra
  if (nts < 0) {return nts;}
  file_in.open(args_str[1], ios::binary);//Apertura del fichero y cabecera
  tie(nps, ppm) = ficheros::lectura_cabecera(file_in);
  struct Constantes constantes(nts, ppm);
  struct Enclosure3D malla(nps);
  fisica::calcular_operandos(constantes.masa,constantes.h,constantes.operandos);
  bloque::num_bloques(malla.num_bloques, constantes.h);
  bloque::tam_bloques(malla.tam_bloques,malla.num_bloques);
  struct Particula particulas(nps); //Inicialización de los objetos
  ficheros::lectura_file(file_in, nps, particulas); //Lectura del fichero
  fisica::main_loop(particulas, malla, constantes);
  file_out.open("out.fld", ios::binary);
  ficheros::escritura_salida(file_out, particulas, ppm, nps);
  return 0;
}