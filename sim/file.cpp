#include "file.hpp"

using namespace std;

namespace ficheros {
  inline void read_value(std::istream & is, float & value) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    is.read(reinterpret_cast<char *>(&value), sizeof(value));
  }

  inline void read_value(std::istream & is, int & value) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    is.read(reinterpret_cast<char *>(&value), sizeof(value));
  }

  inline void read_value(std::istream & is, double & value) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    is.read(reinterpret_cast<char *>(&value), sizeof(value));
  }

  // Función que se encarga de leer la cabecera
  tuple<int, double> lectura_cabecera(ifstream & file_in) {
    const int menos_cinco = -5;
    const double cinco_punto_cero = 5.0;
    tuple<int, double> bad_return = {menos_cinco, cinco_punto_cero};
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
    while (!file_in.eof()) {
      // hay que hacer el checkeo de np (variable que vaya sumando, comprobar al final o poner un if
      // con un break)
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
    if (np_real - 1 != np) {
      cerr << " Number of particles mismatch. Header: " << np << ", Found:" << np_real - 1 << "\n";
      return bad_return;
    }
    return 0;
  }

  // Función que escribe un fichero de salida de comprobación
  [[maybe_unused]] int escritura_comp() {  // Esta función hay que borrarla
    ifstream fichero_comp;
    ofstream fichero_comp_salida("salida.txt");
    fichero_comp.open("./trz/small/boundint-base-3.trz", ios::binary);
    int cabecera = 0;
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    fichero_comp.read(reinterpret_cast<char *>(&cabecera), sizeof(int));
    fichero_comp_salida << cabecera << "\n";
    int num_bloque = 0;
    while (!fichero_comp.eof()) {
      long int num_p = 0;
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      fichero_comp.read(reinterpret_cast<char *>(&num_p), sizeof(long int));
      fichero_comp_salida << num_bloque << " " << num_p << "\n";
      loop_escritura_comp(num_p, fichero_comp, fichero_comp_salida);
      num_bloque++;
      fichero_comp_salida << "\n";
    }
    return 0;
  }

  [[maybe_unused]] void loop_escritura_comp(long int & num_p, ifstream & fichero_comp,
                                            ofstream & fichero_comp_salida) {
    for (int j = 0; j < num_p; j++) {
      long int identificador = 0;
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      fichero_comp.read(reinterpret_cast<char *>(&identificador), sizeof(long int));
      fichero_comp_salida << identificador << " ";
      double aux = 0.0;
      for (int k = 0; k < 3; k++) {
        read_value(fichero_comp, aux);
        fichero_comp_salida << aux << " ";
        read_value(fichero_comp, aux);
        fichero_comp_salida << aux << " ";
        read_value(fichero_comp, aux);
        fichero_comp_salida << aux << " ";
      }
      read_value(fichero_comp, aux);
      fichero_comp_salida << aux << " ";
      for (int k = 0; k < 3; k++) {
        read_value(fichero_comp, aux);
        fichero_comp_salida << aux << " ";
      }
      fichero_comp_salida << "\n";
    }
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
    int nps_1         = 0;
    float ppm_float_1 = 0.0;
    int nps_2         = 0;
    float ppm_float_2 = 0.0;
    read_value(file_in, ppm_float_1);
    read_value(file_in, nps_1);
    read_value(file_corect, ppm_float_2);
    read_value(file_corect, nps_2);
    const int nps_temp = static_cast<int>(nps_2);
    if (nps_1 != nps_temp || ppm_float_1 != ppm_float_2) { return -1; }
    float aux_float_1 = 0.0;
    float aux_float_2 = 0.0;
    while (!file_corect.eof()) {
      read_value(file_in, aux_float_1);
      read_value(file_corect, aux_float_2);
      if (aux_float_1 != aux_float_2) { return -1; }
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
    ;
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