#include "calculos.hpp"

using namespace std;

namespace calc {
  // Función que calcula los operandos de las ecuaciones
  int calcular_operandos(double & masa, double & h, vector<double> & operandos) {
    double const op_1 = ((315 * masa) / (64 * std::numbers::pi * pow(h, 9.0)));
    double const op_2 = pow(h, 6) * op_1;
    double const op_3 = (15 * masa * 3 * presion_de_rigidez) / (std::numbers::pi * pow(h, 6.0) * 2);
    double const op_4 = (45 / (std::numbers::pi * pow(h, 6.0))) * viscosidad * masa;
    double const h_c  = h * h;
    operandos.push_back(op_1);
    operandos.push_back(op_2);
    operandos.push_back(op_3);
    operandos.push_back(op_4);
    operandos.push_back(h_c);
    return 0;
  }

  // Función que inicializa la densidad y la aceleración de las partículas (Paso 4.3.2.1)
  int inicializar_dens_acel(Particula & part, int id_p) {
    part.acel_x[id_p] = gravedad_x;
    part.acel_y[id_p] = gravedad_y;
    part.acel_z[id_p] = gravedad_z;
    part.dens[id_p]   = 0.0;
    return 0;
  }

  // Función que incrementa las densidades (Paso 4.3.2.2)
  void incremento_densidades(Particula & part, double & operandos, vector<int> const & id_p,
                             double & diferencia) {
    // particula i== id_p[0] y particula j == id_p[1]
    double const incremento =
        (operandos - diferencia) * (operandos - diferencia) * (operandos - diferencia);
    part.dens[id_p[0]] += incremento;
    part.dens[id_p[1]] += incremento;
  }

  // Función que realiza una transformación de las densidades (Paso 4.3.2.3)
  inline double trans_densidad(double & incremento, double & operando_1, double & operando_2) {
    return incremento * operando_1 + operando_2;
  }

  // Función que realiza la transferencia de aceleración (Paso 4.3.2.4)
  inline void trans_acele(Particula & part, vector<int> const & id_p, Constantes & constantes,
                          double const & diferencia) {
    double const distancia = sqrt(max(diferencia, 1e-12));
    double const operando_1 =
        constantes.operandos[2] *
        ((constantes.h - distancia) * (constantes.h - distancia) / distancia) *
        (part.dens[id_p[0]] + part.dens[id_p[1]] - 2 * densidad_de_fluido);
    double const denominador = part.dens[id_p[0]] * part.dens[id_p[1]];
    double const acl_x       = ((part.pos_x[id_p[0]] - part.pos_x[id_p[1]]) * operando_1 +
                          (part.vel_x[id_p[1]] - part.vel_x[id_p[0]]) * constantes.operandos[3]) /
                         denominador;
    double const acl_y = ((part.pos_y[id_p[0]] - part.pos_y[id_p[1]]) * operando_1 +
                          (part.vel_y[id_p[1]] - part.vel_y[id_p[0]]) * constantes.operandos[3]) /
                         denominador;
    double const acl_z = ((part.pos_z[id_p[0]] - part.pos_z[id_p[1]]) * operando_1 +
                          (part.vel_z[id_p[1]] - part.vel_z[id_p[0]]) * constantes.operandos[3]) /
                         denominador;
    part.acel_x[id_p[0]] += acl_x;
    part.acel_y[id_p[0]] += acl_y;
    part.acel_z[id_p[0]] += acl_z;
    part.acel_x[id_p[1]] -= acl_x;
    part.acel_y[id_p[1]] -= acl_y;
    part.acel_z[id_p[1]] -= acl_z;
  }

  // Función que llama a mov_part, col_x, col_y y col_z
  int col_mov(Particula & part, vector<int> const & num_bloques, int id_p) {
    if ((part.loc_x[id_p] == 0) || (part.loc_x[id_p] == (num_bloques[0] - 1))) {
      calc::col_x(part, id_p);
    }
    if ((part.loc_y[id_p] == 0) || (part.loc_y[id_p] == (num_bloques[1] - 1))) {
      calc::col_y(part, id_p);
    }
    if ((part.loc_z[id_p] == 0) || (part.loc_z[id_p] == (num_bloques[2] - 1))) {
      calc::col_z(part, id_p);
    }
    calc::mov_part(part, id_p);
    return 0;
  }

  // Función grande que llama int_x, int_y e int_z
  int interaccion(Particula & part, vector<int> const & num_bloques, int id_p) {
    if ((part.loc_x[id_p] == 0) || (part.loc_x[id_p] == (num_bloques[0] - 1))) {
      calc::int_x(part, id_p);
    }
    if ((part.loc_y[id_p] == 0) || (part.loc_y[id_p] == (num_bloques[1] - 1))) {
      calc::int_y(part, id_p);
    }
    if ((part.loc_z[id_p] == 0) || (part.loc_z[id_p] == (num_bloques[2] - 1))) {
      calc::int_z(part, id_p);
    }
    return 0;
  }

