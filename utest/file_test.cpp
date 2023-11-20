#include "sim/file.hpp"
#include "sim/grid.hpp"
#include "gtest/gtest.h"

//Comprobacion funcion lectura_cabecera, comprobacion nps
TEST(lectura_cabecera,1){
  //CREACION DEL FICHERO DE PRUEBA
  // Abrir el archivo en modo de escritura
  ofstream prueba_escritura;
  prueba_escritura.open("prueba_lc1.fld", ios::binary);
  const int nps_in = 10;
  const float ppm_in = 6.5;
  // Escribir el número en binario en el archivo
  auto aux_ppm = static_cast<float>(ppm_in);
  auto aux_nps = static_cast<int>(nps_in);
  prueba_escritura.write(ficheros::to_str(aux_ppm), sizeof(aux_ppm));
  prueba_escritura.write(ficheros::to_str(aux_nps), sizeof(aux_nps));
  // Cerrar el archivo
  prueba_escritura.close();
  //Cambiar el tipo de archivo de escritura a lectura para comprobar
  ifstream prueba_lectura("prueba_lc1.fld", ios::binary);
  int nps_out = 0 ;
  float ppm_out = 0.0;
  tie(nps_out, ppm_out) = ficheros::lectura_cabecera(prueba_lectura);
  if (remove("prueba_lc1.fld") == 0){EXPECT_EQ(10 ,nps_out);}
}

//Comprobacion funcion lectura_cabecera, comprobacion ppm
TEST(lectura_cabecera,2){
  //CREACION DEL FICHERO DE PRUEBA
  // Abrir el archivo en modo de escritura
  ofstream prueba_escritura;
  prueba_escritura.open("prueba_lc2.fld", ios::binary);
  const int nps_in = 10;
  const float ppm_in = 6.5;
  // Escribir el número en binario en el archivo
  auto aux_ppm = static_cast<float>(ppm_in);
  auto aux_nps = static_cast<int>(nps_in);
  prueba_escritura.write(ficheros::to_str(aux_ppm), sizeof(aux_ppm));
  prueba_escritura.write(ficheros::to_str(aux_nps), sizeof(aux_nps));
  // Cerrar el archivo
  prueba_escritura.close();
  //Cambiar el tipo de archivo de escritura a lectura para comprobar
  ifstream prueba_lectura("prueba_lc2.fld", ios::binary);
  int nps_out = 0 ;
  float ppm_out = 0.0;
  tie(nps_out, ppm_out) = ficheros::lectura_cabecera(prueba_lectura);
  if (remove("prueba_lc2.fld") == 0) {EXPECT_EQ(6.5 ,ppm_out);}
}

//Comprobacion funcion lectura_float_to_double
TEST(lectura_float_to_double,1){
  //CREACION DE ARCHIVO AUXILIAR
  ofstream prueba_escritura;
  prueba_escritura.open("prueba_lftd.fld", ios::binary);
  const float num1 = 3.5;
  auto aux_num1 = static_cast<float>(num1);
  prueba_escritura.write(ficheros::to_str(aux_num1), sizeof(aux_num1));
  prueba_escritura.close();
  //Cambiar el tipo de archivo de escritura a lectura para comprobar
  ifstream prueba_lectura;
  prueba_lectura.open("prueba_lftd.fld", ios::binary);
  const double result = ficheros::lectura_float_to_double(prueba_lectura);
  if (remove("prueba_lftd.fld") == 0) {EXPECT_EQ(3.5 , result);}
}

