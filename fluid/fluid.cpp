//
// Created by marina on 27/09/23.
//

#include <iostream>
#include <vector>
#include <span>
#include "../sim/constants.hpp"
#include "../sim/progargs.hpp"
#include "../sim/grid.hpp"
#include "../sim/file.hpp"
#include "../sim/block.hpp"
#include "../sim/calculos.hpp"
#include "../sim/simulacion.cpp"

using namespace std;

//Función main que llama a la simulación
int main(int argc, char **argv){
  const span args{argv, static_cast<size_t>(argc)}; //Vista sobre argumentos
  const std::vector<std::string> args_str{args.begin() +1, args.end()}; //Vector strings
  return simulacion(args_str); // Llamada a la simulación
}

// NOLINTBEGIN
// NOLINTEND