  // Función que realiza la actualización de la vel, pos y hv (Paso 4.3.4)
  int mov_part(Particula & part, int id_p) {
    part.pos_x[id_p] = part.pos_x[id_p] + part.hv_x[id_p] * paso_tiempo +
                       part.acel_x[id_p] * paso_tiempo * paso_tiempo;
    part.pos_y[id_p] = part.pos_y[id_p] + part.hv_y[id_p] * paso_tiempo +
                       part.acel_y[id_p] * paso_tiempo * paso_tiempo;
    part.pos_z[id_p] = part.pos_z[id_p] + part.hv_z[id_p] * paso_tiempo +
                       part.acel_z[id_p] * paso_tiempo * paso_tiempo;

    part.vel_x[id_p] = part.hv_x[id_p] + (part.acel_x[id_p] * paso_tiempo) / 2;
    part.vel_y[id_p] = part.hv_y[id_p] + (part.acel_y[id_p] * paso_tiempo) / 2;
    part.vel_z[id_p] = part.hv_z[id_p] + (part.acel_z[id_p] * paso_tiempo) / 2;

    part.hv_x[id_p] = part.hv_x[id_p] + part.acel_x[id_p] * paso_tiempo;
    part.hv_y[id_p] = part.hv_y[id_p] + part.acel_y[id_p] * paso_tiempo;
    part.hv_z[id_p] = part.hv_z[id_p] + part.acel_z[id_p] * paso_tiempo;
    return 0;
  }

  // Funciones vectoriales que realizan la colisión entre partículas (Paso 4.3.3)
  int col_x(Particula & part, int id_p) {
    double const nueva_x = part.pos_x[id_p] + part.hv_x[id_p] * paso_tiempo;
    double dist_x        = tamano_particulas;
    if (part.loc_x[id_p] == 0) {
      dist_x -= (nueva_x - lim_inf_x);
      if (dist_x > distancia_minima) {
        part.acel_x[id_p] += (s_c * dist_x - d_v * part.vel_x[id_p]);
      }
    } else {
      dist_x -= (lim_sup_x - nueva_x);
      if (dist_x > distancia_minima) {
        part.acel_x[id_p] -= (s_c * dist_x + d_v * part.vel_x[id_p]);
      }
    }
    return 0;
  }

  int col_y(Particula & part, int id_p) {
    double const nueva_y = part.pos_y[id_p] + part.hv_y[id_p] * paso_tiempo;
    double dist_y        = tamano_particulas;
    if (part.loc_y[id_p] == 0) {
      dist_y -= (nueva_y - lim_inf_y);
      if (dist_y > distancia_minima) {
        part.acel_y[id_p] += (s_c * dist_y - d_v * part.vel_y[id_p]);
      }
    } else {
      dist_y -= (lim_sup_y - nueva_y);
      if (dist_y > distancia_minima) {
        part.acel_y[id_p] -= (s_c * dist_y + d_v * part.vel_y[id_p]);
      }
    }
    return 0;
  }

  int col_z(Particula & part, int id_p) {
    double const nueva_z = part.pos_z[id_p] + part.hv_z[id_p] * paso_tiempo;
    double dist_z        = tamano_particulas;
    if (part.loc_z[id_p] == 0) {
      dist_z = dist_z - (nueva_z - lim_inf_z);
      if (dist_z > distancia_minima) {
        part.acel_z[id_p] += (s_c * dist_z - d_v * part.vel_z[id_p]);
      }
    } else {
      dist_z = dist_z - (lim_sup_z - nueva_z);
      if (dist_z > distancia_minima) {
        part.acel_z[id_p] -= (s_c * dist_z + d_v * part.vel_z[id_p]);
      }
    }
    return 0;
  }

  // Funciones vectoriales que realizan la colisión entre partículas (Paso 4.3.5)
  int int_x(Particula & part, int id_p) {
    if (part.loc_x[id_p] == 0) {
      double const dist_x = part.pos_x[id_p] - lim_inf_x;
      if (dist_x < 0) {
        part.pos_x[id_p] = lim_inf_x - dist_x;
        part.vel_x[id_p] = -part.vel_x[id_p];
        part.hv_x[id_p]  = -part.hv_x[id_p];
      }
    } else {
      double const dist_x = lim_sup_x - part.pos_x[id_p];
      if (dist_x < 0) {
        part.pos_x[id_p] = lim_sup_x + dist_x;
        part.vel_x[id_p] = -part.vel_x[id_p];
        part.hv_x[id_p]  = -part.hv_x[id_p];
      }
    }
    return 0;
  }

  int int_y(Particula & part, int id_p) {
    if (part.loc_y[id_p] == 0) {
      double const dist_y = part.pos_y[id_p] - lim_inf_y;
      if (dist_y < 0) {
        part.pos_y[id_p] = lim_inf_y - dist_y;
        part.vel_y[id_p] = -part.vel_y[id_p];
        part.hv_y[id_p]  = -part.hv_y[id_p];
      }
    } else {
      double const dist_y = lim_sup_y - part.pos_y[id_p];
      if (dist_y < 0) {
        part.pos_y[id_p] = lim_sup_y + dist_y;
        part.vel_y[id_p] = -part.vel_y[id_p];
        part.hv_y[id_p]  = -part.hv_y[id_p];
      }
    }
    return 0;
  }