//Comprobacion funcion lectura_file, comprobacion pos_x
TEST(lectura_file,1){
  //CREACION DEL ARCHIVO AUXILIAR CON PARAMETROS PARA LA PARTICULA DEL 1 AL 9 (ver en file.cpp)
  ficheros::archivo_creacion();
  const int numpar = 1;
  Particula particulas(numpar);
  particulas.pos_x[0] = 0.0;
  particulas.pos_y[0] = 0.0;
  particulas.pos_z[0] = 0.0;
  particulas.hv_x[0] = 0.0;
  particulas.hv_y[0] = 0.0;
  particulas.hv_z[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  ifstream archivo_prueba;
  archivo_prueba.open("prueba_lf.fld", ios::binary);
  ficheros::lectura_file(archivo_prueba, numpar, particulas);
  if (remove("prueba_lf.fld") == 0) {EXPECT_EQ(1.5 ,particulas.pos_x[0]);}
}

//Comprobacion funcion lectura_file, comprobacion pos_y
TEST(lectura_file,2){
  //CREACION DEL ARCHIVO AUXILIAR CON PARAMETROS PARA LA PARTICULA DEL 1 AL 9 (ver en file.cpp)
  ficheros::archivo_creacion();
  const int numpar =1;
  Particula particulas(numpar);
  particulas.pos_x[0] = 0.0;
  particulas.pos_y[0] = 0.0;
  particulas.pos_z[0] = 0.0;
  particulas.hv_x[0] = 0.0;
  particulas.hv_y[0] = 0.0;
  particulas.hv_z[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  ifstream archivo_prueba;
  archivo_prueba.open("prueba_lf.fld", ios::binary);
  ficheros::lectura_file(archivo_prueba, numpar, particulas);
  if (remove("prueba_lf.fld") == 0) {EXPECT_EQ(2.5 ,particulas.pos_y[0]);}
}

//Comprobacion funcion lectura_file, comprobacion pos_z
TEST(lectura_file,3){
  //CREACION DEL ARCHIVO AUXILIAR CON PARAMETROS PARA LA PARTICULA DEL 1 AL 9 (ver en file.cpp)
  ficheros::archivo_creacion();
  const int numpar =1;
  Particula particulas(numpar);
  particulas.pos_x[0] = 0.0;
  particulas.pos_y[0] = 0.0;
  particulas.pos_z[0] = 0.0;
  particulas.hv_x[0] = 0.0;
  particulas.hv_y[0] = 0.0;
  particulas.hv_z[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  ifstream archivo_prueba;
  archivo_prueba.open("prueba_lf.fld", ios::binary);
  ficheros::lectura_file(archivo_prueba, numpar, particulas);
  if (remove("prueba_lf.fld") == 0) {EXPECT_EQ(3.5 ,particulas.pos_z[0]);}
}

//Comprobacion funcion lectura_file, comprobacion hv_x
TEST(lectura_file,4){
  //CREACION DEL ARCHIVO AUXILIAR CON PARAMETROS PARA LA PARTICULA DEL 1 AL 9 (ver en file.cpp)
  ficheros::archivo_creacion();
  const int numpar =1;
  Particula particulas(numpar);
  particulas.pos_x[0] = 0.0;
  particulas.pos_y[0] = 0.0;
  particulas.pos_z[0] = 0.0;
  particulas.hv_x[0] = 0.0;
  particulas.hv_y[0] = 0.0;
  particulas.hv_z[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  ifstream archivo_prueba;
  archivo_prueba.open("prueba_lf.fld", ios::binary);
  ficheros::lectura_file(archivo_prueba, numpar, particulas);
  if (remove("prueba_lf.fld") == 0) {EXPECT_EQ(4.5 ,particulas.hv_x[0]);}
}

//Comprobacion funcion lectura_file, comprobacion hv_y
TEST(lectura_file,5){
  //CREACION DEL ARCHIVO AUXILIAR CON PARAMETROS PARA LA PARTICULA DEL 1 AL 9 (ver en file.cpp)
  ficheros::archivo_creacion();
  const int numpar =1;
  Particula particulas(numpar);
  particulas.pos_x[0] = 0.0;
  particulas.pos_y[0] = 0.0;
  particulas.pos_z[0] = 0.0;
  particulas.hv_x[0] = 0.0;
  particulas.hv_y[0] = 0.0;
  particulas.hv_z[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  ifstream archivo_prueba;
  archivo_prueba.open("prueba_lf.fld", ios::binary);
  ficheros::lectura_file(archivo_prueba, numpar, particulas);
  if (remove("prueba_lf.fld") == 0) {EXPECT_EQ(5.5 ,particulas.hv_y[0]);}
}

//Comprobacion funcion lectura_file, comprobacion hv_z
TEST(lectura_file,6){
  //CREACION DEL ARCHIVO AUXILIAR CON PARAMETROS PARA LA PARTICULA DEL 1 AL 9 (ver en file.cpp)
  ficheros::archivo_creacion();
  const int numpar =1;
  Particula particulas(numpar);
  particulas.pos_x[0] = 0.0;
  particulas.pos_y[0] = 0.0;
  particulas.pos_z[0] = 0.0;
  particulas.hv_x[0] = 0.0;
  particulas.hv_y[0] = 0.0;
  particulas.hv_z[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  ifstream archivo_prueba;
  archivo_prueba.open("prueba_lf.fld", ios::binary);
  ficheros::lectura_file(archivo_prueba, numpar, particulas);
  if (remove("prueba_lf.fld") == 0) {EXPECT_EQ(6.5 ,particulas.hv_z[0]);}
}

//Comprobacion funcion lectura_file, comprobacion vel_x
TEST(lectura_file,7){
  //CREACION DEL ARCHIVO AUXILIAR CON PARAMETROS PARA LA PARTICULA DEL 1 AL 9 (ver en file.cpp)
  ficheros::archivo_creacion();
  const int numpar =1;
  Particula particulas(numpar);
  particulas.pos_x[0] = 0.0;
  particulas.pos_y[0] = 0.0;
  particulas.pos_z[0] = 0.0;
  particulas.hv_x[0] = 0.0;
  particulas.hv_y[0] = 0.0;
  particulas.hv_z[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  ifstream archivo_prueba;
  archivo_prueba.open("prueba_lf.fld", ios::binary);
  ficheros::lectura_file(archivo_prueba, numpar, particulas);
  if (remove("prueba_lf.fld") == 0) {EXPECT_EQ(7.5 ,particulas.vel_x[0]);}
}

//Comprobacion funcion lectura_file, comprobacion vel_y
TEST(lectura_file,8){
  //CREACION DEL ARCHIVO AUXILIAR CON PARAMETROS PARA LA PARTICULA DEL 1 AL 9 (ver en file.cpp)
  ficheros::archivo_creacion();
  const int numpar =1;
  Particula particulas(numpar);
  particulas.pos_x[0] = 0.0;
  particulas.pos_y[0] = 0.0;
  particulas.pos_z[0] = 0.0;
  particulas.hv_x[0] = 0.0;
  particulas.hv_y[0] = 0.0;
  particulas.hv_z[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  ifstream archivo_prueba;
  archivo_prueba.open("prueba_lf.fld", ios::binary);
  ficheros::lectura_file(archivo_prueba, numpar, particulas);
  if (remove("prueba_lf.fld") == 0) {EXPECT_EQ(8.5 ,particulas.vel_y[0]);}
}

//Comprobacion funcion lectura_file, comprobacion vel_z
TEST(lectura_file,9){
  //CREACION DEL ARCHIVO AUXILIAR CON PARAMETROS PARA LA PARTICULA DEL 1 AL 9 (ver en file.cpp)
  ficheros::archivo_creacion();
  const int numpar =1;
  Particula particulas(numpar);
  particulas.pos_x[0] = 0.0;
  particulas.pos_y[0] = 0.0;
  particulas.pos_z[0] = 0.0;
  particulas.hv_x[0] = 0.0;
  particulas.hv_y[0] = 0.0;
  particulas.hv_z[0] = 0.0;
  particulas.acel_x[0] = 0.0;
  particulas.acel_y[0] = 0.0;
  particulas.acel_z[0] = 0.0;
  ifstream archivo_prueba;
  archivo_prueba.open("prueba_lf.fld", ios::binary);
  ficheros::lectura_file(archivo_prueba, numpar, particulas);
  if (remove("prueba_lf.fld") == 0) {EXPECT_EQ(9.5 ,particulas.vel_z[0]);}
}

//Comprobacion funcion escritura_salida, comprobacion ppm
TEST(escritura_salida,1){
  ofstream file_vacio;
  const double num1 = 10.5;
  const double num2 = 11.5;
  const double num3 = 12.5;
  const double num4 = 13.5;
  const double num5 = 14.5;
  const double num6 = 15.5;
  const double num7 = 16.5;
  const double num8 = 17.5;
  const double num9 = 18.5;
  const double ppm = 0.0;
  double ppm2 = num7;
  //double const epsilon = 0.00001;
  Particula particulas(1);
  particulas.pos_x[0] = num1;
  particulas.pos_y[0] = num2;
  particulas.pos_z[0] = num3;
  particulas.hv_x[0] = num4;
  particulas.hv_y[0] = num5;
  particulas.hv_z[0] = num6;
  particulas.vel_x[0] = num7;
  particulas.vel_y[0] = num8;
  particulas.vel_z[0] = num9;
  file_vacio.open("prueba_es1.fld", ios::binary);
  ficheros::escritura_salida(file_vacio, particulas, ppm2, 1);
  file_vacio.close();
  //FICHERO ESCRITO
  ifstream fichero_comprobacion;
  fichero_comprobacion.open("prueba_es1.fld", ios::binary);
  auto ppm_tmp = static_cast<float>(ppm);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&ppm_tmp), sizeof(float));
  if (remove("prueba_es1.fld") == 0) {EXPECT_EQ(16.5, ppm_tmp);}
}


//Comprobacion funcion escritura_salida, comprobacion np
TEST(escritura_salida,2){
  ofstream file_vacio;
  const double num1 = 10.5;
  const double num2 = 11.5;
  const double num3 = 12.5;
  const double num4 = 13.5;
  const double num5 = 14.5;
  const double num6 = 15.5;
  const double num7 = 16.5;
  const double num8 = 17.5;
  const double num9 = 18.5;
  double ppm = num7;
  const int nps = 4;
  Particula particulas(nps);
  particulas.pos_x[0] = num1;
  particulas.pos_y[0] = num2;
  particulas.pos_z[0] = num3;
  particulas.hv_x[0] = num4;
  particulas.hv_y[0] = num5;
  particulas.hv_z[0] = num6;
  particulas.vel_x[0] = num7;
  particulas.vel_y[0] = num8;
  particulas.vel_z[0] = num9;
  file_vacio.open("prueba_es.fld", ios::binary);
  ficheros::escritura_salida(file_vacio, particulas, ppm, nps);
  file_vacio.close();
  //FICHERO ESCRITO
  ifstream fichero_comprobacion;
  fichero_comprobacion.open("prueba_es.fld", ios::binary);
  auto ppm_tmp = static_cast<float>(ppm);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&ppm_tmp), sizeof(float));
  int nps_tmp = static_cast<int>(nps);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&nps_tmp), sizeof(int));
  if (remove("prueba_es.fld") == 0) {EXPECT_EQ(4, nps_tmp);}
}

//Comprobacion funcion escritura_salida, comprobacion pos_x
TEST(escritura_salida,3){
  ofstream file_vacio;
  const double num1 = 10.5;
  const double num2 = 11.5;
  const double num3 = 12.5;
  const double num4 = 13.5;
  const double num5 = 14.5;
  const double num6 = 15.5;
  const double num7 = 16.5;
  const double num8 = 17.5;
  const double num9 = 18.5;
  double ppm = num7;
  const int nps = 4;
  Particula particulas(nps);
  particulas.pos_x[0] = num1;
  particulas.pos_y[0] = num2;
  particulas.pos_z[0] = num3;
  particulas.hv_x[0] = num4;
  particulas.hv_y[0] = num5;
  particulas.hv_z[0] = num6;
  particulas.vel_x[0] = num7;
  particulas.vel_y[0] = num8;
  particulas.vel_z[0] = num9;
  file_vacio.open("prueba_es.fld", ios::binary);
  ficheros::escritura_salida(file_vacio, particulas, ppm, nps);
  file_vacio.close();
  //FICHERO ESCRITO
  ifstream fichero_comprobacion;
  fichero_comprobacion.open("prueba_es.fld", ios::binary);
  auto ppm_tmp = static_cast<float>(ppm);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&ppm_tmp), sizeof(float));
  int nps_tmp = static_cast<int>(nps);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&nps_tmp), sizeof(int));
  particulas.pos_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  if (remove("prueba_es.fld") == 0) {EXPECT_EQ(10.5 ,particulas.pos_x[0]);}
}

