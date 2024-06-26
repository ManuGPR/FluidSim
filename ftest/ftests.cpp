#include "gtest/gtest.h"
#include "sim/calculos.hpp"
#include "sim/file.hpp"
#include "sim/simulacion.hpp"
#include "sim/block.hpp"
#include "sim/grid.hpp"
#include <fstream>


TEST(argumentos, 1){
  const vector<string> vec = {"1", "in/small.fld","out.fld"};
  const int resultado = sim::simulacion(vec);
  if (remove("out.fld") == 0) {EXPECT_EQ(0,resultado);}
}

//Número inválido de argumentos
TEST(argumentos, 2){
  const vector<string> vec = { "in/small.fld","out.fld"};
  const int resultado = sim::simulacion(vec);
  if (remove("out.fld") == 0) {EXPECT_EQ(-1,resultado);}
}

//El argumento de paso de parametros no es un número
TEST(argumentos, 3){
  const vector<string> vec = { "a","in/small.fld","out.fld"};
  const int resultado = sim::simulacion(vec);
  if (remove("../out,fld") == 0) {EXPECT_EQ(-1,resultado);}
}

//El número de paso es negativo
TEST(argumentos, 4){
  const vector<string> vec = { "-1","in/small.fld","out.fld"};
  const int resultado = sim::simulacion(vec);
  if (remove("out.fld") == 0) {EXPECT_EQ(-2,resultado);}
}

//Error al abrir archivo de lectura
TEST(argumentos, 5){
  const vector<string> vec = { "1","./no_existe.fld","out.fld"};
  const int resultado = sim::simulacion(vec);
  if (remove("out.fld") == 0) {EXPECT_EQ(-3,resultado);}
}

//Error al abrir archivo de salida
TEST(argumentos, 6){
  const vector<string> vec = { "1","in/small.fld","../.+./out.fld"};
  const int resultado = sim::simulacion(vec);
  if (remove("out.fld") == 0) {EXPECT_EQ(-4,resultado);}
}

//Modificar el archivo de entrada para que el np sea negativo
TEST(argumentos, 7) {
  ficheros::archivo_creacion_entero(-1);
  const vector<string> vec = { "1", "prueba_escr.fld","out.fld"};
  const int resultado = sim::simulacion(vec);
  if (remove("prueba_escr.fld") == 0) {}
  if (remove("out.fld") == 0) {EXPECT_EQ(-5,resultado);}
}

TEST(argumentos, 8) {
  ficheros::archivo_creacion_entero(0);
  const vector<string> vec = { "1", "prueba_escr.fld","out.fld"};
  const int resultado = sim::simulacion(vec);
  if (remove("prueba_escr.fld") == 0) {}
  if (remove("out.fld") == 0) {EXPECT_EQ(-5,resultado);}
}

//Modificar el archivo de entrada para que np no coincide y es mayor que el numero de particula
TEST(argumentos, 9) {
  ficheros::archivo_creacion_entero(3);
  const vector<string> vec = { "1", "prueba_escr.fld","out.fld"};
  const int resultado = sim::simulacion(vec);
  if (remove("prueba_escr.fld") == 0) {}
  if (remove("out.fld") == 0) {EXPECT_EQ(-5,resultado);}
}

//Modificar el archivo de entrada para que np no coincida y el numero de particulas es menor
TEST(argumentos, 10) {
 ficheros::archivo_creacion_entero(1);
 const vector<string> vec = { "1", "prueba_escr.fld","out.fld"};
 const int resultado = sim::simulacion(vec);
 if (remove("prueba_escr.fld") == 0) {}
 if (remove("out.fld") == 0) {EXPECT_EQ(-5,resultado);}
}

//El numero de paso de tiempo 0
TEST(argumentos, 11){
  const vector<string> vec = { "0", "in/small.fld", "out.fld"};
  const int resultado = sim::simulacion(vec);
  if (remove("out.fld") == 0) {EXPECT_EQ(-2,resultado);}
}

