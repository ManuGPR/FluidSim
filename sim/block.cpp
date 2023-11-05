//
// Created by marina on 27/09/23.
//

#include "block.hpp"

namespace bloque {
  int num_bloques (vector<int> &num_bloques, double & h) {
    /*Función encargada de calcular el número de bloques
         *param1: Vector con los límites superiores, param2: Vector con los límites inferiores
         *param3: Longitud de suavizado, param4: Vector donde guardar el resultado */
    num_bloques.push_back(floor((lim_sup_x - lim_inf_x) / h));
    num_bloques.push_back(floor((lim_sup_y - lim_inf_y) / h));
    num_bloques.push_back(floor((lim_sup_z - lim_inf_z) / h));
    return 0;
  }

  int tam_bloques (vector<double> &tam_bloques,vector<int> &num_bloques){
    /*Función encargada de calcular el tamaño de bloques
         *param1: Vector con los límites superiores, param2: Vector con los límites inferiores
         *param3: Vector con el número de bloques de cada eje, param4: vector donde guardar el resultado*/
    tam_bloques.push_back((lim_sup_x - lim_inf_x) / num_bloques[0]);
    tam_bloques.push_back((lim_sup_y - lim_inf_y) / num_bloques[1]);
    tam_bloques.push_back((lim_sup_z - lim_inf_z) / num_bloques[2]);
    return 0;
  }



  int loc_particula_bucle(struct Particula & particulas, struct Enclosure3D & malla, vector<int> &num_bloques, vector<struct Bloque> & bloques) {
    //CAMBIAR A TRES FUNCIONES DE RELOCALIZACIÓN
    const int num_bloques_total = num_bloques[0] * num_bloques[1] * num_bloques[2];
    for (int i = 0; i < num_bloques_total; i ++) {
      bloques[i].lista_particulas.clear();
    }
    for (int i = 0; i < malla.nps; i++) {
      particulas.loc_x[i] = loc_particula_x (particulas.loc_x[i], particulas.pos_x[i], malla.tam_bloques[0], num_bloques[0] );
      particulas.loc_y[i] = loc_particula_y (particulas.loc_y[i], particulas.pos_y[i], malla.tam_bloques[1], num_bloques[1] );
      particulas.loc_z[i] =loc_particula_z (particulas.loc_z[i], particulas.pos_z[i], malla.tam_bloques[2], num_bloques[2] );
      particulas.bloque[i] = particulas.loc_x[i] + num_bloques[0] *(particulas.loc_y[i] + num_bloques[1] * particulas.loc_z[i]);
      bloques[particulas.bloque[i]].lista_particulas.push_back(i);
    }
    return 0;
  }
  inline int loc_particula_x( int loc, double &pos, double &tam_bloques, int num_bloque){
    loc = floor((pos - lim_inf_x) / tam_bloques);
    if (loc < 0) {
      loc = 0;
    } else if (loc >= num_bloque) {
      loc = num_bloque - 1;
    }
    return loc;
  }
  inline int loc_particula_y( int loc, double &pos, double &tam_bloques, int num_bloque){
    loc = floor((pos - lim_inf_y) / tam_bloques);
    if (loc < 0) {
       loc = 0;
    } else if (loc >= num_bloque) {
       loc = num_bloque - 1;
    }
    return loc;
  }
  inline int loc_particula_z( int loc, double &pos, double &tam_bloques, int num_bloque){
    loc = floor((pos - lim_inf_z) / tam_bloques);
    if (loc < 0) {
      loc = 0;
    } else if (loc >= num_bloque) {
      loc = num_bloque - 1;
    }
    return loc;
  }

  /*int loc_bloque(struct Particula & particulas, vector<struct Bloque> & bloques, int nps, int num_bloques){
    for (int i = 0; i < num_bloques; i ++) {
      bloques[i].lista_particulas.clear();
    }
    for (int i = 0; i < nps; i ++){
      bloques[particulas.bloque[i]].lista_particulas.push_back(i);
    }
    return 0;
  }*/

  int total_bloques(vector<int> & num_bloques) {
    return num_bloques[0] * num_bloques[1] * num_bloques[2];
  }

  int crear_bloques(vector<struct Bloque> & bloques, int total_bloques, vector<int> & num_bloques) {
    struct Aux auxiliar(total_bloques);
    crear_auxiliar(num_bloques, auxiliar);
    for (int i = 0; i < total_bloques; i++) {
      struct Bloque bloque_i;
      for (int j = 0; j < total_bloques; j++) {
        const int suma_x = abs(auxiliar.pos_x[i] - auxiliar.pos_x[j]);
        const int suma_y = abs(auxiliar.pos_y[i] - auxiliar.pos_y[j]);
        const int suma_z = abs(auxiliar.pos_z[i] - auxiliar.pos_z[j]);
        if (suma_x <= 1) {
          if (suma_y <= 1) {
            if (suma_z <= 1) { bloque_i.bloque_contiguo.push_back(j); }
          }
        }
      }
      bloques.push_back(bloque_i);
    }
    return 0;
  }

  int crear_auxiliar(vector<int> & num_bloques, struct Aux & auxiliar){
    for (int k = 0; k < num_bloques[2]; k++) {
      for (int j = 0; j < num_bloques[1]; j++) {
        for (int i = 0; i < num_bloques[0]; i++) {
          const int codigo_id = i + num_bloques[0] * (j + num_bloques[1] * k);
          auxiliar.pos_x[codigo_id] = i;
          auxiliar.pos_y[codigo_id] = j;
          auxiliar.pos_z[codigo_id] = k;
        }
      }
    }
    return 0;
  }
}  // namespace bloque