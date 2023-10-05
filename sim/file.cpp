//
// Created by manu on 5/10/23.
//

#include "file.hpp"

namespace ficheros {
    pair <int, double> lectura_cabecera(ifstream & file_in){
        double ppm;
        int np;
        float ppm_float;
        pair <int, double> datos;
        file_in.read(reinterpret_cast<char *> (&ppm_float), sizeof(float));
        ppm = static_cast<double>(ppm_float);
        file_in.read(reinterpret_cast<char *> (&np), sizeof(int));
        //Comprobación del np
        if (entry::check_np(np) != 0){return -5;}
        datos.first = np;
        datos.second = ppm;
        return datos;
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

    int escritura_fichero(char* file_out, struct Particula &particulas, double ppm, int np) {
        ofstream
        file_out.write(static_cast<float>(ppm), sizeof(float));
        file_out.write(np, sizeof(float));
        return 0;
    }
}