#include "sim/calculos.hpp"
#include "sim/calculos.cpp"
#include "sim/constants.hpp"
#include "sim/grid.hpp"
#include "gtest/gtest.h"

// Comprobacion de la masa
TEST(operandos, 1) {
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double const oper   = constantes.masa;
  double const result = 1000.0;
  ASSERT_EQ(oper, result);
}

// Comprobacion de h
TEST(operandos, 2) {
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  double const oper   = constantes.h;
  double const result = 1.695;
  ASSERT_EQ(oper, result);
}

// Comprobacion de nts
TEST(operandos, 3) {
  struct Constantes constantes(1, 1);
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  int const oper   = constantes.nts;
  int const result = 1;
  ASSERT_EQ(oper, result);
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
  ASSERT_EQ(0, result);
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

  ASSERT_EQ(0, result);
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
  ASSERT_EQ(0, result);
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
  ASSERT_EQ(0, result);
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
  ASSERT_EQ(0, result);
}

// Comprobación de la inicialización de densidad
TEST(inicializar_dens_acel, 1) {
  Particula part(1);
  calc::inicializar_dens_acel(part, 0);
  const double resultado = 0.0;
  const double densidad = part.dens[0];
  ASSERT_EQ(resultado, densidad);
}

// Comprobación de la inizialización de acel_
TEST(inicializar_dens_acel, 2) {
  Particula part(1);
  calc::inicializar_dens_acel(part, 0);
  ASSERT_EQ(gravedad_x, part.acel_x[0]);
}

// Comprobación de la inizialización de acel_y
TEST(inicializar_dens_acel, 3) {
  Particula part(1);
  calc::inicializar_dens_acel(part, 0);
  ASSERT_EQ(gravedad_y, part.acel_y[0]);
}

// Comprobación de la inizialización de acel_z
TEST(inicializar_dens_acel, 4) {
  Particula part(1);
  calc::inicializar_dens_acel(part, 0);
  ASSERT_EQ(gravedad_z, part.acel_z[0]);
}

// Comprobación del incremento de densidades
TEST(incremento_densidades, 1) {
  Particula part(2);
  const double epsilon = 0.0000001;
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
    part.dens[i] = 0;
  }
  Constantes constantes(1, 1);
  double cero = 0.0;
  calc::calcular_operandos(constantes.masa, constantes.h, constantes.operandos);
  vector<int> const ids = {0, 1};
  calc::incremento_densidades(part, constantes.operandos[4], ids, cero);
  int result = 0;
  const double density = 23.714731682;
  if (fabs(density - part.dens[0]) >= epsilon) {result = -1;}
  ASSERT_EQ(result, 0);
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
  ASSERT_EQ(0,result);
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
  ASSERT_EQ(0,result);
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
  ASSERT_EQ(0,result);
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
  ASSERT_EQ(0,result);
}

//Comprobacion funcion trans_acele cmprobacion del parametro diferencia
TEST(trans_acelec, 1){
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
  ASSERT_EQ(diferencia , 0.06);
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
  ASSERT_EQ(0 , result );
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
  ASSERT_EQ(0 , result );
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
  ASSERT_EQ(0 , result );
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
  ASSERT_EQ(0 , result );
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
  ASSERT_EQ(0 , result );
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
  ASSERT_EQ(0 , result );
}

