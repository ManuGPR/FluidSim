//
// Created by manu on 5/10/23.
//

#include "file.hpp"



using namespace std;

namespace ficheros {
  tuple <int, double> lectura_cabecera(ifstream & file_in){
    const tuple<int, double> bad_return = {-5, 5.0};
    int nps = 0;
    float ppm_float = 0.0;
    file_in.read(reinterpret_cast<char *> (&ppm_float), sizeof(float));
    const double ppm = static_cast<double>(ppm_float);
    file_in.read(reinterpret_cast<char *> (&nps), sizeof(int));
    //Comprobación del nps
    if (entry::check_np(nps) != 0){return bad_return;}
    const tuple<int, double> good_return = {nps, ppm};
    return good_return;
  }

  double lectura_float_to_double (ifstream & fichero) {
    /*Función que se encarga de leer un float del fichero y devolver un double
         * param1: fichero del que se lee*/
    float aux_float = 0.0;
    fichero.read(reinterpret_cast<char *> (&aux_float), sizeof(float));
    return static_cast<double>(aux_float);
  }

  int lectura_file(ifstream & file_in, int np, struct Particula & particulas){
        const int bad_return = -5;
    int np_real = 0;
    for (int i = 0; i < np; i++){
      //hay que hacer el checkeo de np (variable que vaya sumando, comprobar al final o poner un if con un break)
      particulas.pos_x[np_real] = ficheros::lectura_float_to_double(file_in);
      particulas.pos_y[np_real] = lectura_float_to_double(file_in);
      particulas.pos_z[np_real] = lectura_float_to_double(file_in);
      particulas.hv_x[np_real] =  lectura_float_to_double(file_in);
      particulas.hv_y[np_real] =  lectura_float_to_double(file_in);
      particulas.hv_z[np_real] =  lectura_float_to_double(file_in);
      particulas.vel_x[np_real] = lectura_float_to_double(file_in);
      particulas.vel_y[np_real] = lectura_float_to_double(file_in);
      particulas.vel_z[np_real] = lectura_float_to_double(file_in);
      particulas.acel_x[np_real] = gravedad_x;
      particulas.acel_y[np_real] = gravedad_y;
      particulas.acel_z[np_real] = gravedad_z;
      //cout << particulas.hv_x[np_real] << "\n";
      np_real ++;
    }
    if (np_real != np){
      cerr << " Number of particles mismatch. Header: " << np <<", Found:" << np_real << "\n";
      return bad_return;
    }
    return 0;
  }

  int escritura_comp() {//Esta función hay que borrarla
    ifstream fichero_comp;
    ofstream fichero_comp_salida("salida.txt");
    fichero_comp.open("boundint-base-5.trz", ios::binary);
    int cabecera = 0;
    fichero_comp.read(reinterpret_cast<char *> (&cabecera), sizeof(int));
    fichero_comp_salida << cabecera << "\n";
    int num_bloque = 0;
    while(!fichero_comp.eof()) {
      long int num_p = 0;
      fichero_comp.read(reinterpret_cast<char *>(&num_p), sizeof(long int));
      fichero_comp_salida << num_bloque << " " << num_p << "\n";
      for (int j = 0; j < num_p; j++) {
        long int identificador = 0;
        fichero_comp.read(reinterpret_cast<char *>(&identificador), sizeof(long int));
        fichero_comp_salida << identificador << " ";
        double aux = 0.0;
        for (int k = 0; k < 3; k++) {
          fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
          fichero_comp_salida << aux << " ";
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
      num_bloque++;
      fichero_comp_salida << "\n";
    }
    return 0;
  }

  int escritura_salida(ofstream& file_out, const struct Particula & particulas, double & ppm, int np) {
    auto aux = static_cast<float>(ppm);
    file_out.write(to_str(aux), sizeof(float));
    file_out.write(to_str(np), sizeof(float));
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

    const char* to_str(int & parameter) {
        const char *value = reinterpret_cast<const char*>(&parameter);
    return value;
  }

    const char* to_str(float & parameter) {
        const char *value = reinterpret_cast<const char *>(&parameter);
    return value;
  }
}