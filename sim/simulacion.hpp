#include "../sim/block.hpp"
#include "../sim/calculos.hpp"
#include "../sim/constants.hpp"
#include "../sim/file.hpp"
#include "../sim/grid.hpp"
#include "../sim/progargs.hpp"

#include <fstream>
#include <iostream>
#include <vector>

#ifndef AC3_SIMULACION_HPP
  #define AC3_SIMULACION_HPP

namespace sim {
  //@param1: string con los argumentos
  int simulacion(std::vector<std::string> const & args_str);
}  // namespace entry
#endif  // AC3_SIMULACION_HPP
