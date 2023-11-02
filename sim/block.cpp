//
// Created by marina on 27/09/23.
//

#include "block.hpp"

namespace bloque {
  int num_bloques (struct Enclosure3D & malla, struct Constantes & constantes) {
    /*Función encargada de calcular el número de bloques
         *param1: Vector con los límites superiores, param2: Vector con los límites inferiores
         *param3: Longitud de suavizado, param4: Vector donde guardar el resultado */
    malla.num_bloques.push_back(floor((lim_sup_x - lim_inf_x) / constantes.h));
    malla.num_bloques.push_back(floor((lim_sup_y - lim_inf_y) / constantes.h));
    malla.num_bloques.push_back(floor((lim_sup_z - lim_inf_z) / constantes.h));
    return 0;
  }

  int tam_bloques (struct Enclosure3D & malla){
    /*Función encargada de calcular el tamaño de bloques
         *param1: Vector con los límites superiores, param2: Vector con los límites inferiores
         *param3: Vector con el número de bloques de cada eje, param4: vector donde guardar el resultado*/
    malla.tam_bloques.push_back((lim_sup_x - lim_inf_x) / malla.num_bloques[0]);
    malla.tam_bloques.push_back((lim_sup_y - lim_inf_y) / malla.num_bloques[1]);
    malla.tam_bloques.push_back((lim_sup_z - lim_inf_z) / malla.num_bloques[2]);
    return 0;
  }

  int pos_particula_x (double pos_x, double tam_bloque_x) {
    /*Función encargada de calcular la posición en x de una partícula
         * param1: posicion vectorial de x, param2: limite inferior en el eje x, param3: tamaño de los bloques de x*/
    return floor((pos_x - lim_inf_x) / tam_bloque_x);
  }
  int pos_particula_y(double pos_y, double tam_bloque_y) {
    /*Función encargada de calcular la posición en y de una particula
         * param1: posición vectorial de y, param2: límite inferior en el eje y, param3: tamaño de los bloques de y*/
    return floor((pos_y - lim_inf_y) / tam_bloque_y);
  }
  int pos_particula_z(double pos_z, double tam_bloque_z) {
    /*Función encargada de calcular la posición en z de una partícula
         * param1: posición vectorial de z, param2: límite inferior en el eje z, param3: tamaño de los bloques de z*/
    return floor((pos_z - lim_inf_z) / tam_bloque_z);
  }

  int loc_particula(struct Particula & particulas, struct Enclosure3D & malla) {
    //CAMBIAR A TRES FUNCIONES DE RELOCALIZACIÓN
    for (int i = 0; i < malla.nps; i++) {
      particulas.loc_x[i] = pos_particula_x(particulas.pos_x[i], malla.tam_bloques[0]);
      if (particulas.loc_x[i] < 0) {
        particulas.loc_x[i] = 0;
      } else if (particulas.loc_x[i] >= malla.num_bloques[0]) {
        particulas.loc_x[i] = malla.num_bloques[0] - 1;
      }
      particulas.loc_y[i] = pos_particula_y(particulas.pos_y[i], malla.tam_bloques[1]);
      if (particulas.loc_y[i] < 0) {
        particulas.loc_y[i] = 0;
      } else if (particulas.loc_y[i] >= malla.num_bloques[1]) {
        particulas.loc_y[i] = malla.num_bloques[1] - 1;
      }
      particulas.loc_z[i] = pos_particula_z(particulas.pos_z[i], malla.tam_bloques[2]);
      if (particulas.loc_z[i] < 0) {
        particulas.loc_z[i] = 0;
      } else if (particulas.loc_z[i] >= malla.num_bloques[2]) {
        particulas.loc_z[i] = malla.num_bloques[2] - 1;
      }
    }
    return 0;
  }

  int particula_contigua(const struct Particula &part, int id_i, int id_j) {
        const int suma_x = abs(part.loc_x[id_i] - part.loc_x[id_j]);
    if (suma_x > 1) { return 0; }
        const int suma_y = abs(part.loc_y[id_i] - part.loc_y[id_j]);
    if (suma_y > 1) { return 0; }
        const int suma_z = abs(part.loc_z[id_i] - part.loc_z[id_j]);
    if (suma_z > 1) { return 0; }
    return 1;
  }
}