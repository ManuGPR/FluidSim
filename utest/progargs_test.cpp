#include "sim/block.hpp"
#include "sim/calculos.hpp"
#include "sim/constants.hpp"
#include "sim/file.hpp"
#include "sim/grid.hpp"
#include "sim/simulacion.hpp"
#include "sim/progargs.hpp"
#include "gtest/gtest.h"

//Test para chequear que el numero de argumentos es correcto
TEST(check_args, 1){
  const vector<std::string> arguments = {"a", "b", "c"};
  const int resultado = entry::check_args(arguments);
  EXPECT_EQ(0,resultado);
}

//Test para chequear que el numero de argumentos es incorrecto (2 en lugar de 3)
TEST(check_args, 2){
  const vector<std::string> arguments = {"a", "b"};
  const int resultado = entry::check_args(arguments);
  EXPECT_EQ(-1,resultado);
}

//Test para chequear que el numero de argumentos es incorrecto (4 en lugar de 3)
TEST(check_args, 3){
  const vector<std::string> arguments = {"a", "b", "c", "d"};
  const int resultado = entry::check_args(arguments);
  EXPECT_EQ(-1,resultado);
}
