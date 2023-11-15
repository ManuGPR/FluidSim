#include "file.hpp"

using namespace std;

// NOLINTBEGIN
namespace ficheros {
  // Función que se encarga de leer la cabecera
  tuple<int, double> lectura_cabecera(ifstream & file_in) {
    tuple<int, double> bad_return = {-5, 5.0};
    int nps                             = 0;
    float ppm                           = 0.0;

    file_in.read(reinterpret_cast<char *>(&ppm), sizeof(float));
    file_in.read(reinterpret_cast<char *>(&nps), sizeof(int));
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
    const int bad_return = -5;
    int np_real          = 0;
    while (!file_in.eof()) {
      // hay que hacer el checkeo de np (variable que vaya sumando, comprobar al final o poner un if con un break)
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
      cerr << " Number of particles mismatch. Header: " << np << ", Found:" << np_real << "\n";
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
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
        fichero_comp_salida << aux << " ";
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
        fichero_comp_salida << aux << " ";
        fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
        fichero_comp_salida << aux << " ";
      }
      fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
      fichero_comp_salida << aux << " ";
      for (int k = 0; k < 3; k++) {
        fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
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
  const char* to_str(int & parameter) {
    const char * value = reinterpret_cast<const char*>(&parameter);
    return value;
  }

  const char* to_str(float & parameter) {
    const char * value = reinterpret_cast<const char *>(&parameter);
    return value;
  }

  //------------FUNCIONES AUXILIARES PARA LOS TEST FUNCIONALES---------------

  // Función que compara dos ficheros (usada en los test)
  int comparar_ficheros(ifstream & file_in, ifstream & file_corect) {
    int nps_1         = 0;
    float ppm_float_1 = 0.0;
    int nps_2         = 0;
    float ppm_float_2 = 0.0;
    file_in.read(reinterpret_cast<char *>(&ppm_float_1), sizeof(float));
    file_in.read(reinterpret_cast<char *>(&nps_1), sizeof(int));
    file_corect.read(reinterpret_cast<char *>(&ppm_float_2), sizeof(float));
    file_corect.read(reinterpret_cast<char *>(&nps_2), sizeof(int));
    if (nps_1 != nps_2 or ppm_float_1 != ppm_float_2) { return -1; }
    float aux_float_1 = 0.0;
    float aux_float_2 = 0.0;
    while (!file_corect.eof()) {
      file_in.read(reinterpret_cast<char *>(&aux_float_1), sizeof(float));
      file_corect.read(reinterpret_cast<char *>(&aux_float_2), sizeof(float));
      if (aux_float_1 != aux_float_2) { return -1; }
    }
    return 0;
  }

  // Función que modifica un fichero (Usada para los tests)
  int modificar_fichero(string & file_name, int nps_mod) {
    ofstream file_out;
    file_out.open("small_modificado.fld", ios::binary);
    ifstream file_in;
    file_in.open(file_name, ios::binary);
    int nps         = 0;
    float ppm_float = 0.0;
    file_in.read(reinterpret_cast<char *>(&ppm_float), sizeof(float));
    file_out.write(to_str(ppm_float), sizeof(float));
    file_in.read(reinterpret_cast<char *>(&nps), sizeof(int));
    file_out.write(to_str(nps_mod), sizeof(int));
    float aux_float = 0.0;
    while (!file_in.eof()) {
      file_in.read(reinterpret_cast<char *>(&aux_float), sizeof(float));
      file_out.write(to_str(aux_float), sizeof(float));
    }
    file_in.close();
    file_out.close();
    return 0;
  }

  // Función que compara un fichero de trazas con unas partículas
  int trazas(ifstream & fichero_comp, Particula & particulas) {
    int cabecera = 0;
    fichero_comp.read(reinterpret_cast<char *>(&cabecera), sizeof(int));
    while (!fichero_comp.eof()) {
      long int num_p = 0;
      fichero_comp.read(reinterpret_cast<char *>(&num_p), sizeof(long int));
      double aux = 0.0;
      for (int j = 0; j < num_p; j++) {
        fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
        read_pos_xyz(fichero_comp, particulas);
        read_hv_xyz(fichero_comp, particulas);
        read_vel_xyz(fichero_comp, particulas);
        fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
        read_acel_xyz(fichero_comp, particulas);
      }
    }
    return 0;
  }

  int read_pos_xyz(ifstream & fichero_comp, Particula & particulas) {
    const double epsilon         = 0.000001;
    const long int identificador = 0;
    double aux                   = 0.0;
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    if (fabs(particulas.pos_x[identificador] - aux) >= epsilon) { return -1; }
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    if (fabs(particulas.pos_y[identificador] - aux) >= epsilon) { return -1; }
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    if (fabs(particulas.pos_z[identificador] - aux) >= epsilon) { return -1; }
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    return 0;
  }

  int read_hv_xyz(ifstream & fichero_comp, Particula & particulas) {
    const double epsilon         = 0.000001;
    const long int identificador = 0;
    double aux                   = 0.0;
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    if (fabs(particulas.hv_x[identificador] - aux) >= epsilon) { return -2; }
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    if (fabs(particulas.hv_y[identificador] - aux) >= epsilon) { return -2; }
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    if (fabs(particulas.hv_z[identificador] - aux) >= epsilon) { return -2; }
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    return 0;
  }

  int read_vel_xyz(ifstream & fichero_comp, Particula & particulas) {
    const double epsilon         = 0.000001;
    const long int identificador = 0;
    double aux                   = 0.0;
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    if (fabs(particulas.vel_x[identificador] - aux) >= epsilon) { return -3; }
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    if (fabs(particulas.vel_y[identificador] - aux) >= epsilon) { return -3; }
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    if (fabs(particulas.vel_z[identificador] - aux) >= epsilon) { return -3; }
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    return 0;
  }

  int read_acel_xyz(ifstream & fichero_comp, Particula & particulas) {
    const double epsilon         = 0.000001;
    const long int identificador = 0;
    double aux                   = 0.0;
    const int numb               = -5;
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    if (fabs(particulas.acel_x[identificador] - aux) >= epsilon) { return numb; }
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    if (fabs(particulas.acel_y[identificador] - aux) >= epsilon) { return numb; }
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    if (fabs(particulas.acel_z[identificador] - aux) >= epsilon) { return numb; }
    fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
    return 0;
  }

  //------------FUNCIONES AUXILIARES PARA LOS TEST UNITARIOS----------------

  vector<float> vector_creacion() {
    vector<float> parametros;
    parametros.push_back(1.5);
    parametros.push_back(2.5);
    parametros.push_back(3.5);
    parametros.push_back(4.5);
    parametros.push_back(5.5);
    parametros.push_back(6.5);
    parametros.push_back(7.5);
    parametros.push_back(8.5);
    parametros.push_back(9.5);

    return parametros;
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

  vector<double> comprobacion_lectura1() {
    vector<double> comprobacion;
    ifstream fichero_comprobacion;
    fichero_comprobacion.open("prueba_es.fld", ios::binary);
    comprobacion[0] = ficheros::lectura_float_to_double(fichero_comprobacion);
    int aux         = 0;
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    fichero_comprobacion.read(reinterpret_cast<char *>(&aux), sizeof(int));
    comprobacion[1] = ficheros::lectura_float_to_double(fichero_comprobacion);
    comprobacion[2] = ficheros::lectura_float_to_double(fichero_comprobacion);
    comprobacion[3] = ficheros::lectura_float_to_double(fichero_comprobacion);
    comprobacion[4] = ficheros::lectura_float_to_double(fichero_comprobacion);
    comprobacion[5] = ficheros::lectura_float_to_double(fichero_comprobacion);
    comprobacion[6] = ficheros::lectura_float_to_double(fichero_comprobacion);
    comprobacion[7] = ficheros::lectura_float_to_double(fichero_comprobacion);
    comprobacion[8] = ficheros::lectura_float_to_double(fichero_comprobacion);
    comprobacion[9] = ficheros::lectura_float_to_double(fichero_comprobacion);
    return comprobacion;
  }

  int comprobacion_lectura2() {
    ifstream fichero_comprobacion;
    fichero_comprobacion.open("prueba_es.fld", ios::binary);
    double inn = 0.0;
    int npart  = 0;
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    fichero_comprobacion.read(reinterpret_cast<char *>(&inn), sizeof(double));
    fichero_comprobacion.read(reinterpret_cast<char *>(&npart), sizeof(int));
    return inn;
  }
}
// NOLINTEND