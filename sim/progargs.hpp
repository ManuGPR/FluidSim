//
// Created by marina on 27/09/23.
//
#include "vector"

#include <fstream>
#include <iostream>

#ifndef ARQUITECTURA_PROGARGS_HPP
  #define ARQUITECTURA_PROGARGS_HPP

namespace entry {
  // Función que checkea los argumentos de entrda
  int check_args(std::vector<std::string> const & arguments);
  // Funciṕn que checkea el número de pasos de tiempo
  int check_nts(std::string const & arguments);
  // Función que checkea el fichero de entrada
  int check_inputfile(std::string const & arguments);
  // Función que checkea el fichero de salida
  int check_outputfile(std::string const & arguments);
  // Función que checkea el número de partículas del fichero
  int check_np(int np);

  // Función de checkeo maestra, que llama al resto de funciones
  int check_param(std::vector<std::string> const & arguments);
}  // namespace entry

#endif  // ARQUITECTURA_PROGARGS_HPP