//Comprobacion funcion escritura_salida, comprobacion pos_y
TEST(escritura_salida,4){
  ofstream file_vacio;
  const double num1 = 10.5;
  const double num2 = 11.5;
  const double num3 = 12.5;
  const double num4 = 13.5;
  const double num5 = 14.5;
  const double num6 = 15.5;
  const double num7 = 16.5;
  const double num8 = 17.5;
  const double num9 = 18.5;
  double ppm = num7;
  const int nps = 1;
  Particula particulas(nps);
  particulas.pos_x[0] = num1;
  particulas.pos_y[0] = num2;
  particulas.pos_z[0] = num3;
  particulas.hv_x[0] = num4;
  particulas.hv_y[0] = num5;
  particulas.hv_z[0] = num6;
  particulas.vel_x[0] = num7;
  particulas.vel_y[0] = num8;
  particulas.vel_z[0] = num9;
  file_vacio.open("prueba_es.fld", ios::binary);
  ficheros::escritura_salida(file_vacio, particulas, ppm, nps);
  file_vacio.close();
  //FICHERO ESCRITO
  ifstream fichero_comprobacion;
  fichero_comprobacion.open("prueba_es.fld", ios::binary);
  auto ppm_tmp = static_cast<float>(ppm);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&ppm_tmp), sizeof(float));
  int nps_tmp = static_cast<int>(nps);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&nps_tmp), sizeof(int));
  particulas.pos_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  if (remove("prueba_es.fld") == 0) {EXPECT_EQ(11.5 ,particulas.pos_y[0] );}
}