//Test correcto el archivo out.fld coincide con small-1.fld
TEST(salida, 1){
  const vector<string> vec = {"1", "in/small.fld", "out.fld"};
  sim::simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("out.fld", ios::binary);
  file_correct.open("out/small-1.fld", ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  if (remove("out.fld") == 0) {EXPECT_EQ(0,resultado);}
}

//Test correcto el archivo out.fld coincide con small-1.fld
TEST(salida, 2){
  const vector<string> vec = {"2", "in/small.fld", "out.fld"};
  sim::simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("out.fld", ios::binary);
  file_correct.open("out/small-2.fld", ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  if (remove("out.fld") == 0) {EXPECT_EQ(0,resultado);}
}

//Test correcto el archivo out.fld coincide con la el el small-3.fld
TEST(salida, 3){
  const vector<string> vec = {"3", "in/small.fld", "out.fld"};
  sim::simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("out.fld", ios::binary);
  file_correct.open("out/small-3.fld", ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  if (remove("out.fld") == 0) {EXPECT_EQ(0,resultado);}
}

TEST(salida, 4){
  const std::string path_to_small = std::filesystem::absolute("in/small.fld");
  const vector<string> vec = {"4", path_to_small,"out.fld"};
  sim::simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("out.fld", ios::binary);
  const std::string path_to_correct = std::filesystem::absolute("out/small-4.fld");
  file_correct.open(path_to_correct, ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  if (remove("out.fld") == 0) {EXPECT_EQ(0,resultado);}
}
TEST(salida, 5){
  const std::string path_to_small = std::filesystem::absolute("in/small.fld");
  const vector<string> vec = {"5", path_to_small,"out.fld"};
  sim::simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("out.fld", ios::binary);
  const std::string path_to_correct = std::filesystem::absolute("out/small-5.fld");
  file_correct.open(path_to_correct, ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  if (remove("out.fld") == 0) {EXPECT_EQ(0,resultado);}
}

//Test correcto el archivo out.fld coincide con small-1.fld
TEST(salida, 6){
  const std::string path_to_small = std::filesystem::absolute("in/large.fld");
  const vector<string> vec = {"1", path_to_small, "out.fld"};
  sim::simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("out.fld", ios::binary);
  const std::string path_to_correct = std::filesystem::absolute("out/large-1.fld");
  file_correct.open(path_to_correct, ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  if (remove("out.fld") == 0) {EXPECT_EQ(0,resultado);}
}

//Test correcto el archivo out.fld coincide con small-1.fld
TEST(salida, 7){
  const std::string path_to_small = std::filesystem::absolute("in/large.fld");
  const vector<string> vec = {"2", path_to_small,"out.fld"};
  sim::simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("out.fld", ios::binary);
  const std::string path_to_correct = std::filesystem::absolute("out/large-2.fld");
  file_correct.open(path_to_correct, ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  if (remove("out.fld") == 0) {EXPECT_EQ(0,resultado);}
}

//Test correcto el archivo out.fld coincide con la el el small-3.fld
TEST(salida, 8){
  const std::string path_to_small = std::filesystem::absolute("in/large.fld");
  const vector<string> vec = {"3", path_to_small,"out.fld"};
  sim::simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("out.fld", ios::binary);
  const std::string path_to_correct = std::filesystem::absolute("out/large-3.fld");
  file_correct.open(path_to_correct, ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  if (remove("out.fld") == 0) {EXPECT_EQ(0,resultado);}
}
TEST(salida, 9){
  const std::string path_to_small = std::filesystem::absolute("in/large.fld");
  const vector<string> vec = {"4", path_to_small,"out.fld"};
  sim::simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("out.fld", ios::binary);
  const std::string path_to_correct = std::filesystem::absolute("out/large-4.fld");
  file_correct.open(path_to_correct, ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  if (remove("out.fld") == 0) {EXPECT_EQ(0,resultado);}
}
TEST(salida, 10){
  const std::string path_to_small = std::filesystem::absolute("in/large.fld");
  const vector<string> vec = {"5", path_to_small,"out.fld"};
  sim::simulacion(vec);
  ifstream file_in;
  ifstream file_correct;
  file_in.open("out.fld", ios::binary);
  const std::string path_to_correct = std::filesystem::absolute("out/large-5.fld");
  file_correct.open(path_to_correct, ios::binary);
  const int resultado = ficheros::comparar_ficheros(file_in,file_correct);
  if (remove("out.fld") == 0) {EXPECT_EQ(0,resultado);}
}