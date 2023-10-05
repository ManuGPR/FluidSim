//
// Created by marina on 27/09/23.
//

#include "block.hpp"

namespace bloque {
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

    int loc_particula(struct Particula particulas, int np, vector<double> lim_inferior, vector<double> tam_bloque) {
        for (int i = 0; i < np; i++) {
            particulas.loc_x[i] = pos_particula_x(particulas.pos_x[i], lim_inferior[0], tam_bloque[0]);
            particulas.loc_y[i] = pos_particula_y(particulas.pos_y[i], lim_inferior[1], tam_bloque[1]);
            particulas.loc_z[i] = pos_particula_z(particulas.pos_z[i], lim_inferior[2], tam_bloque[2]);
        }
        return 0;
    }
}