//Comprobacion funcion escritura_salida, comprobacion pos_z
TEST(escritura_salida,5){
  ofstream file_vacio;
  const double num1 = 10.5;
  const double num2 = 11.5;
  const double num3 = 12.5;
  const double num4 = 13.5;
  const double num5 = 14.5;
  const double num6 = 15.5;
  const double num7 = 16.5;
  const double num8 = 17.5;
  const double num9 = 18.5;
  double ppm = num7;
  const int nps = 1;
  Particula particulas(nps);
  particulas.pos_x[0] = num1;
  particulas.pos_y[0] = num2;
  particulas.pos_z[0] = num3;
  particulas.hv_x[0] = num4;
  particulas.hv_y[0] = num5;
  particulas.hv_z[0] = num6;
  particulas.vel_x[0] = num7;
  particulas.vel_y[0] = num8;
  particulas.vel_z[0] = num9;
  file_vacio.open("prueba_es.fld", ios::binary);
  ficheros::escritura_salida(file_vacio, particulas, ppm, nps);
  file_vacio.close();
  //FICHERO ESCRITO
  ifstream fichero_comprobacion;
  fichero_comprobacion.open("prueba_es.fld", ios::binary);
  auto ppm_tmp = static_cast<float>(ppm);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&ppm_tmp), sizeof(float));
  int nps_tmp = static_cast<int>(nps);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&nps_tmp), sizeof(int));
  particulas.pos_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_z[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  if (remove("prueba_es.fld") == 0) {EXPECT_EQ(12.5 ,particulas.pos_z[0]);}
}