//Particula en cordenada x 0 que no interacciona
TEST(col_x,1){
  double const epsilon = 0.0000001;
  Particula particulas(1);
  particulas.pos_x[0] = 0.0;
  particulas.hv_x[0] = 0.0;
  particulas.vel_x[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.loc_x[0] = 0;
  calc::col_x(particulas,0);
  const double calculo = 0.0;
  int result = 0;
  if (fabs(calculo - particulas.acel_x[0]) >= epsilon){
    result = -1;
  }
  ASSERT_EQ(0, result);
}

//Particula en cordenada x 2(considerada num_bloque -1 en este test) que no interacciona
TEST(col_x,2){
  double const epsilon = 0.0000001;
  Particula particulas(1);
  particulas.pos_x[0] = 0.0;
  particulas.hv_x[0] = 0.0;
  particulas.vel_x[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.loc_x[0] = 2;
  calc::col_x(particulas,0);
  const double calculo = 0.0;
  int result = 0;
  if (fabs(calculo - particulas.acel_x[0]) >= epsilon){
    result = -1;
  }
  ASSERT_EQ(0, result);
}

//Particula fuera de la malla por vector pos_x negativo
TEST(col_x,3){
  double const epsilon = 0.0000000001;
  double const posicion = -0.07;
  Particula particulas(1);
  particulas.pos_x[0] = posicion;
  particulas.hv_x[0] = 0.0;
  particulas.vel_x[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.loc_x[0] = 0;
  calc::col_x(particulas,0);
  const double calculo = 156.0;
  int result = 0;
  if (fabs(calculo - particulas.acel_x[0]) >= epsilon){
    result = -1;
  }
  ASSERT_EQ(0, result);
}

//Particula fuera de la malla por vector pos_x positivo
TEST(col_x,4){
  double const epsilon = 0.0000000001;
  double const posicion = 0.08;
  Particula particulas(1);
  particulas.pos_x[0] = posicion;
  particulas.hv_x[0] = 0.0;
  particulas.vel_x[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.loc_x[0] = 2;
  calc::col_x(particulas,0);
  const double calculo = -456.0;
  int result = 0;
  if (fabs(calculo - particulas.acel_x[0]) >= epsilon){
    result = -1;
  }
  ASSERT_EQ(0, result);
}

//Particula en cordenada y 0 que no interacciona
TEST(col_y,1){
  double const epsilon = 0.0000001;
  Particula particulas(1);
  particulas.pos_y[0] = 0.0;
  particulas.hv_y[0] = 0.0;
  particulas.vel_y[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.loc_y[0] = 0;
  calc::col_y(particulas,0);
  const double calculo = 0.0;
  int result = 0;
  if (fabs(calculo - particulas.acel_y[0]) >= epsilon){
    result = -1;
  }
  ASSERT_EQ(0, result);
}

//Particula en cordenada y 2(considerada num_bloque -1 en este test) que no interacciona
TEST(col_y,2){
  double const epsilon = 0.0000001;
  Particula particulas(1);
  particulas.pos_y[0] = 0.0;
  particulas.hv_y[0] = 0.0;
  particulas.vel_y[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.loc_y[0] = 2;
  calc::col_y(particulas,0);
  const double calculo = 0.0;
  int result = 0;
  if (fabs(calculo - particulas.acel_y[0]) >= epsilon){
    result = -1;
  }
  ASSERT_EQ(0, result);
}

//Particula fuera de la malla por vector pos_x negativo
TEST(col_y,3){
  double const epsilon = 0.0000000001;
  double const posicion = -0.09;
  Particula particulas(1);
  particulas.pos_y[0] = posicion;
  particulas.hv_y[0] = 0.0;
  particulas.vel_y[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.loc_y[0] = 0;
  calc::col_y(particulas,0);
  const double calculo = 306.0;
  int result = 0;
  if (fabs(calculo - particulas.acel_y[0]) >= epsilon){
    result = -1;
  }
  ASSERT_EQ(0, result);
}

//Particula fuera de la malla por vector pos_x positivo
TEST(col_y,4){
  double const epsilon = 0.0000000001;
  double const posicion = 0.12;
  Particula particulas(1);
  particulas.pos_y[0] = posicion;
  particulas.hv_y[0] = 0.0;
  particulas.vel_y[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.loc_y[0] = 2;
  calc::col_y(particulas,0);
  const double calculo = -606.0;
  int result = 0;
  if (fabs(calculo - particulas.acel_y[0]) >= epsilon){
    result = -1;
  }
  ASSERT_EQ(0, result);
}

//Particula en cordenada z 0 que no interacciona
TEST(col_z,1){
  double const epsilon = 0.0000001;
  Particula particulas(1);
  particulas.pos_z[0] = 0.0;
  particulas.hv_z[0] = 0.0;
  particulas.vel_z[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  particulas.loc_z[0] = 0;
  calc::col_z(particulas,0);
  const double calculo = 0.0;
  int result = 0;
  if (fabs(calculo - particulas.acel_z[0]) >= epsilon){
    result = -1;
  }
  ASSERT_EQ(0, result);
}

//Particula en cordenada z 2(considerada num_bloque -1 en este test) que no interacciona
TEST(col_z,2){
  double const epsilon = 0.0000001;
  Particula particulas(1);
  particulas.pos_z[0] = 0.0;
  particulas.hv_z[0] = 0.0;
  particulas.vel_z[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  particulas.loc_z[0] = 2;
  calc::col_z(particulas,0);
  const double calculo = 0.0;
  int result = 0;
  if (fabs(calculo - particulas.acel_z[0]) >= epsilon){
    result = -1;
  }
  ASSERT_EQ(0, result);
}

//Particula fuera de la malla por vector pos_x negativo
TEST(col_z,3){
  double const epsilon = 0.0000000001;
  double const posicion = -0.07;
  Particula particulas(1);
  particulas.pos_z[0] = posicion;
  particulas.hv_z[0] = 0.0;
  particulas.vel_z[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  particulas.loc_z[0] = 0;
  calc::col_z(particulas,0);
  const double calculo = 156.0;
  int result = 0;
  if (fabs(calculo - particulas.acel_z[0]) >= epsilon){
    result = -1;
  }
  ASSERT_EQ(0, result);
}

//Particula fuera de la malla por vector pos_x positivo
TEST(col_z,4){
  double const epsilon = 0.0000000001;
  double const posicion = 0.08;
  Particula particulas(1);
  particulas.pos_z[0] = posicion;
  particulas.hv_z[0] = 0.0;
  particulas.vel_z[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  particulas.loc_z[0] = 2;
  calc::col_z(particulas,0);
  const double calculo = -456.0;
  int result = 0;
  if (fabs(calculo - particulas.acel_z[0]) >= epsilon){
    result = -1;
  }
  ASSERT_EQ(0, result);
}

//Comprobacion funcion mov_part, comprobacion pos_x[0]
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
  ASSERT_EQ(0 , result );
}

//Comprobacion funcion mov_part, comprobacion pos_y[0]
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
  ASSERT_EQ(0 , result );
}
//Comprobacion funcion mov_part, comprobacion pos_z[0]
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
  ASSERT_EQ(0 , result );
}
//Comprobacion funcion mov_part, comprobacion vel_x[0]
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
  ASSERT_EQ(1.0005 , particulas.vel_x[0]);
}
//Comprobacion funcion mov_part, comprobacion vel_y[0]
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
  ASSERT_EQ(1.0005 , particulas.vel_y[0]);
}
//Comprobacion funcion mov_part, comprobacion vel_z[0]
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
  ASSERT_EQ(1.0005 , particulas.vel_z[0]);
}
//Comprobacion funcion mov_part, comprobacion hv_x[0]
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
  ASSERT_EQ(1.001 , particulas.hv_x[0]);
}
//Comprobacion funcion mov_part, comprobacion hv_y[0]
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
  ASSERT_EQ(1.001 , particulas.hv_y[0]);
}
//Comprobacion funcion mov_part, comprobacion hv_z[0]
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
  ASSERT_EQ(1.001 , particulas.hv_z[0]);
}

//Particula en cordenada x 0 que no interacciona
TEST(int_x,1) {
  double const epsilon  = 0.0000001;
  double const posicion = 0.01;
  Particula particulas(1);
  particulas.pos_x[0] = posicion;
  particulas.hv_x[0]  = 0.0;
  particulas.vel_x[0] = 0.0;
  particulas.loc_x[0] = 0;
  calc::int_x(particulas, 0);
  const double calculo = 0.01;
  int result           = 0;
  if (fabs(calculo - particulas.pos_x[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada x 0 que interacciona, comprobacion pos_x
TEST(int_x,2) {
  double const epsilon  = 0.0000001;
  double const posicion = -0.07;
  Particula particulas(1);
  particulas.pos_x[0] = posicion;
  particulas.hv_x[0]  = 0.0;
  particulas.vel_x[0] = 0.0;
  particulas.loc_x[0] = 0;
  calc::int_x(particulas, 0);
  const double calculo = -0.06;
  int result           = 0;
  if (fabs(calculo - particulas.pos_x[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}



//Particula en cordenada x 0 que interacciona, comprobacion h_x
TEST(int_x,3) {
  double const epsilon  = 0.0000001;
  double const posicion = -0.07;
  Particula particulas(1);
  particulas.pos_x[0] = posicion;
  particulas.hv_x[0]  = 1;
  particulas.vel_x[0] = 0.0;
  particulas.loc_x[0] = 0;
  calc::int_x(particulas, 0);
  const double calculo = -1;
  int result           = 0;
  if (fabs(calculo - particulas.hv_x[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada x 0 que interacciona, comprobacion vel_x
TEST(int_x,4) {
  double const epsilon  = 0.0000001;
  double const posicion = -0.07;
  Particula particulas(1);
  particulas.pos_x[0] = posicion;
  particulas.hv_x[0]  = 0.0;
  particulas.vel_x[0] = 1;
  particulas.loc_x[0] = 0;
  calc::int_x(particulas, 0);
  const double calculo = -1;
  int result           = 0;
  if (fabs(calculo - particulas.vel_x[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada x=2(considerado num_bloque[0]-1) que interacciona, comprobacion pos_x
TEST(int_x,5) {
  double const epsilon  = 0.0000001;
  double const posicion = 0.08;
  Particula particulas(1);
  particulas.pos_x[0] = posicion;
  particulas.hv_x[0]  = 0.0;
  particulas.vel_x[0] = 0.0;
  particulas.loc_x[0] = 2;
  calc::int_x(particulas, 0);
  const double calculo = 0.05;
  int result           = 0;
  if (fabs(calculo - particulas.pos_x[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada y 0 que no interacciona
TEST(int_y,1) {
  double const epsilon  = 0.0000001;
  double const posicion = 0.01;
  Particula particulas(1);
  particulas.pos_y[0] = posicion;
  particulas.hv_y[0]  = 0.0;
  particulas.vel_y[0] = 0.0;
  particulas.loc_y[0] = 0;
  calc::int_y(particulas, 0);
  const double calculo = 0.01;
  int result           = 0;
  if (fabs(calculo - particulas.pos_y[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada y 0 que interacciona, comprobacion pos_y
TEST(int_y,2) {
  double const epsilon  = 0.0000001;
  double const posicion = -0.09;
  Particula particulas(1);
  particulas.pos_y[0] = posicion;
  particulas.hv_y[0]  = 0.0;
  particulas.vel_y[0] = 0.0;
  particulas.loc_y[0] = 0;
  calc::int_y(particulas, 0);
  const double calculo = -0.07;
  int result           = 0;
  if (fabs(calculo - particulas.pos_y[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada x 0 que interacciona, comprobacion h_y
TEST(int_y,3) {
  double const epsilon  = 0.0000001;
  double const posicion = -0.09;
  Particula particulas(1);
  particulas.pos_y[0] = posicion;
  particulas.hv_y[0]  = 1;
  particulas.vel_y[0] = 0.0;
  particulas.loc_y[0] = 0;
  calc::int_y(particulas, 0);
  const double calculo = -1;
  int result           = 0;
  if (fabs(calculo - particulas.hv_y[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada x 0 que interacciona, comprobacion vel_y
TEST(int_y,4) {
  double const epsilon  = 0.0000001;
  double const posicion = -0.09;
  Particula particulas(1);
  particulas.pos_y[0] = posicion;
  particulas.hv_y[0]  = 0.0;
  particulas.vel_y[0] = 1;
  particulas.loc_y[0] = 0;
  calc::int_y(particulas, 0);
  const double calculo = -1;
  int result           = 0;
  if (fabs(calculo - particulas.vel_y[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada y=2(considerado num_bloque[0]-1) que interacciona, comprobacion pos_y
TEST(int_y,5) {
  double const epsilon  = 0.0000001;
  double const posicion = 0.11;
  Particula particulas(1);
  particulas.pos_y[0] = posicion;
  particulas.hv_y[0]  = 0.0;
  particulas.vel_y[0] = 0.0;
  particulas.loc_y[0] = 2;
  calc::int_y(particulas, 0);
  const double calculo = 0.09;
  int result           = 0;
  if (fabs(calculo - particulas.pos_y[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada z 0 que no interacciona
TEST(int_z,1) {
  double const epsilon  = 0.0000001;
  double const posicion = 0.01;
  Particula particulas(1);
  particulas.pos_z[0] = posicion;
  particulas.hv_z[0]  = 0.0;
  particulas.vel_z[0] = 0.0;
  particulas.loc_z[0] = 0;
  calc::int_z(particulas, 0);
  const double calculo = 0.01;
  int result           = 0;
  if (fabs(calculo - particulas.pos_z[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada z=0 que interacciona, comprobacion pos_z
TEST(int_z,2) {
  double const epsilon  = 0.0000001;
  double const posicion = -0.07;
  Particula particulas(1);
  particulas.pos_z[0] = posicion;
  particulas.hv_z[0]  = 0.0;
  particulas.vel_z[0] = 0.0;
  particulas.loc_z[0] = 0;
  calc::int_z(particulas, 0);
  const double calculo = -0.06;
  int result           = 0;
  if (fabs(calculo - particulas.pos_z[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada z = 0 que interacciona, comprobacion h_z
TEST(int_z,3) {
  double const epsilon  = 0.0000001;
  double const posicion = -0.07;
  Particula particulas(1);
  particulas.pos_z[0] = posicion;
  particulas.hv_z[0]  = 1;
  particulas.vel_z[0] = 0.0;
  particulas.loc_z[0] = 0;
  calc::int_z(particulas, 0);
  const double calculo = -1;
  int result           = 0;
  if (fabs(calculo - particulas.hv_z[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada z = 0 que interacciona, comprobacion vel_z
TEST(int_z,4) {
  double const epsilon  = 0.0000001;
  double const posicion = -0.07;
  Particula particulas(1);
  particulas.pos_z[0] = posicion;
  particulas.hv_z[0]  = 0.0;
  particulas.vel_z[0] = 1;
  particulas.loc_z[0] = 0;
  calc::int_z(particulas, 0);
  const double calculo = -1;
  int result           = 0;
  if (fabs(calculo - particulas.vel_z[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}

//Particula en cordenada z=2(considerado num_bloque[0]-1) que interacciona, comprobacion pos_z
TEST(int_z,5) {
  double const epsilon  = 0.0000001;
  double const posicion = 0.08;
  Particula particulas(1);
  particulas.pos_z[0] = posicion;
  particulas.hv_z[0]  = 0.0;
  particulas.vel_z[0] = 0.0;
  particulas.loc_z[0] = 2;
  calc::int_z(particulas, 0);
  const double calculo = 0.05;
  int result           = 0;
  if (fabs(calculo - particulas.pos_z[0]) >= epsilon) { result = -1; }
  ASSERT_EQ(0, result);
}