  int int_z(Particula & part, int id_p) {
    if (part.loc_z[id_p] == 0) {
      double const dist_z = part.pos_z[id_p] - lim_inf_z;
      if (dist_z < 0) {
        part.pos_z[id_p] = lim_inf_z - dist_z;
        part.vel_z[id_p] = -part.vel_z[id_p];
        part.hv_z[id_p]  = -part.hv_z[id_p];
      }
    } else {
      double const dist_z = lim_sup_z - part.pos_z[id_p];
      if (dist_z < 0) {
        part.pos_z[id_p] = lim_sup_z + dist_z;
        part.vel_z[id_p] = -part.vel_z[id_p];
        part.hv_z[id_p]  = -part.hv_z[id_p];
      }
    }
    return 0;
  }

  // Main loop, se encarga de aplicar las funciones del procesamiento de la simulación (Paso 4.3)
  int main_loop(Particula & particulas, Enclosure3D & malla, Constantes & constantes,
                vector<block::Bloque> & bloques) {
    for (int time = constantes.nts; time > 0; time--) {
      block::loc_particula_bucle(particulas, malla, malla.num_bloques, bloques);  // actualizacion
      int const num_bloques_total = block::total_bloques(malla.num_bloques);
      int const it_bloque         = num_bloques_total - 1;
      for (int i = malla.nps - 1; i >= 0; i--) { calc::inicializar_dens_acel(particulas, i); }
      calc::bucle_incremento_densidades(particulas, constantes, bloques, it_bloque);
      for (int part_1 = malla.nps - 1; part_1 >= 0; part_1--) {
        particulas.dens[part_1] = calc::trans_densidad(
            particulas.dens[part_1], constantes.operandos[0], constantes.operandos[1]);
      }
      calc::bucle_trans(particulas, constantes, bloques, it_bloque);
      for (int part_1 = 0; part_1 < malla.nps; ++part_1) {
        calc::col_mov(particulas, malla.num_bloques, part_1);
        calc::interaccion(particulas, malla.num_bloques, part_1);
      }
    }
    return 0;
  }

  // Función que se encarga de realizar la parte explicada en el punto 4.3.2.4
  int bucle_trans(Particula & particulas, Constantes & constantes, vector<block::Bloque> & bloques,
                  int it_bloque) {
    for (int bloque = it_bloque; bloque >= 0; bloque--) {
      for (int const bloques_cont : bloques[bloque].bloque_contiguo) {
        for (int const part_1 : bloques[bloque].lista_particulas) {
          for (int const part_2 : bloques[bloques_cont].lista_particulas) {
            if (part_1 < part_2) {
              double const diferencia = (particulas.pos_x[part_1] - particulas.pos_x[part_2]) *
                                            (particulas.pos_x[part_1] - particulas.pos_x[part_2]) +
                                        (particulas.pos_y[part_1] - particulas.pos_y[part_2]) *
                                            (particulas.pos_y[part_1] - particulas.pos_y[part_2]) +
                                        (particulas.pos_z[part_1] - particulas.pos_z[part_2]) *
                                            (particulas.pos_z[part_1] - particulas.pos_z[part_2]);
              if (diferencia < constantes.operandos[4]) {
                vector<int> const part = {part_1, part_2};
                calc::trans_acele(particulas, part, constantes, diferencia);
              }
            }
          }
        }
      }
    }
    return 0;
  }

  // Función que se encarga de realizar la parte explicada en el punto 4.3.2.2
  int bucle_incremento_densidades(Particula & particulas, Constantes & constantes,
                                  vector<block::Bloque> & bloques, int it_bloque) {
    for (int bloque = it_bloque; bloque >= 0; bloque--) {
      for (int const part_1 : bloques[bloque].lista_particulas) {
        for (int const bloques_cont : bloques[bloque].bloque_contiguo) {
          for (int const part_2 : bloques[bloques_cont].lista_particulas) {
            if (part_1 < part_2) {
              double diferencia = ((particulas.pos_x[part_1] - particulas.pos_x[part_2]) *
                                   (particulas.pos_x[part_1] - particulas.pos_x[part_2])) +
                                  ((particulas.pos_y[part_1] - particulas.pos_y[part_2]) *
                                   (particulas.pos_y[part_1] - particulas.pos_y[part_2])) +
                                  ((particulas.pos_z[part_1] - particulas.pos_z[part_2]) *
                                   (particulas.pos_z[part_1] - particulas.pos_z[part_2]));
              if (diferencia < constantes.operandos[4]) {
                vector<int> const part = {part_1, part_2};
                calc::incremento_densidades(particulas, constantes.operandos[4], part, diferencia);
              }
            }
          }
        }
      }
    }
    return 0;
  }

}  // namespace calc