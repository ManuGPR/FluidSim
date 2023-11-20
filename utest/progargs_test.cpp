#include "gtest/gtest.h"
#include "sim/simulacion.hpp"


//No hay fallos
TEST(argumentos, 1){
  const vector<string> vec = {"1", "./small.fld","./out.fld"};
  const int resultado = sim::simulacion(vec);
  EXPECT_EQ(0,resultado);
}

//Número inválido de argumentos
TEST(argumentos, 2){
  const vector<string> vec = { "./small.fld","./out.fld"};
  const int resultado = sim::simulacion(vec);
  EXPECT_EQ(-1,resultado);
}

//El argumento de paso de parametros no es un número
TEST(argumentos, 3){
  const vector<string> vec = { "a","./small.fld","./out.fld"};
  const int resultado = sim::simulacion(vec);
  EXPECT_EQ(-1,resultado);
}

//El número de paso es negativo
TEST(argumentos, 4){
  const vector<string> vec = { "-1","./small.fld","./out.fld"};
  const int resultado = sim::simulacion(vec);
  EXPECT_EQ(-2,resultado);
}

//Error al abrir archivo de lectura
TEST(argumentos, 5){
  const vector<string> vec = { "1","./no_existe.fld","./out.fld"};
  const int resultado = sim::simulacion(vec);
  EXPECT_EQ(-3,resultado);
}

//Error al abrir archivo de salida
TEST(argumentos, 6){
  const vector<string> vec = { "1","./small.fld","../.+./out.fld"};
  const int resultado = sim::simulacion(vec);
  EXPECT_EQ(-4,resultado);
}

//Modificar el archivo de entrada para que el np sea negativo
TEST(argumentos, 7) {
  ficheros::archivo_creacion_entero(-1);
 const vector<string> vec = { "1", "prueba_escr.fld","./out.fld"};
 const int resultado = sim::simulacion(vec);
  EXPECT_EQ(-5,resultado);
}

//Modificar el archivo de entrada para que el np sea negativo
TEST(argumentos, 8) {
  ficheros::archivo_creacion_entero(0);
 const vector<string> vec = { "1", "prueba_escr.fld","./out.fld"};
 const int resultado = sim::simulacion(vec);
  EXPECT_EQ(-5,resultado);
}

//Modificar el archivo de entrada para que np no coincide y es mayor que el numero de particula
TEST(argumentos, 9) {
  ficheros::archivo_creacion_entero(3);
 const vector<string> vec = { "1", "prueba_escr.fld","./out.fld"};
 const int resultado = sim::simulacion(vec);
  EXPECT_EQ(-5,resultado);
}

//Modificar el archivo de entrada para que np no coincida y el numero de particulas es menor
TEST(argumentos, 10) {
  ficheros::archivo_creacion_entero(1);
 const vector<string> vec = { "1", "prueba_escr.fld","./out.fld"};
 const int resultado = sim::simulacion(vec);
  EXPECT_EQ(-5,resultado);
}

//El numero de paso de tiempo 0
TEST(argumentos, 11){
  const vector<string> vec = { "0","small.fld","./out.fld"};
  const int resultado = sim::simulacion(vec);
  EXPECT_EQ(-2,resultado);
}
