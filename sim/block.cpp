#include "block.hpp"

namespace block {
  // Función que calcula el número de bloques
  int num_bloques(vector<int> & num_bloques, double & h) {
    //Calcula el número de bloques y los guarda en el vector
    num_bloques.push_back(floor((lim_sup_x - lim_inf_x) / h));
    num_bloques.push_back(floor((lim_sup_y - lim_inf_y) / h));
    num_bloques.push_back(floor((lim_sup_z - lim_inf_z) / h));
    return 0;
  }

  // Funcion que calcula el tamaño de bloques
  int tam_bloques(vector<double> & tam_bloques, vector<int> & num_bloques) {
    //Calcula el tamaño de bloques y los guarda en el vector
    tam_bloques.push_back((lim_sup_x - lim_inf_x) / num_bloques[0]);
    tam_bloques.push_back((lim_sup_y - lim_inf_y) / num_bloques[1]);
    tam_bloques.push_back((lim_sup_z - lim_inf_z) / num_bloques[2]);
    return 0;
  }

  // Función que localiza todas las partículas
  int loc_particula_bucle(struct Particula & particulas, struct Enclosure3D & malla,
                          vector<int> & num_bloques, vector<struct Bloque> & bloques) {
    //Calcula el numero de bloques total y reinicia la lista de partículas
    int const num_bloques_total = num_bloques[0] * num_bloques[1] * num_bloques[2];
    for (int i = 0; i < num_bloques_total; i++) { bloques[i].lista_particulas.clear(); }
    //Calcula la localización de la partícula y la guarda en el bloque
    for (int i = 0; i < malla.nps; i++) {
      particulas.loc_x[i] =
          loc_particula_x(particulas.pos_x[i], malla.tam_bloques[0], num_bloques[0]);
      particulas.loc_y[i] =
          loc_particula_y(particulas.pos_y[i], malla.tam_bloques[1], num_bloques[1]);
      particulas.loc_z[i] =
          loc_particula_z(particulas.pos_z[i], malla.tam_bloques[2], num_bloques[2]);
      particulas.bloque[i] =
          particulas.loc_x[i] +
          num_bloques[0] * (particulas.loc_y[i] + num_bloques[1] * particulas.loc_z[i]);
      bloques[particulas.bloque[i]].lista_particulas.push_back(i);
    }
    return 0;
  }

  // Funciones que localizan la partícula
  inline int loc_particula_x(double & pos, double & tam_bloques, int num_bloque) {
    //Calcula la localización y la ajusta si se sale
    int loc = floor((pos - lim_inf_x) / tam_bloques);
    if (loc < 0) {
      loc = 0;
    } else if (loc >= num_bloque) {
      loc = num_bloque - 1;
    }
    return loc;
  }

  inline int loc_particula_y(double & pos, double & tam_bloques, int num_bloque) {
    //Calcula la localización y la ajusta si se sale
    int loc = floor((pos - lim_inf_y) / tam_bloques);
    if (loc < 0) {
      loc = 0;
    } else if (loc >= num_bloque) {
      loc = num_bloque - 1;
    }
    return loc;
  }

  inline int loc_particula_z(double & pos, double & tam_bloques, int num_bloque) {
    //Calcula la localización y la ajusta si se sale
    int loc = floor((pos - lim_inf_z) / tam_bloques);
    if (loc < 0) {
      loc = 0;
    } else if (loc >= num_bloque) {
      loc = num_bloque - 1;
    }
    return loc;
  }

  // Función auxiliar que devuelve el total de bloques
  int total_bloques(vector<int> & num_bloques) {
    return num_bloques[0] * num_bloques[1] * num_bloques[2];
  }

  // Función que crea los bloques
  int crear_bloques(vector<struct Bloque> & bloques, int total_bloques, vector<int> & num_bloques) {
    // Crea una estructura auxiliar y la inicializa
    struct Aux auxiliar(total_bloques);
    crear_auxiliar(num_bloques, auxiliar);
    //Rellena el vector de bloques con bloques con la información de partículas y bloques contiguos
    for (int i = 0; i < total_bloques; i++) {
      struct Bloque bloque_i;
      for (int j = 0; j < total_bloques; j++) {
        int const suma_x = abs(auxiliar.pos_x[i] - auxiliar.pos_x[j]);
        int const suma_y = abs(auxiliar.pos_y[i] - auxiliar.pos_y[j]);
        int const suma_z = abs(auxiliar.pos_z[i] - auxiliar.pos_z[j]);
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

  // Función que crea la struct auxiliar
  int crear_auxiliar(vector<int> & num_bloques, struct Aux & auxiliar) {
    //Función que inicializa la estructura de bloques
    for (int k = 0; k < num_bloques[2]; k++) {
      for (int j = 0; j < num_bloques[1]; j++) {
        for (int i = 0; i < num_bloques[0]; i++) {
          int const codigo_id       = i + num_bloques[0] * (j + num_bloques[1] * k);
          auxiliar.pos_x[codigo_id] = i;
          auxiliar.pos_y[codigo_id] = j;
          auxiliar.pos_z[codigo_id] = k;
        }
      }
    }
    return 0;
  }
}  // namespace block