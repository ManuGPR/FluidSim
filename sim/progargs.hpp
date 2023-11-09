#include "vector"

#include <fstream>
#include <iostream>

#ifndef ARQUITECTURA_PROGARGS_HPP
  #define ARQUITECTURA_PROGARGS_HPP

namespace entry {
  //@param1: vector de strings con los argumentos
  int check_args(std::vector<std::string> const & arguments);
  //@param1: string con nts
  int check_nts(std::string const & arguments);
  //@param1: string con el nombre del fichero de entrada
  int check_inputfile(std::string const & arguments);
  //@param1: string con el nombre del fichero de salida
  int check_outputfile(std::string const & arguments);
  //@param1: número de partículas
  int check_np(int np);
  //@param1: string con los argumentos
  int check_param(std::vector<std::string> const & arguments);
}  // namespace entry

#endif  // ARQUITECTURA_PROGARGS_HPP