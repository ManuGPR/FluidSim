//
// Created by manu on 5/10/23.
//

#include "file.hpp"

namespace ficheros {
    double  lectura_cabecera(ifstream & file_in){
        double ppm;
        int np;
        float ppm_float;
        file_in.read(reinterpret_cast<char *> (&ppm_float), sizeof(float));
        ppm = static_cast<double>(ppm_float);
        file_in.read(reinterpret_cast<char *> (&np), sizeof(int));
        //Comprobación del np
        if (entry::check_np(np) != 0){return -5.0;}
        np = static_cast<double>(np);
        return np, ppm;
    }

    double lectura_float_to_double (ifstream & fichero) {
        /*Función que se encarga de leer un float del fichero y devolver un double
         * param1: fichero del que se lee*/
        float aux_float;
        fichero.read(reinterpret_cast<char *> (&aux_float), sizeof(float));
        return static_cast<double>(aux_float);
    }
    int lectura_file(ifstream & fichero, struct Particula &particulas){
        for (int i = 0; i<np; i++) {
            //hay que hacer el checkeo de np (variable que vaya sumando, comprobar al final o poner un if con un break)
            particulas.pos_x[i] = ficheros::lectura_float_to_double(fichero);
            particulas.pos_y[i] = lectura_float_to_double(fichero);
            particulas.pos_z[i] = lectura_float_to_double(fichero);
            particulas.hv_x[i] =  lectura_float_to_double(fichero);
            particulas.hv_y[i] =  lectura_float_to_double(fichero);
            particulas.hv_z[i] =  lectura_float_to_double(fichero);
            particulas.vel_x[i] = lectura_float_to_double(fichero);
            particulas.vel_y[i] = lectura_float_to_double(fichero);
            particulas.vel_z[i] = lectura_float_to_double(fichero);
            particulas.acel_x[i] = aceleracion_externa[0];
            particulas.acel_y[i] = aceleracion_externa[1];
            particulas.acel_z[i]= aceleracion_externa[2];
        }
    }

    int escritura_fichero(char* name_out, struct Particula &particulas, double ppm, int np) {
        ofstream file_out;
        file_out.open(name_out, ios::binary);
        file_out.write(double_to_str(ppm), sizeof(float));
        file_out.write(int_to_str(np), sizeof(float));
        for (int i = 0; i < np; i++) {
            file_out.write(double_to_str(particulas.pos_x[i]), sizeof(float));
            file_out.write(double_to_str(particulas.pos_y[i]), sizeof(float));
            file_out.write(double_to_str(particulas.pos_z[i]), sizeof(float));
            file_out.write(double_to_str(particulas.hv_x[i]), sizeof(float));
            file_out.write(double_to_str(particulas.hv_y[i]), sizeof(float));
            file_out.write(double_to_str(particulas.hv_z[i]), sizeof(float));
            file_out.write(double_to_str(particulas.vel_x[i]), sizeof(float));
            file_out.write(double_to_str(particulas.vel_y[i]), sizeof(float));
            file_out.write(double_to_str(particulas.vel_z[i]), sizeof(float));
        }
        return 0;
    }

    const char* int_to_str(int parameter) {
        string aux_srt = to_string(parameter);
        const char* value = aux_srt.c_str();
        return value;
    }

    const char* double_to_str(double parameter) {
        float aux;
        aux = static_cast<float>(parameter);
        string aux_str = to_string(aux);
        const char* value = aux_str.c_str();
        return value;
    }
}