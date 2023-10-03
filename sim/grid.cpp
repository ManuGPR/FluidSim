//
// Created by marina on 27/09/23.
//

#include "grid.hpp"

//NOTA; quizás se pueden meter vectores en los parámetros para evitar hacer tres funciones por eje
namespace malla {
    int num_bloques (vector<double> lim_sup, vector<double> lim_inf, double h, vector<int> & result) {
        /*Función encargada de calcular el número de bloques
         *param1: Vector con los límites superiores, param2: Vector con los límites inferiores
         *param3: Longitud de suavizado, param4: Vector donde guardar el resultado */
        result[0] = floor((lim_sup[0] - lim_inf[0]) / h);
        result[1] = floor((lim_sup[1] - lim_inf[1]) / h);
        result[2] = floor((lim_sup[2] - lim_inf[2]) / h);
        return 0;
    }

    int tam_bloques (vector<double> lim_sup, vector<double> lim_inf, vector<int> num_bloques, vector<double> & result){
        /*Función encargada de calcular el tamaño de bloques
         *param1: Vector con los límites superiores, param2: Vector con los límites inferiores
         *param3: Vector con el número de bloques de cada eje, param4: vector donde guardar el resultado*/
        result[0] = (lim_sup[0] - lim_inf[0]) / num_bloques[0];
        result[1] = (lim_sup[1] - lim_inf[1]) / num_bloques[1];
        result[2] = (lim_sup[2] - lim_inf[2]) / num_bloques[2];
        return 0;
    }

    int pos_particula_x (double pos_x, double xmin, double tam_bloque_x) {
        /*Función encargada de calcular la posición en x de una partícula
         * param1: posicion vectorial de x, param2: limite inferior en el eje x, param3: tamaño de los bloques de x*/
        return floor((pos_x - xmin) / tam_bloque_x);
    }
    int pos_particula_y(double pos_y, double ymin, double tam_bloque_y) {
        /*Función encargada de calcular la posición en y de una particula
         * param1: posición vectorial de y, param2: límite inferior en el eje y, param3: tamaño de los bloques de y*/
        return floor((pos_y - ymin) / tam_bloque_y);
    }
    int pos_particula_z(double pos_z, double zmin, double tam_bloque_z) {
        /*Función encargada de calcular la posición en z de una partícula
         * param1: posición vectorial de z, param2: límite inferior en el eje z, param3: tamaño de los bloques de z*/
        return floor((pos_z - zmin) / tam_bloque_z);
    }

    double lectura_float_to_double (ifstream & fichero) {
        /*Función que se encarga de leer un float del fichero y devolver un double
         * param1: fichero del que se lee*/
        float aux_float;
        fichero.read(reinterpret_cast<char*> (&aux_float), sizeof(float));
        return static_cast<double>(aux_float);
    }
}