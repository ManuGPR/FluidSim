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
/*
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
const double oper = constantes.operandos[4];
calc::incremento_densidades(part, oper, ids, cero);
EXPECT_EQ(part.dens[0], 23.714731682);
}
*/
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

// Comprobacion funcion total_bloques
TEST(total_bloques, 1){
  vector<int> num_bloques = {1,2,3};
  int const oper = block::total_bloques(num_bloques);
  int const result = 6;
  EXPECT_EQ(oper,result);
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
  EXPECT_EQ(oper,result);
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
  EXPECT_EQ(oper,result);
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
  EXPECT_EQ(oper,result);
}

// Comprobacion bloque en esquina
TEST(crear_bloque, 1){
  //bloque[8]=(0,1,0)
  vector<struct block::Bloque> vector_bloques;
  vector<int> num_bloques = {2,2,3};
  int total_bloques = block::total_bloques(num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  vector const oper = vector_bloques[2].bloque_contiguo;
  vector const result = {0,1,2,3,4,5,6,7};
  EXPECT_EQ(oper,result);
}

// Comprobacion bloque totalmente rodeado
TEST(crear_bloque, 2){
  //bloque[8]=(1,1,1)
  vector<struct block::Bloque> vector_bloques;
  vector<int> num_bloques = {3,3,3};
  int total_bloques = block::total_bloques(num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  vector const oper = vector_bloques[13].bloque_contiguo;
  vector const result = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
  EXPECT_EQ(oper,result);
}

// Comprobacion bloque en lateral
TEST(crear_bloque, 3){
  //bloque[8]=(1,1,0)
  vector<struct block::Bloque> vector_bloques;
  vector<int> num_bloques = {3,3,3};
  int total_bloques = block::total_bloques(num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  vector const oper = vector_bloques[4].bloque_contiguo;
  vector const result = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
  EXPECT_EQ(oper,result);
}

// Comprobacion bloque en vertice
TEST(crear_bloque, 4){
  //bloque[8]=(1,0,0)
  vector<struct block::Bloque> vector_bloques;
  vector<int> num_bloques = {3,3,3};
  int total_bloques = block::total_bloques(num_bloques);
  block::crear_bloques(vector_bloques, total_bloques, num_bloques);
  vector const oper = vector_bloques[1].bloque_contiguo;
  vector const result = {0,1,2,3,4,5,9,10,11,12,13,14};
  EXPECT_EQ(oper,result);
}

//comprobacion loc_particula_x, particula dento de bloque en cordenada x
TEST(loc_particula_x, 1){
  vector<int> num_bloques = {10,20,15};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = 0.05;
  int loc = block::loc_particula_x(pos, tam_bloque[0], num_bloques[0]);
  int const oper = loc;
  int const result = 8;
  EXPECT_EQ(oper,result);
}

//comprobacion loc_particula_x, particula fuera de bloque con cordenada x negativa
TEST(loc_particula_x, 2){
  vector<int> num_bloques = {10,20,15};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = -0.07;
  int loc = block::loc_particula_x(pos, tam_bloque[0], num_bloques[0]);
  int const oper = loc;
  int const result = 0;
  EXPECT_EQ(oper,result);
}

//comprobacion loc_particula_x, particula fuera de bloque con cordenada x positiva
TEST(loc_particula_x, 3){
  vector<int> num_bloques = {10,20,15};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = 0.1;
  int loc = block::loc_particula_x(pos, tam_bloque[0], num_bloques[0]);
  int const oper = loc;
  int const result = 9;
  EXPECT_EQ(oper,result);
}

//comprobacion loc_particula_y, particula dento de bloque en cordenada y
TEST(loc_particula_y, 1){
  vector<int> num_bloques = {10,20,15};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = 0.04;
  int loc = block::loc_particula_y(pos, tam_bloque[1], num_bloques[1]);
  int const oper = loc;
  int const result = 13;
  EXPECT_EQ(oper,result);
}

//comprobacion loc_particula_x, particula fuera de bloque con cordenada y negativa
TEST(loc_particula_y, 2){
  vector<int> num_bloques = {10,20,15};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = -0.09;
  int loc = block::loc_particula_y(pos, tam_bloque[1], num_bloques[1]);
  int const oper = loc;
  int const result = 0;
  EXPECT_EQ(oper,result);
}

//comprobacion loc_particula, particula fuera de bloque con cordenada y positiva
TEST(loc_particula_y, 3){
  vector<int> num_bloques = {10,20,15};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = 0.11;
  int loc = block::loc_particula_y(pos, tam_bloque[1], num_bloques[1]);
  int const oper = loc;
  int const result = 19;
  EXPECT_EQ(oper,result);
}

//comprobacion loc_particula_z, particula dento de bloque en cordenada z
TEST(loc_particula_z, 1){
  vector<int> num_bloques = {10,20,15};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = 0.03;
  int loc = block::loc_particula_z(pos, tam_bloque[2], num_bloques[2]);
  int const oper = loc;
  int const result = 10;
  EXPECT_EQ(oper,result);
}

//comprobacion loc_particula_z, particula fuera de bloque con cordenada z negativa
TEST(loc_particula_z, 2){
  vector<int> num_bloques = {10,20,15};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = -0.08;
  int loc = block::loc_particula_z(pos, tam_bloque[2], num_bloques[2]);
  int const oper = loc;
  int const result = 0;
  EXPECT_EQ(oper,result);
}

//comprobacion loc_particula_z, particula fuera de bloque con cordenada z positiva
TEST(loc_particula_z, 3){
  vector<int> num_bloques = {10,20,15};
  vector<double> tam_bloque;
  block::tam_bloques(tam_bloque, num_bloques);
  double pos = 0.8;
  int loc = block::loc_particula_z(pos, tam_bloque[2], num_bloques[2]);
  int const oper = loc;
  int const result = 14;
  EXPECT_EQ(oper,result);
}

//Comprobacion funcion trans_densidad con incremento == 1
TEST(trans_densidad,1){
  double const epsilon = 0.000001;
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double incremento = 1.0;
  const double resultado = calc::trans_densidad(incremento, constantes.operandos[0], constantes.operandos[1]);
  int result = 0;
  const double calculo =335.281263;
  if (fabs(calculo - resultado) > epsilon ){
    result = -1;
  }
  EXPECT_EQ(0,result);
}

//Comprobacion funcion trans_densidad con incremento negativo
TEST(trans_densidad,2){
  double const epsilon = 0.000001;
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double incremento = -1.0;
  const double resultado = calc::trans_densidad(incremento, constantes.operandos[0], constantes.operandos[1]);
  int result = 0;
  const double calculo =308.149165;
  if (fabs(calculo - resultado) > epsilon ){
    result = -1;
  }
  EXPECT_EQ(0,result);
}
//Comprobacion funcion trans_densidad con incremento == 0
TEST(trans_densidad,3){
  double const epsilon = 0.000001;
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double incremento = 0.0;
  const double resultado = calc::trans_densidad(incremento, constantes.operandos[0], constantes.operandos[1]);
  int result = 0;
  const double calculo =321.715214;
  if (fabs(calculo- resultado) > epsilon ){
    result = -1;
  }
  EXPECT_EQ(0,result);
}
//Comprobacion funcion trans_densidad con incremento == 2
TEST(trans_densidad,4){
  const double dos = 2;
  double const epsilon = 0.000001;
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double incremento = dos;
  const double resultado = calc::trans_densidad(incremento, constantes.operandos[0], constantes.operandos[1]);
  int result = 0;
  const double calculo =348.8473121 ;

  if (fabs(calculo - resultado) > epsilon ){
    result = -1;
  }
  EXPECT_EQ(0,result);
}

//Comprobacion funcion trans_acele cmprobacion del parametro diferencia
TEST(trans_acele, 1){
  const double uno = 0.1;
  const double dos = 0.2;
  const double  tres = 0.3;
  Particula particulas(2);
  particulas.pos_x[0] = uno;
  particulas.pos_y[0] = uno;
  particulas.pos_z[0] = dos;
  particulas.pos_x[1] = tres;
  particulas.pos_y[1] = dos;
  particulas.pos_z[1] = uno;
  const double diferencia = pow((particulas.pos_x[0] - particulas.pos_x[1]), 2)  +
                          pow((particulas.pos_y[0] - particulas.pos_y[1]) ,2) +
                          pow((particulas.pos_z[0] - particulas.pos_z[1]),2);
  EXPECT_EQ(diferencia , 0.06);
}

//Comprobacion funcion trans_acele, compracbion acel_x[0]
TEST(trans_acelec, 2){
  const double uno = 0.1;
  const double dos = 0.2;
  const double  tres = 0.3;
  double const epsilon = 0.001;
  Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  Particula particulas(2);
  particulas.pos_x[0] = uno;
  particulas.pos_y[0] = uno;
  particulas.pos_z[0] = dos;
  particulas.pos_x[1] = tres;
  particulas.pos_y[1] = dos;
  particulas.pos_z[1] = uno;
  for (int i = 0; i < 2; i++) {
    particulas.vel_x[i] = 1.0;
    particulas.vel_y[i] = 1.0;
    particulas.vel_z[i] = 1.0;
    particulas.dens[i] = 1.0;
  }
  vector<int> const part = {0,1};
  const double diferencia = pow((particulas.pos_x[0] - particulas.pos_x[1]), 2)  +
                      pow((particulas.pos_y[0] - particulas.pos_y[1]) ,2) +
                      pow((particulas.pos_z[0] - particulas.pos_z[1]),2);

  calc::trans_acele(particulas, part, constantes, diferencia );
  const double calculo =3107793.178;
  int result = 0;
  if (fabs(calculo - particulas.acel_x[0]) >= epsilon ){
    result = -1;
  }
  EXPECT_EQ(0 , result );
}
//Comprobacion funcion trans_acele, compracbion acel_x[1]
TEST(trans_acelec, 3){
  const double uno = 0.1;
  const double dos = 0.2;
  const double  tres = 0.3;
  double const epsilon = 0.001;
  Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  Particula particulas(2);
  particulas.pos_x[0] = uno;
  particulas.pos_y[0] = uno;
  particulas.pos_z[0] = dos;
  particulas.pos_x[1] = tres;
  particulas.pos_y[1] = dos;
  particulas.pos_z[1] = uno;
  for (int i = 0; i < 2; i++) {
    particulas.vel_x[i] = 1.0;
    particulas.vel_y[i] = 1.0;
    particulas.vel_z[i] = 1.0;
    particulas.dens[i] = 1.0;
  }
  vector<int> const part = {0,1};
  const double diferencia = pow((particulas.pos_x[0] - particulas.pos_x[1]), 2)  +
                            pow((particulas.pos_y[0] - particulas.pos_y[1]) ,2) +
                            pow((particulas.pos_z[0] - particulas.pos_z[1]),2);

  calc::trans_acele(particulas, part, constantes, diferencia );
  const double calculo =-3107793.178;
  int result = 0;
  if (fabs( calculo - particulas.acel_x[1]) >= epsilon ){
    result = -1;
  }
  EXPECT_EQ(0 , result );
}

//Comprobacion funcion trans_acele, compracbion acel_y[0]
TEST(trans_acelec, 4){
  const double uno = 0.1;
  const double dos = 0.2;
  const double  tres = 0.3;
  double const epsilon = 10;
  Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  Particula particulas(2);
  particulas.pos_x[0] = uno;
  particulas.pos_y[0] = uno;
  particulas.pos_z[0] = dos;
  particulas.pos_x[1] = tres;
  particulas.pos_y[1] = dos;
  particulas.pos_z[1] = uno;
  for (int i = 0; i < 2; i++) {
    particulas.vel_x[i] = 1.0;
    particulas.vel_y[i] = 1.0;
    particulas.vel_z[i] = 1.0;
    particulas.dens[i] = 1.0;
  }
  vector<int> const part = {0,1};
  const double diferencia = pow((particulas.pos_x[0] - particulas.pos_x[1]), 2)  +
                            pow((particulas.pos_y[0] - particulas.pos_y[1]) ,2) +
                            pow((particulas.pos_z[0] - particulas.pos_z[1]),2);

  calc::trans_acele(particulas, part, constantes, diferencia );
  const double calculo =1553896.589;
  int result = 0;
  if (fabs(calculo - particulas.acel_y[0]) > epsilon ){
    result = -1;
  }
  EXPECT_EQ(0 , result );
}

//Comprobacion funcion trans_acele, compracbion acel_y[1]
TEST(trans_acelec, 5){
  const double uno = 0.1;
  const double dos = 0.2;
  const double  tres = 0.3;
  double const epsilon = 10;
  Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  Particula particulas(2);
  particulas.pos_x[0] = uno;
  particulas.pos_y[0] = uno;
  particulas.pos_z[0] = dos;
  particulas.pos_x[1] = tres;
  particulas.pos_y[1] = dos;
  particulas.pos_z[1] = uno;
  for (int i = 0; i < 2; i++) {
    particulas.vel_x[i] = 1.0;
    particulas.vel_y[i] = 1.0;
    particulas.vel_z[i] = 1.0;
    particulas.dens[i] = 1.0;
  }
  vector<int> const part = {0,1};
  const double diferencia = pow((particulas.pos_x[0] - particulas.pos_x[1]), 2)  +
                            pow((particulas.pos_y[0] - particulas.pos_y[1]) ,2) +
                            pow((particulas.pos_z[0] - particulas.pos_z[1]),2);

  calc::trans_acele(particulas, part, constantes, diferencia );
  const double calculo = -1553896.589;
  int result = 0;
  if (fabs(calculo - particulas.acel_y[1]) >= epsilon ){
    result = -1;
  }
  EXPECT_EQ(0 , result );
}

//Comprobacion funcion trans_acele, compracbion acel_z[0]
TEST(trans_acelec, 6){
  const double uno = 0.1;
  const double dos = 0.2;
  const double  tres = 0.3;
  double const epsilon = 0.001;
  Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  Particula particulas(2);
  particulas.pos_x[0] = uno;
  particulas.pos_y[0] = uno;
  particulas.pos_z[0] = dos;
  particulas.pos_x[1] = tres;
  particulas.pos_y[1] = dos;
  particulas.pos_z[1] = uno;
  for (int i = 0; i < 2; i++) {
    particulas.vel_x[i] = 1.0;
    particulas.vel_y[i] = 1.0;
    particulas.vel_z[i] = 1.0;
    particulas.dens[i] = 1.0;
  }
  vector<int> const part = {0,1};
  const double diferencia = pow((particulas.pos_x[0] - particulas.pos_x[1]), 2)  +
                            pow((particulas.pos_y[0] - particulas.pos_y[1]) ,2) +
                            pow((particulas.pos_z[0] - particulas.pos_z[1]),2);

  calc::trans_acele(particulas, part, constantes, diferencia );
  const double calculo =- 1553896.589;
  int result = 0;
  if (fabs(calculo - particulas.acel_z[0]) >= epsilon ){
    result = -1;
  }
  EXPECT_EQ(0 , result );
}

//Comprobacion funcion trans_acele, compracbion acel_z[1]
TEST(trans_acelec, 7){
  const double uno = 0.1;
  const double dos = 0.2;
  const double  tres = 0.3;
  double const epsilon = 0.001;
  Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  Particula particulas(2);
  particulas.pos_x[0] = uno;
  particulas.pos_y[0] = uno;
  particulas.pos_z[0] = dos;
  particulas.pos_x[1] = tres;
  particulas.pos_y[1] = dos;
  particulas.pos_z[1] = uno;
  for (int i = 0; i < 2; i++) {
    particulas.vel_x[i] = 1.0;
    particulas.vel_y[i] = 1.0;
    particulas.vel_z[i] = 1.0;
    particulas.dens[i] = 1.0;
  }
  vector<int> const part = {0,1};
  const double diferencia = pow((particulas.pos_x[0] - particulas.pos_x[1]), 2)  +
                            pow((particulas.pos_y[0] - particulas.pos_y[1]) ,2) +
                            pow((particulas.pos_z[0] - particulas.pos_z[1]),2);

  calc::trans_acele(particulas, part, constantes, diferencia );
  const double calculo =1553896.589;
  int result = 0;
  if (fabs(calculo - particulas.acel_z[1]) >= epsilon ){
    result = -1;
  }
  EXPECT_EQ(0 , result );
}

//Comprobacion funcion mov_part, compracbion pos_x[0]
TEST(mov_part,1){
  double const epsilon = 0.0000001;
  Particula particulas(1);
  particulas.pos_x[0] = 1.0;
  particulas.pos_y[0] = 1.0;
  particulas.pos_z[0] = 1.0;
  particulas.hv_x[0] = 1.0;
  particulas.hv_y[0] = 1.0;
  particulas.hv_z[0] = 1.0;
  particulas.acel_x[0] = 1.0;
  particulas.acel_y[0] = 1.0;
  particulas.acel_z[0] = 1.0;
  calc::mov_part(particulas,0);
  const double calculo =1.001001;
  int result = 0;
  if (fabs(calculo - particulas.pos_x[0]) >= epsilon){
    result = -1;
  }
  EXPECT_EQ(0 , result );
}

//Comprobacion funcion mov_part, compracbion pos_y[0]
TEST(mov_part,2){
  double const epsilon = 0.0000001;
  Particula particulas(1);
  particulas.pos_x[0] = 1.0;
  particulas.pos_y[0] = 1.0;
  particulas.pos_z[0] = 1.0;
  particulas.hv_x[0] = 1.0;
  particulas.hv_y[0] = 1.0;
  particulas.hv_z[0] = 1.0;
  particulas.acel_x[0] = 1.0;
  particulas.acel_y[0] = 1.0;
  particulas.acel_z[0] = 1.0;
  calc::mov_part(particulas,0);
  const double calculo =1.001001;
  int result = 0;
  if (fabs(calculo - particulas.pos_y[0]) >= epsilon){
    result = -1;
  }
  EXPECT_EQ(0 , result );
}
//Comprobacion funcion mov_part, compracbion pos_z[0]
TEST(mov_part,3){
  double const epsilon = 0.0000001;
  Particula particulas(1);
  particulas.pos_x[0] = 1.0;
  particulas.pos_y[0] = 1.0;
  particulas.pos_z[0] = 1.0;
  particulas.hv_x[0] = 1.0;
  particulas.hv_y[0] = 1.0;
  particulas.hv_z[0] = 1.0;
  particulas.acel_x[0] = 1.0;
  particulas.acel_y[0] = 1.0;
  particulas.acel_z[0] = 1.0;
  calc::mov_part(particulas,0);
  const double calculo =1.001001;
  int result = 0;
  if (fabs(calculo - particulas.pos_z[0]) >= epsilon){
    result = -1;
  }
  EXPECT_EQ(0 , result );
}
//Comprobacion funcion mov_part, compracbion vel_x[0]
TEST(mov_part,4){
  Particula particulas(1);
  particulas.pos_x[0] = 1.0;
  particulas.pos_y[0] = 1.0;
  particulas.pos_z[0] = 1.0;
  particulas.hv_x[0] = 1.0;
  particulas.hv_y[0] = 1.0;
  particulas.hv_z[0] = 1.0;
  particulas.acel_x[0] = 1.0;
  particulas.acel_y[0] = 1.0;
  particulas.acel_z[0] = 1.0;
  calc::mov_part(particulas,0);
  EXPECT_EQ(1.0005 , particulas.vel_x[0]);
}
//Comprobacion funcion mov_part, compracbion vel_y[0]
TEST(mov_part,5){
  Particula particulas(1);
  particulas.pos_x[0] = 1.0;
  particulas.pos_y[0] = 1.0;
  particulas.pos_z[0] = 1.0;
  particulas.hv_x[0] = 1.0;
  particulas.hv_y[0] = 1.0;
  particulas.hv_z[0] = 1.0;
  particulas.acel_x[0] = 1.0;
  particulas.acel_y[0] = 1.0;
  particulas.acel_z[0] = 1.0;
  calc::mov_part(particulas,0);
  EXPECT_EQ(1.0005 , particulas.vel_y[0]);
}
//Comprobacion funcion mov_part, compracbion vel_z[0]
TEST(mov_part,6){
  Particula particulas(1);
  particulas.pos_x[0] = 1.0;
  particulas.pos_y[0] = 1.0;
  particulas.pos_z[0] = 1.0;
  particulas.hv_x[0] = 1.0;
  particulas.hv_y[0] = 1.0;
  particulas.hv_z[0] = 1.0;
  particulas.acel_x[0] = 1.0;
  particulas.acel_y[0] = 1.0;
  particulas.acel_z[0] = 1.0;
  calc::mov_part(particulas,0);
  EXPECT_EQ(1.0005 , particulas.vel_z[0]);
}
//Comprobacion funcion mov_part, compracbion hv_x[0]
TEST(mov_part,7){
  Particula particulas(1);
  particulas.pos_x[0] = 1.0;
  particulas.pos_y[0] = 1.0;
  particulas.pos_z[0] = 1.0;
  particulas.hv_x[0] = 1.0;
  particulas.hv_y[0] = 1.0;
  particulas.hv_z[0] = 1.0;
  particulas.acel_x[0] = 1.0;
  particulas.acel_y[0] = 1.0;
  particulas.acel_z[0] = 1.0;
  calc::mov_part(particulas,0);
  EXPECT_EQ(1.001 , particulas.hv_x[0]);
}
//Comprobacion funcion mov_part, compracbion hv_y[0]
TEST(mov_part,8){
  Particula particulas(1);
  particulas.pos_x[0] = 1.0;
  particulas.pos_y[0] = 1.0;
  particulas.pos_z[0] = 1.0;
  particulas.hv_x[0] = 1.0;
  particulas.hv_y[0] = 1.0;
  particulas.hv_z[0] = 1.0;
  particulas.acel_x[0] = 1.0;
  particulas.acel_y[0] = 1.0;
  particulas.acel_z[0] = 1.0;
  calc::mov_part(particulas,0);
  EXPECT_EQ(1.001 , particulas.hv_y[0]);
}
//Comprobacion funcion mov_part, compracbion hv_z[0]
TEST(mov_part,9){
  Particula particulas(1);
  particulas.pos_x[0] = 1.0;
  particulas.pos_y[0] = 1.0;
  particulas.pos_z[0] = 1.0;
  particulas.hv_x[0] = 1.0;
  particulas.hv_y[0] = 1.0;
  particulas.hv_z[0] = 1.0;
  particulas.acel_x[0] = 1.0;
  particulas.acel_y[0] = 1.0;
  particulas.acel_z[0] = 1.0;
  calc::mov_part(particulas,0);
  EXPECT_EQ(1.001 , particulas.hv_z[0]);
}


