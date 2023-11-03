//
// Created by marina on 27/09/23.
//

#include <iostream>
#include <fstream>
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

int main(int argc, char **argv){
  const span args{argv, static_cast<size_t>(argc)};
  const std::vector<std::string> args_str{args.begin() +1, args.end()};
  return simulacion(args_str);
}

// NOLINTBEGIN
// NOLINTEND