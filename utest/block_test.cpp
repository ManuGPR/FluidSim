#include "sim/block.hpp"
#include "sim/block.cpp"
#include "sim/calculos.hpp"
#include "sim/grid.hpp"
#include "gtest/gtest.h"

// Comprobacion num_bloque 0
TEST(num_bloques, 1) {
  const int quince = 15;
  struct Constantes constantes(1, quince);
  struct Enclosure3D malla(1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  block::num_bloques(malla.num_bloques, constantes.h);
  int const bloque  = malla.num_bloques[0];
  int const result = 1;
  ASSERT_EQ(bloque, result);
}

// Comprobacion num_bloque 1
TEST(num_bloques, 2) {
  const int quince = 15;
  struct Constantes constantes(1, quince);
  struct Enclosure3D malla(1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  block::num_bloques(malla.num_bloques, constantes.h);
  int const bloque  = malla.num_bloques[1];
  int const result = 1;
  ASSERT_EQ(bloque, result);
}
// Comprobacion num_bloque 2
TEST(num_bloques, 3) {
  const int quince = 15;
  struct Constantes constantes(1, quince);
  struct Enclosure3D malla(1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  block::num_bloques(malla.num_bloques, constantes.h);
  int const bloque  = malla.num_bloques[2];
  int const result = 1;
  ASSERT_EQ(bloque, result);
}

TEST(tam_bloque, 1) {
  const int quince = 15;
  struct Constantes constantes(1, quince);
  struct Enclosure3D malla(1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  block::num_bloques(malla.num_bloques, constantes.h);
  block::tam_bloques(malla.tam_bloques, malla.num_bloques);
  double const operando1  = malla.tam_bloques[0];
  double const result = 0.13;
  ASSERT_EQ(operando1, result);
}

TEST(tam_bloque, 2) {
  const int quince = 15;
  struct Constantes constantes(1, quince);
  struct Enclosure3D malla(1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  block::num_bloques(malla.num_bloques, constantes.h);
  block::tam_bloques(malla.tam_bloques, malla.num_bloques);
  double const  operando1  = malla.tam_bloques[1];
  double const result = 0.18;
  ASSERT_EQ(operando1, result);
}

TEST(tam_bloque, 3) {
  const int quince = 15;
  struct Constantes constantes(1, quince);
  struct Enclosure3D malla(1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  block::num_bloques(malla.num_bloques, constantes.h);
  block::tam_bloques(malla.tam_bloques, malla.num_bloques);
  double const operando1  = malla.tam_bloques[2];
  double const result = 0.13;
  ASSERT_EQ(operando1, result);
}

// Comprobacion funcion total_bloques
TEST(total_bloques, 1){
  vector<int> num_bloques = {1,2,3};
  int const oper = block::total_bloques(num_bloques);
  int const result = 6;
  ASSERT_EQ(oper,result);
}

// Comprobacion pos_x de estructura auxiliar
TEST(crear_auxiliar, 1){
  //bloque[8]=(1,0,2)
  vector<int> num_bloques = {2,2,3};
  int const total_bloques = block::total_bloques(num_bloques);
  struct block::Aux auxiliar(total_bloques);
  block::crear_auxiliar(num_bloques, auxiliar);
  int const oper = auxiliar.pos_x[9];
  int const result = 1;
  ASSERT_EQ(oper,result);
}

// Comprobacion pos_y de estructura auxiliar
TEST(crear_auxiliar, 2){
  //bloque[8]=(1,0,2)
  vector<int> num_bloques = {2,2,3};
  int const total_bloques = block::total_bloques(num_bloques);
  struct block::Aux auxiliar(total_bloques);
  block::crear_auxiliar(num_bloques, auxiliar);
  int const oper = auxiliar.pos_y[9];
  int const result = 0;
  ASSERT_EQ(oper,result);
}

// Comprobacion pos_z de estructura auxiliar
TEST(crear_auxiliar, 3){
  //bloque[8]=(1,0,2)
  vector<int> num_bloques = {2,2,3};
  int const total_bloques = block::total_bloques(num_bloques);
  struct block::Aux auxiliar(total_bloques);
  block::crear_auxiliar(num_bloques, auxiliar);
  int const oper = auxiliar.pos_z[9];
  int const result = 2;
  ASSERT_EQ(oper,result);
}

// Comprobacion bloque en esquina
TEST(crear_bloque, 1){
  //bloque[8]=(0,1,0)
  vector<struct block::Bloque> vector_bloques;
  vector<int> num_bloques = {2,2,3};
  const int total_bloques = block::total_bloques(num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  vector const oper = vector_bloques[2].bloque_contiguo;
  vector const result = {0,1,2,3,4,5,6,7};
  ASSERT_EQ(oper,result);
}

// Comprobacion bloque totalmente rodeado
TEST(crear_bloque, 2){
  //bloque[8]=(1,1,1)
  vector<struct block::Bloque> vector_bloques;
  vector<int> num_bloques = {3,3,3};
  const int total_bloques = block::total_bloques(num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  vector const oper = vector_bloques[13].bloque_contiguo;
  vector const result = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
  ASSERT_EQ(oper,result);
}

// Comprobacion bloque en lateral
TEST(crear_bloque, 3){
  //bloque[8]=(1,1,0)
  vector<struct block::Bloque> vector_bloques;
  vector<int> num_bloques = {3,3,3};
  const int total_bloques = block::total_bloques(num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  vector const oper = vector_bloques[4].bloque_contiguo;
  vector const result = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
  ASSERT_EQ(oper,result);
}

// Comprobacion bloque en vertice
TEST(crear_bloque, 4){
  //bloque[8]=(1,0,0)
  vector<struct block::Bloque> vector_bloques;
  vector<int> num_bloques = {3,3,3};
  const int total_bloques = block::total_bloques(num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  vector const oper = vector_bloques[1].bloque_contiguo;
  vector const result = {0,1,2,3,4,5,9,10,11,12,13,14};
  ASSERT_EQ(oper,result);
}

//comprobacion loc_particula_x, particula dento de bloque en cordenada x
TEST(loc_particula_x, 1){
  const int num1 = 10;
  const int num2 = 20;
  const int num3 = 15;
  const double num4 = 0.05;
  vector<int> num_bloques = {num1,num2,num3};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = num4;
  const int loc = block::loc_particula_x(pos, tam_bloque[0], num_bloques[0]);
  int const oper = loc;
  int const result = 8;
  ASSERT_EQ(oper,result);
}

//comprobacion loc_particula_x, particula fuera de bloque con cordenada x negativa
TEST(loc_particula_x, 2){
  const int num1 = 10;
  const int num2 = 20;
  const int num3 = 15;
  const double num4 = -0.07;
  vector<int> num_bloques = {num1,num2,num3};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = num4;
  const int loc = block::loc_particula_x(pos, tam_bloque[0], num_bloques[0]);
  int const oper = loc;
  int const result = 0;
  ASSERT_EQ(oper,result);
}

//comprobacion loc_particula_x, particula fuera de bloque con cordenada x positiva
TEST(loc_particula_x, 3){
  const int num1 = 10;
  const int num2 = 20;
  const int num3 = 15;
  const double num4 = 0.1;
  vector<int> num_bloques = {num1,num2,num3};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = num4;
  const int loc = block::loc_particula_x(pos, tam_bloque[0], num_bloques[0]);
  int const oper = loc;
  int const result = 9;
  ASSERT_EQ(oper,result);
}

//comprobacion loc_particula_y, particula dento de bloque en cordenada y
TEST(loc_particula_y, 1){
  const int num1 = 10;
  const int num2 = 20;
  const int num3 = 15;
  const double num4 = 0.04;
  vector<int> num_bloques = {num1,num2,num3};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = num4;
  const int loc = block::loc_particula_y(pos, tam_bloque[1], num_bloques[1]);
  int const oper = loc;
  int const result = 13;
  ASSERT_EQ(oper,result);
}

//comprobacion loc_particula_x, particula fuera de bloque con cordenada y negativa
TEST(loc_particula_y, 2){
  const int num1 = 10;
  const int num2 = 20;
  const int num3 = 15;
  const double num4 = -0.09;
  vector<int> num_bloques = {num1,num2,num3};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = num4;
  const int loc = block::loc_particula_y(pos, tam_bloque[1], num_bloques[1]);
  int const oper = loc;
  int const result = 0;
  ASSERT_EQ(oper,result);
}

//comprobacion loc_particula, particula fuera de bloque con cordenada y positiva
TEST(loc_particula_y, 3){
  const int num1 = 10;
  const int num2 = 20;
  const int num3 = 15;
  const double num4 = 0.11;
  vector<int> num_bloques = {num1,num2,num3};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = num4;
  const int loc = block::loc_particula_y(pos, tam_bloque[1], num_bloques[1]);
  int const oper = loc;
  int const result = 19;
  ASSERT_EQ(oper,result);
}

//comprobacion loc_particula_z, particula dento de bloque en cordenada z
TEST(loc_particula_z, 1){
  const int num1 = 10;
  const int num2 = 20;
  const int num3 = 15;
  const double num4 = 0.03;
  vector<int> num_bloques = {num1,num2,num3};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = num4;
  const int loc = block::loc_particula_z(pos, tam_bloque[2], num_bloques[2]);
  int const oper = loc;
  int const result = 10;
  ASSERT_EQ(oper,result);
}

//comprobacion loc_particula_z, particula fuera de bloque con cordenada z negativa
TEST(loc_particula_z, 2){
  const int num1 = 10;
  const int num2 = 20;
  const int num3 = 15;
  const double num4 = -0.08;
  vector<int> num_bloques = {num1,num2,num3};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = num4;
  const int loc = block::loc_particula_z(pos, tam_bloque[2], num_bloques[2]);
  int const oper = loc;
  int const result = 0;
  ASSERT_EQ(oper,result);
}

//comprobacion loc_particula_z, particula fuera de bloque con cordenada z positiva
TEST(loc_particula_z, 3){
  const int num1 = 10;
  const int num2 = 20;
  const int num3 = 15;
  const double num4 = 0.08;
  vector<int> num_bloques = {num1,num2,num3};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = num4;
  const int loc = block::loc_particula_z(pos, tam_bloque[2], num_bloques[2]);
  int const oper = loc;
  int const result = 14;
  ASSERT_EQ(oper,result);
}

//particula en cordenadas limite inferiores, bloque 0
TEST(loc_particula_bucle, 1){
  vector<struct block::Bloque> vector_bloques;
  struct Enclosure3D malla(1);
  vector<int> num_bloques = {3,3,3};
  int const total_bloques = block::total_bloques(num_bloques);
  Particula part(1);
  part.pos_x[0] = lim_inf_x;
  part.pos_y[0] = lim_inf_y;
  part.pos_z[0] = lim_inf_z;
  block::tam_bloques(malla.tam_bloques, num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  block::loc_particula_bucle(part, malla, num_bloques,vector_bloques);
  int const oper = part.bloque[0];
  int const result = 0;
  ASSERT_EQ(oper,result);
}

//particula en cordenadas limite superiores, bloque 26
TEST(loc_particula_bucle, 2){
  vector<struct block::Bloque> vector_bloques;
  struct Enclosure3D malla(1);
  vector<int> num_bloques = {3,3,3};
  int const total_bloques = block::total_bloques(num_bloques);
  Particula part(1);
  part.pos_x[0] = lim_sup_x;
  part.pos_y[0] = lim_sup_y;
  part.pos_z[0] = lim_sup_z;
  block::tam_bloques(malla.tam_bloques, num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  block::loc_particula_bucle(part, malla, num_bloques,vector_bloques);
  int const oper = part.bloque[0];
  int const result = 26;
  ASSERT_EQ(oper,result);
}

//particula en bloque central
TEST(loc_particula_bucle, 3){
  vector<struct block::Bloque> vector_bloques;
  struct Enclosure3D malla(1);
  vector<int> num_bloques = {3,3,3};
  int const total_bloques = block::total_bloques(num_bloques);
  Particula part(1);
  part.pos_x[0] = 0;
  part.pos_y[0] = 0;
  part.pos_z[0] = 0;
  block::tam_bloques(malla.tam_bloques, num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  block::loc_particula_bucle(part, malla, num_bloques,vector_bloques);
  int const oper = part.bloque[0];
  int const result = 13;
  ASSERT_EQ(oper,result);
}

//bloque con 2 particulas
TEST(loc_particula_bucle, 4){
  vector<struct block::Bloque> vector_bloques;
  struct Enclosure3D malla(2);
  vector<int> num_bloques = {3,3,3};
  int const total_bloques = block::total_bloques(num_bloques);
  Particula part(2);
  part.pos_x[0] = 0;
  part.pos_y[0] = 0;
  part.pos_z[0] = 0;
  part.pos_x[1] = 0;
  part.pos_y[1] = 0;
  part.pos_z[1] = 0;
  block::tam_bloques(malla.tam_bloques, num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  block::loc_particula_bucle(part, malla, num_bloques,vector_bloques);
  vector const oper = vector_bloques[13].lista_particulas;
  vector const result = {0,1};
  ASSERT_EQ(oper,result);
}

//bloque sin particulas
TEST(loc_particula_bucle, 5){
  vector<struct block::Bloque> vector_bloques;
  struct Enclosure3D malla(2);
  vector<int> num_bloques = {3,3,3};
  int const total_bloques = block::total_bloques(num_bloques);
  Particula part(2);
  part.pos_x[0] = 0;
  part.pos_y[0] = 0;
  part.pos_z[0] = 0;
  part.pos_x[1] = 0;
  part.pos_y[1] = 0;
  part.pos_z[1] = 0;
  block::tam_bloques(malla.tam_bloques, num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  block::loc_particula_bucle(part, malla, num_bloques,vector_bloques);
  vector const oper = vector_bloques[10].lista_particulas;
  vector vacio = {0};
  vacio.clear();
  vector const result = vacio;
  ASSERT_EQ(oper,result);
}
