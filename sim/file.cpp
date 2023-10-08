//
// Created by manu on 5/10/23.
//

#include "file.hpp"
#include "constants.hpp"


using namespace std;

namespace ficheros {
    tuple <int, double> lectura_cabecera(ifstream & file_in){
        double ppm;
        int np;
        float ppm_float;
        tuple <int,double> datos;
        file_in.read(reinterpret_cast<char *> (&ppm_float), sizeof(float));
        ppm = static_cast<double>(ppm_float);
        file_in.read(reinterpret_cast<char *> (&np), sizeof(int));
        //Comprobación del np
        if (entry::check_np(np) != 0){return tuple(-5, -5.0);}
        np = static_cast<double>(np);
        return tuple(np, ppm);
    }

    double lectura_float_to_double (ifstream & fichero) {
        /*Función que se encarga de leer un float del fichero y devolver un double
         * param1: fichero del que se lee*/
        float aux_float;
        fichero.read(reinterpret_cast<char *> (&aux_float), sizeof(float));
        return static_cast<double>(aux_float);
    }
    int lectura_file(ifstream & file_in, int np, struct Particula & particulas){
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
            particulas.acel_x[np_real] = acel_ex[0];
            particulas.acel_y[np_real] = acel_ex[1];
            particulas.acel_z[np_real]= acel_ex[2];
            np_real ++;
        }
        if (np_real != np){
            cerr << " Number of particles mismatch. Header: " << np <<", Found:" << np_real << endl;
            return -5;
        }
    }

    int escritura_salida(ofstream& file_out, const struct Particula & particulas, double ppm, int np) {
        file_out.write(to_str(ppm), sizeof(float));
        file_out.write(to_str(np), sizeof(float));
        for (int i = 0; i < np; i++) {
            file_out.write(to_str(particulas.pos_x[i]), sizeof(float));
            file_out.write(to_str(particulas.pos_y[i]), sizeof(float));
            file_out.write(to_str(particulas.pos_z[i]), sizeof(float));
            file_out.write(to_str(particulas.hv_x[i]), sizeof(float));
            file_out.write(to_str(particulas.hv_y[i]), sizeof(float));
            file_out.write(to_str(particulas.hv_z[i]), sizeof(float));
            file_out.write(to_str(particulas.vel_x[i]), sizeof(float));
            file_out.write(to_str(particulas.vel_y[i]), sizeof(float));
            file_out.write(to_str(particulas.vel_z[i]), sizeof(float));
        }
        return 0;
    }

    const char* to_str(int parameter) {
        const char *value = reinterpret_cast<char*>(&parameter);
        return value;
    }

    const char* to_str(double parameter) {
        float aux = static_cast<float>(parameter);
        const char* value = reinterpret_cast<char *>(&aux);
        return value;
    }
}