//Comprobacion funcion escritura_salida, comprobacion hv_x
TEST(escritura_salida,6){
  ofstream file_vacio;
  const double num1 = 10.5;
  const double num2 = 11.5;
  const double num3 = 12.5;
  const double num4 = 13.5;
  const double num5 = 14.5;
  const double num6 = 15.5;
  const double num7 = 16.5;
  const double num8 = 17.5;
  const double num9 = 18.5;
  double ppm = num7;
  const int nps = 1;
  Particula particulas(nps);
  particulas.pos_x[0] = num1;
  particulas.pos_y[0] = num2;
  particulas.pos_z[0] = num3;
  particulas.hv_x[0] = num4;
  particulas.hv_y[0] = num5;
  particulas.hv_z[0] = num6;
  particulas.vel_x[0] = num7;
  particulas.vel_y[0] = num8;
  particulas.vel_z[0] = num9;
  file_vacio.open("prueba_es.fld", ios::binary);
  ficheros::escritura_salida(file_vacio, particulas, ppm, nps);
  file_vacio.close();
  //FICHERO ESCRITO
  ifstream fichero_comprobacion;
  fichero_comprobacion.open("prueba_es.fld", ios::binary);
  auto ppm_tmp = static_cast<float>(ppm);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&ppm_tmp), sizeof(float));
  int nps_tmp = static_cast<int>(nps);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&nps_tmp), sizeof(int));
  particulas.pos_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_z[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  if (remove("prueba_es.fld") == 0) {EXPECT_EQ(13.5 ,particulas.hv_x[0] );}
}

