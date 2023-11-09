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

/*class myTestFixture: public ::testing::Test {
  public:
    myTestFixture( ) {
      // initialization;
      // can also be done in SetUp()
    }

    void SetUp( ) {
      // initialization or some code to run before each test
    }

    void TearDown( ) {
      // code to run after each test;
      // can be used instead of a destructor,
      // but exceptions can be handled in this function only
    }

    ~myTestFixture( )  {
      //resources cleanup, no exceptions allowed
    }

    // shared user data
};*/

TEST(argumentos, 1){
  const vector<string> vec = {"1", "./small.fld","out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(0,resultado);
}

//Número inválido de argumentos
TEST(argumentos, 2){
  const vector<string> vec = { "./small.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-1,resultado);
}

//El argumento de paso de parametros no es un número
TEST(argumentos, 3){
  const vector<string> vec = { "a","./small.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-1,resultado);
}

//El número de paso es negativo
TEST(argumentos, 4){
  const vector<string> vec = { "-1","./small.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-2,resultado);
}

//Error al abrir archivo de lectura
TEST(argumentos, 5){
  const vector<string> vec = { "1","./no_existe.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-3,resultado);
}

//Error al abrir archivo de salida
TEST(argumentos, 6){
  const vector<string> vec = { "1","./small.fld","../.+./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-4,resultado);
}

//Modificar el archivo de entrada
TEST(argumentos, 7){
  string file = "small.fld";
  ficheros::modificar_fichero(file,0);
  const vector<string> vec = { "1", "./small_modificado.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-5,resultado);
}

//Modificar el archivo de entrada para que el np sea negativo
TEST(argumentos, 8){
  string file = "small.fld";
  ficheros::modificar_fichero(file,-1);
  const vector<string> vec = { "1", "./small_modificado.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-5,resultado);
}


//Modificar el archivo de entrada para que np no coincida
TEST(argumentos, 9){
  string file = "small.fld";
  ficheros::modificar_fichero(file, 10);
  const vector<string> vec = { "1", "../small_modificado.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-5,resultado);
}

//El numero de paso de tiempo 0
TEST(argumentos, 10){
  const vector<string> vec = { "0","small.fld","./out.fld"};
  const int resultado = simulacion(vec);
  EXPECT_EQ(-2,resultado);
}

//Test correcto el archivo out.fld coincide con small-1.fld
TEST(salida, 1){
  const vector<string> vec = {"1", "./small.fld","./out.fld"};
  simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("./out.fld", ios::binary);
  file_correct.open("./out/small-1.fld", ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  EXPECT_EQ(0,resultado);
}

//Test correcto el archivo out.fld coincide con small-1.fld
TEST(salida, 2){
  const vector<string> vec = {"2", "./small.fld","./out.fld"};
  simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("./out.fld", ios::binary);
  file_correct.open("./out/small-2.fld", ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  EXPECT_EQ(0,resultado);
}

//Test correcto el archivo out.fld coincide con la el el small-3.fld
TEST(salida, 3){
  const vector<string> vec = {"3", "./small.fld","./out.fld"};
  simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("./out.fld", ios::binary);
  file_correct.open("./out/small-3.fld", ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  EXPECT_EQ(0,resultado);
}

TEST(trazas,uno){
  const vector<string> vec = {"1", "./small.fld","./out.fld"};
  simulacion(vec);
  ifstream file_in;
  struct Particula particula(4800);
  file_in.open("./trz/small/boundint-base-1.trz", ios::binary);
  const int resultado = ficheros::trazas(file_in,particula);
  EXPECT_EQ(0,resultado);
}
