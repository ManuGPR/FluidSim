//
// Created by marina on 30/10/23.
//
#include "gtest/gtest.h"
#include "sim/calculos.hpp"
#include "sim/file.hpp"
#include "sim/simulacion.cpp"
#include "sim/block.hpp"
#include "sim/grid.hpp"
#include <fstream>

TEST(argumentos, uno){
  const vector<string> vec = {"1", "./small.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(0,resultado);
}

//Numero invalido de argumentos
TEST(argumentos, dos){
  const vector<string> vec = { "./small.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-1,resultado);
}

//El argumento de paso de parametros no es un numero
TEST(argumentos, tres){
  const vector<string> vec = { "a","./small.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-1,resultado);
}


//El numero de paso es negativo
TEST(argumentos, cuatro){
  const vector<string> vec = { "-1","./small.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-2,resultado);
}



//Error al abrir archivo de lectura
TEST(argumentos, cinco){
  const vector<string> vec = { "1","./ssmal.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-3,resultado);
}

//Error al abrir archivo de salida
TEST(argumentos, seis){
  const vector<string> vec = { "1","./small.fld","../.+./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-4,resultado);
}
/*
//Numero de particulas es zero
//Modificar el archivo de entrada
TEST(argumentos, ocho){
  ifstream file_in;
  file_in.open("./small.fld", ios::binary);
  ficheros::lectura_para_modificar_fichero(file_in,0);
  const vector<string> vec = { "1", "./small_modificado.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-5,resultado);
}

//Numero de particulas es negativo
//Modificar el archivo de entrada
TEST(argumentos, ocho){
  ifstream file_in;
  file_in.open("./small.fld", ios::binary);
  ficheros::lectura_para_modificar_fichero(file_in,-1);
  const vector<string> vec = { "1", "./small_modificado.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-5,resultado);
}


//Numero de particulas no coincide como el real
//Modificar el archivo de entrada
TEST(argumentos, nueve){
  ifstream file_in;
  file_in.open("./small.fld", ios::binary);
  ficheros::lectura_para_modificar_fichero(file_in,6);
  const vector<string> vec = { "1", "./small_modificado.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-5,resultado);
}
*/
//El numero de paso es 0
TEST(argumentos, diez){
  const vector<string> vec = { "0","../../small.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-2,resultado);
}

//Test correcto el archivo out.fld councide con la el el small-1.fld
TEST(argumentos, once){
  const vector<string> vec = {"1", "./small.fld","./out.fld"};
  simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("./out.fld", ios::binary);
  file_correct.open("./small-1.fld", ios::binary);
  const int resultado = ficheros::lectura_salida(file_in,file_correct);
  EXPECT_EQ(0,resultado);
}
//Test correcto el archivo out.fld councide con la el el small-1.fld
TEST(argumentos, doce){
  const vector<string> vec = {"2", "./small.fld","./out.fld"};
  simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("./out.fld", ios::binary);
  file_correct.open("./small-2.fld", ios::binary);
  const int resultado = ficheros::lectura_salida(file_in,file_correct);
  EXPECT_EQ(0,resultado);
}

//Test correcto el archivo out.fld councide con la el el small-5.fld
TEST(argumentos, trece){
  const vector<string> vec = {"3", "./small.fld","./out.fld"};
  simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("./out.fld", ios::binary);
  file_correct.open("./small-3.fld", ios::binary);
  const int resultado = ficheros::lectura_salida(file_in,file_correct);
  EXPECT_EQ(0,resultado);
}

TEST(trazas,uno){
  const vector<string> vec = {"1", "./small.fld","./out.fld"};
  simulacion(vec);
  ifstream file_in;
  struct Particula particula(4800);
  file_in.open("boundint-base-1.trz", ios::binary);
  const int resultado = ficheros::trazas(file_in,particula);
  EXPECT_EQ(0,resultado);
}