//Comprobacion funcion escritura_salida, comprobacion hv_y
TEST(escritura_salida,7){
  ofstream file_vacio;
  const double num1 = 10.5;
  const double num2 = 11.5;
  const double num3 = 12.5;
  const double num4 = 13.5;
  const double num5 = 14.5;
  const double num6 = 15.5;
  const double num7 = 16.5;
  const double num8 = 17.5;
  const double num9 = 18.5;
  double ppm = num7;
  const int nps = 1;
  Particula particulas(nps);
  particulas.pos_x[0] = num1;
  particulas.pos_y[0] = num2;
  particulas.pos_z[0] = num3;
  particulas.hv_x[0] = num4;
  particulas.hv_y[0] = num5;
  particulas.hv_z[0] = num6;
  particulas.vel_x[0] = num7;
  particulas.vel_y[0] = num8;
  particulas.vel_z[0] = num9;
  file_vacio.open("prueba_es.fld", ios::binary);
  ficheros::escritura_salida(file_vacio, particulas, ppm, nps);
  file_vacio.close();
  //FICHERO ESCRITO
  ifstream fichero_comprobacion;
  fichero_comprobacion.open("prueba_es.fld", ios::binary);
  auto ppm_tmp = static_cast<float>(ppm);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&ppm_tmp), sizeof(float));
  int nps_tmp = static_cast<int>(nps);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&nps_tmp), sizeof(int));
  particulas.pos_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_z[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  if (remove("prueba_es.fld") == 0) {EXPECT_EQ(14.5 ,particulas.hv_y[0] );}
}

