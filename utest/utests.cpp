#include "sim/block.hpp"
#include "sim/calculos.hpp"
#include "sim/constants.hpp"
#include "sim/file.hpp"
#include "sim/grid.hpp"
#include "sim/simulacion.hpp"
#include "gtest/gtest.h"

/*TEST(bloques, 3){
  struct Particula particula(1);
  struct Enclosure3D malla(1);
  vector<struct block::Bloque> vector_bloques;
  block::loc_particula_bucle(particula, malla,);


  EXPECT_EQ(oper,result);
}

 TEST(crear_bloque, 1){
 //bloque[8]=(2,0,1)
 vector<struct block::Bloque> vector_bloques;
 vector<int> num_bloques = {2,2,3};
 int total_bloques = block::total_bloques(num_bloques);
 block::crear_bloques(bloques, total_bloques, num_bloques);
 int const oper = auxiliar.posx[6];
 int const result = 2;
  EXPECT_EQ(oper,result);
}

 */

// Comprobacion de la masa
TEST(operandos, 1) {
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double const oper   = constantes.masa;
  double const result = 1000.0;
  EXPECT_EQ(oper, result);
}

// Comprobacion de h
TEST(operandos, 2) {
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double const oper   = constantes.h;
  double const result = 1.695;
  EXPECT_EQ(oper, result);
}

// Comprobacion de nts
TEST(operandos, 3) {
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  int const oper   = constantes.nts;
  int const result = 1;
  EXPECT_EQ(oper, result);
}

// Comprobacion de operandando 1
TEST(operandos, 4) {
  double const epsilon = 0.0000001;
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double const operando1   = constantes.operandos[0];
  double const operando2 = 13.56604909;
  int result = 0;
  if (fabs(operando1 - operando2 ) > epsilon ){
    result = -1;
  }
  EXPECT_EQ(0, result);
}

// Comprobacion de operandando 2
TEST(operandos, 5) {
  double const epsilon = 0.000001;
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double const operando1   = constantes.operandos[1];
  double const operando2 = 321.715214;
  cout << constantes.operandos[1];
  int result = 0;
  if (fabs(operando1 - operando2 ) > epsilon ){
    result = -1;
  }

  EXPECT_EQ(0, result);
}

// Comprobacion de operandando 3
TEST(operandos, 6) {
  double const epsilon = 0.0000001;
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double const operando1   = constantes.operandos[2];
  double const operando2 = 906.0156196;
  int result = 0;
  if (fabs(operando1 - operando2 ) > epsilon ){
    result = -1;
  }
  EXPECT_EQ(0, result);
}

// Comprobacion de operandando 4
TEST(operandos, 7) {
  double const epsilon = 0.0000001;
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double const operando1  = constantes.operandos[3];
  double const operando2 = 241.6041652;
  int result = 0;
  if (fabs(operando1 - operando2 ) > epsilon ){
    result = -1;
  }
  EXPECT_EQ(0, result);
}

// Comprobacion de operandando 5
TEST(operandos, 8) {
  double const epsilon = 0.0000001;
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double const operando1   = constantes.operandos[4];
  double const operando2 = 2.873025;
  int result = 0;
  if (fabs(operando1 - operando2 ) > epsilon ){
    result = -1;
  }
  EXPECT_EQ(0, result);
}

// Comprobación de la inicialización de densidad
TEST(inicializar_dens_acel, 1) {
  Particula part(1);
  calc::inicializar_dens_acel(part, 0);
  const double resultado = 0.0;
  const double densidad = part.dens[0];
  EXPECT_EQ(resultado, densidad);
}

// Comprobación de la inizialización de acel_
TEST(inicializar_dens_acel, 2) {
  Particula part(1);
  calc::inicializar_dens_acel(part, 0);
  EXPECT_EQ(gravedad_x, part.acel_x[0]);
}

// Comprobación de la inizialización de acel_y
TEST(inicializar_dens_acel, 3) {
  Particula part(1);
  calc::inicializar_dens_acel(part, 0);
  EXPECT_EQ(gravedad_y, part.acel_y[0]);
}

// Comprobación de la inizialización de acel_z
TEST(inicializar_dens_acel, 4) {
  Particula part(1);
  calc::inicializar_dens_acel(part, 0);
  EXPECT_EQ(gravedad_z, part.acel_z[0]);
}

// Comprobación del incremento de densidades
TEST(incremento_densidades, 1) {
  Particula part(2);
  for (int i = 0; i < 2; i++) {
    calc::inicializar_dens_acel(part, i);
    part.pos_x[i] = lim_inf_x;
    part.pos_y[i] = lim_inf_y;
    part.pos_z[i] = lim_inf_z;
    part.vel_x[i] = 1.0;
    part.vel_y[i] = 1.0;
    part.vel_z[i] = 1.0;
    part.hv_x[i] = 1.0;
    part.hv_y[i] = 1.0;
    part.hv_z[i] = 1.0;
    part.loc_x[i] = 0;
    part.loc_y[i] = 0;
    part.loc_z[i] = 0;
    part.bloque[i] = 0;
  }
Constantes constantes(1, 1);
double uno = 1.0;
double cero = 0.0;
calc::calcular_operandos(uno, uno, constantes.operandos);
vector<int> const ids = {0, 1};
calc::incremento_densidades(part, constantes.operandos[4], ids, cero);
EXPECT_EQ(part.dens[0], 23.714731682);
}

// Comprobacion num_bloque 0

TEST(num_bloques, 1) {
  const int quince = 15;
  struct Constantes constantes(1, quince);
  struct Enclosure3D malla(1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  block::num_bloques(malla.num_bloques, constantes.h);
  int const bloque  = malla.num_bloques[0];
  int const result = 1;
  EXPECT_EQ(bloque, result);
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
  EXPECT_EQ(bloque, result);
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
  EXPECT_EQ(bloque, result);
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
  EXPECT_EQ(operando1, result);
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
  EXPECT_EQ(operando1, result);
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
  EXPECT_EQ(operando1, result);
}


TEST(total_bloques, 1){
  vector<int> num_bloques = {1,2,3};
  int const oper = block::total_bloques(num_bloques);
  int const result = 6;
  EXPECT_EQ(oper,result);
}

TEST(crear_auxiliar, 1){
  //bloque[8]=(1,0,2)
  vector<int> num_bloques = {2,2,3};
  int const total_bloques = block::total_bloques(num_bloques);
  struct block::Aux auxiliar(total_bloques);
  block::crear_auxiliar(num_bloques, auxiliar);
  int const oper = auxiliar.pos_x[9];
  int const result = 1;
  EXPECT_EQ(oper,result);
}

TEST(crear_auxiliar, 2){
  //bloque[8]=(1,0,2)
  vector<int> num_bloques = {2,2,3};
  int const total_bloques = block::total_bloques(num_bloques);
  struct block::Aux auxiliar(total_bloques);
  block::crear_auxiliar(num_bloques, auxiliar);
  int const oper = auxiliar.pos_y[9];
  int const result = 0;
  EXPECT_EQ(oper,result);
}

TEST(crear_auxiliar, 3){
  //bloque[8]=(1,0,2)
  vector<int> num_bloques = {2,2,3};
  int const total_bloques = block::total_bloques(num_bloques);
  struct block::Aux auxiliar(total_bloques);
  block::crear_auxiliar(num_bloques, auxiliar);
  int const oper = auxiliar.pos_z[9];
  int const result = 2;
  EXPECT_EQ(oper,result);
}


