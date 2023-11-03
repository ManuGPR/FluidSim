//
// Created by marina on 30/10/23.
//
#include "gtest/gtest.h"
#include "sim/calculos.hpp"
#include "sim/simulacion.cpp"
#include <fstream>

TEST(unitarias, uno){
  EXPECT_EQ(1,1);
}
TEST(unitarias, dos){
  EXPECT_EQ(3,3);
}

//Saliada del fichero coincide con la traza
/*
TEST(calculos,uno){
 const vector<string> vec = {"1", "../small.fld","../out.fld"};
 simulation(vec);
 ifstream archivo1;
 ifstream archivo2;
 archivo1.open("../boundint-base-1.trz", ios::binary);
 archivo2.open( "../out.fld", ios::binary);
 ASSERT_FLOAT_EQ(archivo2, archivo1);
}
*/

TEST(argumentos, uno){
  const vector<string> vec = {"1", "../../small.fld","../../out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(0,resultado);
}

//Numero invalido de argumentos
TEST(argumentos, dos){
  const vector<string> vec = { "../../ssmall.fld","../../out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-1,resultado);
}

//El argumento de paso de parametros no es un numero
TEST(argumentos, tres){
  const vector<string> vec = { "a","../../ssmall.fld","../../out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-1,resultado);
}

//El numero de paso es negativo
TEST(argumentos, cuatro){
  const vector<string> vec = { "-1","../../ssmall.fld","../../out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-2,resultado);
}
//El numero de paso es 0
TEST(argumentos, diez){
  const vector<string> vec = { "0","../../ssmall.fld","../../sout.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-2,resultado);
}


//Error al abrir archivo de lectura
TEST(argumentos, cinco){
  const vector<string> vec = { "1","../../ssmal.fld","../../sout.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-3,resultado);
}

//Error al abrir archivo de salida
TEST(argumentos, seis){
  const vector<string> vec = { "1","../../small.fld","../../outf."};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-4,resultado);
}

//Numero de particulas es igual a 0
//Modificar el archivo de entrada
TEST(argumentos, siete){
  const vector<string> vec = { "1", "../../small.fld","../../out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-5,resultado);
}

//Numero de particulas es negativo
//Modificar el archivo de entrada
TEST(argumentos, ocho){
  const vector<string> vec = {"1", "../../ssmall.fld","../../out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-5,resultado);
}


//Numero de particulas no coincide como el real
//Modificar el archivo de entrada
TEST(argumentos, nueve){
  const vector<string> vec = {"1", "../../ssmall.fld","../../out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-5,resultado);
}
