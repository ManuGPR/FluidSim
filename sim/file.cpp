#include "file.hpp"

using namespace std;

namespace ficheros {
  //Funciones inline auxiliares para evitar el error de reinterpret cast del clang-tidy
  inline void read_value(std::istream & is, float & value) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    is.read(reinterpret_cast<char *>(&value), sizeof(value));
  }

  inline void read_value(std::istream & is, int & value) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    is.read(reinterpret_cast<char *>(&value), sizeof(value));
  }

  // Función que se encarga de leer la cabecera
  tuple<int, double> lectura_cabecera(ifstream & file_in) {
    const int menos_cinco = -5; //Evitan el error de clang-tidy de magic number
    const double cinco_punto_cero = 5.0;
    tuple<int, double> bad_return = {menos_cinco, cinco_punto_cero}; //Crea la tupla de error
    int nps                 = 0;
    float ppm               = 0.0;
    read_value(file_in, ppm);
    read_value(file_in, nps);
    // Comprobación del nps
    if (entry::check_np(nps) != 0) { return bad_return; }
    tuple<int, double> good_return = {nps, static_cast<double>(ppm)};
    return good_return;
  }

  // Función que se encarga de leer un objeto del fichero, hacer el cast a double y devolverlo
  double lectura_float_to_double(ifstream & fichero) {
    float aux_float = 0.0;
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    fichero.read(reinterpret_cast<char *>(&aux_float), sizeof(float));
    return static_cast<double>(aux_float);
  }

  int lectura_file(ifstream & file_in, int np, struct Particula & particulas) {
    int const bad_return = -5;
    int np_real          = 0;
    //Bucle que se encarga de leer el fichero
    while (!file_in.eof()) {
      particulas.pos_x[np_real]  = lectura_float_to_double(file_in);
      particulas.pos_y[np_real]  = lectura_float_to_double(file_in);
      particulas.pos_z[np_real]  = lectura_float_to_double(file_in);
      particulas.hv_x[np_real]   = lectura_float_to_double(file_in);
      particulas.hv_y[np_real]   = lectura_float_to_double(file_in);
      particulas.hv_z[np_real]   = lectura_float_to_double(file_in);
      particulas.vel_x[np_real]  = lectura_float_to_double(file_in);
      particulas.vel_y[np_real]  = lectura_float_to_double(file_in);
      particulas.vel_z[np_real]  = lectura_float_to_double(file_in);
      particulas.acel_x[np_real] = gravedad_x;
      particulas.acel_y[np_real] = gravedad_y;
      particulas.acel_z[np_real] = gravedad_z;
      np_real++;
    }
    //Si no hay el mismo número de partículas que dice la cabecera
    if (np_real - 1 != np) {
      cerr << " Number of particles mismatch. Header: " << np << ", Found:" << np_real - 1 << "\n";
      return bad_return;
    }
    return 0;
  }

  // Función que se encarga de la escritura del fichero de salida
  int escritura_salida(ofstream & file_out, const struct Particula & particulas, double & ppm,
                       int np) {
    auto aux = static_cast<float>(ppm);
    file_out.write(to_str(aux), sizeof(float));
    file_out.write(to_str(np), sizeof(int));
    for (int i = 0; i < np; i++) {
      aux = static_cast<float>(particulas.pos_x[i]);
      file_out.write(to_str(aux), sizeof(float));
      aux = static_cast<float>(particulas.pos_y[i]);
      file_out.write(to_str((aux)), sizeof(float));
      aux = static_cast<float>(particulas.pos_z[i]);
      file_out.write(to_str(aux), sizeof(float));
      aux = static_cast<float>(particulas.hv_x[i]);
      file_out.write(to_str(aux), sizeof(float));
      aux = static_cast<float>(particulas.hv_y[i]);
      file_out.write(to_str(aux), sizeof(float));
      aux = static_cast<float>(particulas.hv_z[i]);
      file_out.write(to_str(aux), sizeof(float));
      aux = static_cast<float>(particulas.vel_x[i]);
      file_out.write(to_str(aux), sizeof(float));
      aux = static_cast<float>(particulas.vel_y[i]);
      file_out.write(to_str(aux), sizeof(float));
      aux = static_cast<float>(particulas.vel_z[i]);
      file_out.write(to_str(aux), sizeof(float));
    }
    return 0;
  }

  // Función con overloading que castea un entero a un char*
  char const * to_str(int & parameter) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    char const * value = reinterpret_cast<char const *>(&parameter);
    return value;
  }

  char const * to_str(float & parameter) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    char const * value = reinterpret_cast<char const *>(&parameter);
    return value;
  }

  //------------FUNCIONES AUXILIARES PARA LOS TEST FUNCIONALES---------------
  // Función que compara dos ficheros (usada en los test)
  int comparar_ficheros(ifstream & file_in, ifstream & file_corect) {
    const int nps_1         = 0;
    const float ppm_float_1 = 0.0;
    const int nps_2         = 0;
    const float ppm_float_2 = 0.0;
    auto ppm1 = static_cast<float>(ppm_float_1);
    read_value(file_in, ppm1);
    int nps1 = static_cast<int>(nps_1);
    read_value(file_in, nps1);
    auto ppm2 = static_cast<float>(ppm_float_2);
    read_value(file_corect, ppm2);
    int nps2 = static_cast<int>(nps_2);
    read_value(file_corect, nps2);
    if (nps1 != nps2 or ppm1 != ppm2) { return -1; }
    const float aux_float_1 = 0.0;
    const float aux_float_2 = 0.0;
    while (!file_corect.eof()) {
      auto aux1 = static_cast<float>(aux_float_1);
      read_value(file_in, aux1);
      auto aux2 = static_cast<float>(aux_float_2);
      read_value(file_corect, aux2);
      if (aux1 != aux2) { return -1; }
    }
    return 0;
  }

  //------------FUNCIONES AUXILIARES PARA LOS TEST UNITARIOS----------------
  //Las funciones para los unitest hemos decidido que no pasen el clang-tidy
  // ya que aumentaría la complejidad de la lectura del código al tener que dividir muchas funciones
  //NOLINTBEGIN
  vector<float> vector_creacion() {
   vector<float> vec;
   float sum = 1.0;
   for (int i = 0; i <= 2*2*2; i++) {
      vec.push_back(sum + static_cast<float>(1.0/2));
      sum++;
   }
   return vec;
  }

  void archivo_creacion() {
    vector<float> parametros = vector_creacion();
    ofstream prueba_escritura;
    prueba_escritura.open("prueba_lf.fld", ios::binary);
    auto aux = static_cast<float>(parametros[0]);
    prueba_escritura.write(ficheros::to_str(aux), sizeof(float));
    auto aux2 = static_cast<float>(parametros[1]);
    prueba_escritura.write(ficheros::to_str(aux2), sizeof(float));
    auto aux3 = static_cast<float>(parametros[2]);
    prueba_escritura.write(ficheros::to_str(aux3), sizeof(float));
    auto aux4 = static_cast<float>(parametros[3]);
    prueba_escritura.write(ficheros::to_str(aux4), sizeof(float));
    auto aux5 = static_cast<float>(parametros[4]);
    prueba_escritura.write(ficheros::to_str(aux5), sizeof(float));
    auto aux6 = static_cast<float>(parametros[5]);
    prueba_escritura.write(ficheros::to_str(aux6), sizeof(float));
    auto aux7 = static_cast<float>(parametros[6]);
    prueba_escritura.write(ficheros::to_str(aux7), sizeof(float));
    auto aux8 = static_cast<float>(parametros[7]);
    prueba_escritura.write(ficheros::to_str(aux8), sizeof(float));
    auto aux9 = static_cast<float>(parametros[8]);
    prueba_escritura.write(ficheros::to_str(aux9), sizeof(float));
    prueba_escritura.close();
    parametros.clear();
  }

  void archivo_creacion_entero(int nps_in) {
    ofstream prueba_escritura;
    prueba_escritura.open("prueba_escr.fld", ios::binary);
    float const ppm_in = 6.5;
    // Escribir el número en binario en el archivo
    auto aux_ppm = static_cast<float>(ppm_in);
    auto aux_nps = static_cast<int>(nps_in);
    prueba_escritura.write(ficheros::to_str(aux_ppm), sizeof(aux_ppm));
    prueba_escritura.write(ficheros::to_str(aux_nps), sizeof(aux_nps));
    vector<float> parametros = vector_creacion();
    for (int i = 0; i < 2; i++) {
      auto aux = static_cast<float>(parametros[0]);
      prueba_escritura.write(ficheros::to_str(aux), sizeof(float));
      auto aux2 = static_cast<float>(parametros[1]);
      prueba_escritura.write(ficheros::to_str(aux2), sizeof(float));
      auto aux3 = static_cast<float>(parametros[2]);
      prueba_escritura.write(ficheros::to_str(aux3), sizeof(float));
      auto aux4 = static_cast<float>(parametros[3]);
      prueba_escritura.write(ficheros::to_str(aux4), sizeof(float));
      auto aux5 = static_cast<float>(parametros[4]);
      prueba_escritura.write(ficheros::to_str(aux5), sizeof(float));
      auto aux6 = static_cast<float>(parametros[5]);
      prueba_escritura.write(ficheros::to_str(aux6), sizeof(float));
      auto aux7 = static_cast<float>(parametros[6]);
      prueba_escritura.write(ficheros::to_str(aux7), sizeof(float));
      auto aux8 = static_cast<float>(parametros[7]);
      prueba_escritura.write(ficheros::to_str(aux8), sizeof(float));
      auto aux9 = static_cast<float>(parametros[8]);
      prueba_escritura.write(ficheros::to_str(aux9), sizeof(float));
    }
    prueba_escritura.close();
    parametros.clear();
  }
}  // namespace ficheros
//NOLINTEND