//Comprobacion funcion escritura_salida, comprobacion hv_z
TEST(escritura_salida,8){
  ofstream file_vacio;
  const double num1 = 10.5;
  const double num2 = 11.5;
  const double num3 = 12.5;
  const double num4 = 13.5;
  const double num5 = 14.5;
  const double num6 = 15.5;
  const double num7 = 16.5;
  const double num8 = 17.5;
  const double num9 = 18.5;
  double ppm = num7;
  const int nps = 1;
  Particula particulas(nps);
  particulas.pos_x[0] = num1;
  particulas.pos_y[0] = num2;
  particulas.pos_z[0] = num3;
  particulas.hv_x[0] = num4;
  particulas.hv_y[0] = num5;
  particulas.hv_z[0] = num6;
  particulas.vel_x[0] = num7;
  particulas.vel_y[0] = num8;
  particulas.vel_z[0] = num9;
  file_vacio.open("prueba_es.fld", ios::binary);
  ficheros::escritura_salida(file_vacio, particulas, ppm, nps);
  file_vacio.close();
  //FICHERO ESCRITO
  ifstream fichero_comprobacion;
  fichero_comprobacion.open("prueba_es.fld", ios::binary);
  auto ppm_tmp = static_cast<float>(ppm);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&ppm_tmp), sizeof(float));
  int nps_tmp = static_cast<int>(nps);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&nps_tmp), sizeof(int));
  particulas.pos_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_z[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_z[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  if (remove("prueba_es.fld") == 0) {EXPECT_EQ(15.5 ,particulas.hv_z[0] );}
}

//Comprobacion funcion escritura_salida, comprobacion vel_x
TEST(escritura_salida,9){
  ofstream file_vacio;
  const double num1 = 10.5;
  const double num2 = 11.5;
  const double num3 = 12.5;
  const double num4 = 13.5;
  const double num5 = 14.5;
  const double num6 = 15.5;
  const double num7 = 16.5;
  const double num8 = 17.5;
  const double num9 = 18.5;
  double ppm = num7;
  const int nps = 1;
  Particula particulas(nps);
  particulas.pos_x[0] = num1;
  particulas.pos_y[0] = num2;
  particulas.pos_z[0] = num3;
  particulas.hv_x[0] = num4;
  particulas.hv_y[0] = num5;
  particulas.hv_z[0] = num6;
  particulas.vel_x[0] = num7;
  particulas.vel_y[0] = num8;
  particulas.vel_z[0] = num9;
  file_vacio.open("prueba_es.fld", ios::binary);
  ficheros::escritura_salida(file_vacio, particulas, ppm, nps);
  file_vacio.close();
  //FICHERO ESCRITO
  ifstream fichero_comprobacion;
  fichero_comprobacion.open("prueba_es.fld", ios::binary);
  auto ppm_tmp = static_cast<float>(ppm);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&ppm_tmp), sizeof(float));
  int nps_tmp = static_cast<int>(nps);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&nps_tmp), sizeof(int));
  particulas.pos_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_z[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_z[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.vel_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  if (remove("prueba_es.fld") == 0) {EXPECT_EQ(16.5 ,particulas.vel_x[0]);}
}

//Comprobacion funcion escritura_salida, comprobacion vel_y
TEST(escritura_salida,10){
  ofstream file_vacio;
  const double num1 = 10.5;
  const double num2 = 11.5;
  const double num3 = 12.5;
  const double num4 = 13.5;
  const double num5 = 14.5;
  const double num6 = 15.5;
  const double num7 = 16.5;
  const double num8 = 17.5;
  const double num9 = 18.5;
  double ppm = num7;
  const int nps = 1;
  Particula particulas(nps);
  particulas.pos_x[0] = num1;
  particulas.pos_y[0] = num2;
  particulas.pos_z[0] = num3;
  particulas.hv_x[0] = num4;
  particulas.hv_y[0] = num5;
  particulas.hv_z[0] = num6;
  particulas.vel_x[0] = num7;
  particulas.vel_y[0] = num8;
  particulas.vel_z[0] = num9;
  file_vacio.open("prueba_es.fld", ios::binary);
  ficheros::escritura_salida(file_vacio, particulas, ppm, nps);
  file_vacio.close();
  //FICHERO ESCRITO
  ifstream fichero_comprobacion;
  fichero_comprobacion.open("prueba_es.fld", ios::binary);
  auto ppm_tmp = static_cast<float>(ppm);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&ppm_tmp), sizeof(float));
  int nps_tmp = static_cast<int>(nps);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&nps_tmp), sizeof(int));
  particulas.pos_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_z[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_z[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.vel_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.vel_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  if (remove("prueba_es.fld") == 0) {EXPECT_EQ(17.5 ,particulas.vel_y[0] );}
}

//Comprobacion funcion escritura_salida, comprobacion vel_z
TEST(escritura_salida,11){
  ofstream file_vacio;
  const double num1 = 10.5;
  const double num2 = 11.5;
  const double num3 = 12.5;
  const double num4 = 13.5;
  const double num5 = 14.5;
  const double num6 = 15.5;
  const double num7 = 16.5;
  const double num8 = 17.5;
  const double num9 = 18.5;
  double ppm = num7;
  const int nps = 1;
  Particula particulas(nps);
  particulas.pos_x[0] = num1;
  particulas.pos_y[0] = num2;
  particulas.pos_z[0] = num3;
  particulas.hv_x[0] = num4;
  particulas.hv_y[0] = num5;
  particulas.hv_z[0] = num6;
  particulas.vel_x[0] = num7;
  particulas.vel_y[0] = num8;
  particulas.vel_z[0] = num9;
  file_vacio.open("prueba_es.fld", ios::binary);
  ficheros::escritura_salida(file_vacio, particulas, ppm, nps);
  file_vacio.close();
  //FICHERO ESCRITO
  ifstream fichero_comprobacion;
  fichero_comprobacion.open("prueba_es.fld", ios::binary);
  auto ppm_tmp = static_cast<float>(ppm);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&ppm_tmp), sizeof(float));
  int nps_tmp = static_cast<int>(nps);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  fichero_comprobacion.read(reinterpret_cast<char *>(&nps_tmp), sizeof(int));
  particulas.pos_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.pos_z[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.hv_z[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.vel_x[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.vel_y[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  particulas.vel_z[0]  = ficheros::lectura_float_to_double(fichero_comprobacion);
  if (remove("prueba_es.fld") == 0) {EXPECT_EQ(18.5,particulas.vel_z[0]);}
}