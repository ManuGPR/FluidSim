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

//Test para chequear que el numero de nts es correcto
TEST(check_nts, 1){
  const string arguments = "123";
  const int resultado = entry::check_nts(arguments);
  int const number_nts = stoi(arguments);
  EXPECT_EQ(number_nts,resultado);
}

//Test para chequear que el numero de nts es incorrecto (no es un numero)
TEST(check_nts, 2){
  const string arguments = "a23";
  const int resultado = entry::check_nts(arguments);
  EXPECT_EQ(-1,resultado);
}

//Test para chequear que el numero de nts es incorrecto (es un numero negativo)
TEST(check_nts, 3){
  const string arguments = "-123";
  const int resultado = entry::check_nts(arguments);
  EXPECT_EQ(-2,resultado);
}

//Test para chequear que el numero de particulas es correcto
TEST(check_np, 1){
  const int nps = 10;
  const int resultado = entry::check_np(nps);
  EXPECT_EQ(0,resultado);
}

//Test para chequear que el numero de particulas es incorrecto (es 0)
TEST(check_np, 2){
  const int nps = 0;
  const int resultado = entry::check_np(nps);
  EXPECT_EQ(-5,resultado);
}

//Test para chequear que el numero de particulas es incorrecto (es negativo)
TEST(check_np, 3){
  const int nps = -1;
  const int resultado = entry::check_np(nps);
  EXPECT_EQ(-5,resultado);
}

