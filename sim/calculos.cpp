//
// Created by marina on 30/09/23.
//
#include "calculos.hpp"

using namespace std;

namespace fisica {
  int calcular_operandos(double & masa,double & h, vector<double> &operandos) {
    const double op_1 = ((315 * masa) / (64 * PI_CONST * pow(h, 9.0)));
    const double op_2 = pow(h, 6) * op_1;
    const double op_3 = (15 * masa *3 * PRESION_DE_RIGIDEZ)/(PI_CONST * pow(h,6.0)*2 );
    const double op_4 = (45 / (PI_CONST * pow(h, 6.0))) * VISCOSIDAD * masa;
    const double h_c = h*h;
    operandos.push_back(op_1);
    operandos.push_back(op_2);
    operandos.push_back(op_3);
    operandos.push_back(op_4);
    operandos.push_back(h_c);
    return 0;
  }

  int inicializar_dens_acelera(struct Particula & part, const int & id_p){
    part.acel_x[id_p] = gravedad_x;
    part.acel_y[id_p] = gravedad_y;
    part.acel_z[id_p] = gravedad_z;
    part.dens[id_p] = 0.0;
    return 0;
  }

  void incremento_densidades(Particula & part, double & operandos, const int & id_i, const int & id_j) {
    // particula i== id_p[0] y particula j == id_p[1]
    double incremento = 0;
    const double diferencia =
        ((part.pos_x[id_i] - part.pos_x[id_j])*(part.pos_x[id_i] - part.pos_x[id_j])) +
        ((part.pos_y[id_i] - part.pos_y[id_j])*(part.pos_y[id_i] - part.pos_y[id_j])) +
        ((part.pos_z[id_i] - part.pos_z[id_j])*(part.pos_z[id_i] - part.pos_z[id_j]));
    if (diferencia < operandos) {
      incremento = (operandos - diferencia)*(operandos - diferencia)*(operandos - diferencia);
    }
    part.dens[id_i] += incremento;
    part.dens[id_j] += incremento;
  }

  inline double trans_densidad(double & incremento, double & operando_1, double & operando_2) {
    return incremento * operando_1 + operando_2;
  }

  inline void trans_acele(struct Particula & part, const vector<int> & id_p, vector<double> & operandos, double & h) {
    const double diferencia = (part.pos_x[id_p[0]] - part.pos_x[id_p[1]]) *
                              (part.pos_x[id_p[0]] - part.pos_x[id_p[1]]) +
                              (part.pos_y[id_p[0]] - part.pos_y[id_p[1]]) *
                              (part.pos_y[id_p[0]] - part.pos_y[id_p[1]]) +
                              (part.pos_z[id_p[0]] - part.pos_z[id_p[1]]) *
                              (part.pos_z[id_p[0]] - part.pos_z[id_p[1]]);
    if (diferencia < operandos[4]) {
      const double distancia = sqrt(max(diferencia, 1e-12));
      const double operando_1 = operandos[2] * ((h - distancia)*(h - distancia)  / distancia) *
                                (part.dens[id_p[0]] + part.dens[id_p[1]] - 2 * DENSIDAD_DE_FLUIDO);
      const double denominador = part.dens[id_p[0]]* part.dens[id_p[1]];
      const double acl_x = ((part.pos_x[id_p[0]] - part.pos_x[id_p[1]]) * operando_1 +
                   (part.vel_x[id_p[1]] -  part.vel_x[id_p[0]]) * operandos[3]) / denominador;
      const double acl_y = ((part.pos_y[id_p[0]] - part.pos_y[id_p[1]]) * operando_1 +
                   (part.vel_y[id_p[1]] -  part.vel_y[id_p[0]]) * operandos[3] )/ denominador;
      const double acl_z = ((part.pos_z[id_p[0]] - part.pos_z[id_p[1]]) * operando_1 +
                   (part.vel_z[id_p[1]] -  part.vel_z[id_p[0]])* operandos[3])/ denominador;

      part.acel_x[id_p[0]] += acl_x;
      part.acel_y[id_p[0]] += acl_y;
      part.acel_z[id_p[0]] += acl_z;
      part.acel_x[id_p[1]] -= acl_x;
      part.acel_y[id_p[1]] -= acl_y;
      part.acel_z[id_p[1]] -= acl_z;
    }}

  int col_mov(struct Particula & part, vector<int> const & num_bloques, const int & id_p){
    if ((part.loc_x[id_p] == 0) || (part.loc_x[id_p] == (num_bloques[0] - 1))) {
      col_x(part, id_p);
    }
    if ((part.loc_y[id_p] == 0) || (part.loc_y[id_p] == (num_bloques[1] - 1))) {
      col_y(part, id_p);
    }
    if ((part.loc_z[id_p] == 0) || (part.loc_z[id_p] == (num_bloques[2] - 1))) {
      col_z(part, id_p);
    }
    mov_part(part, id_p);
    return 0;
  }

  int interaccion(Particula & part, vector<int> const & num_bloques, const int & id_p) {
    if ((part.loc_x[id_p] == 0) || (part.loc_x[id_p] == (num_bloques[0] - 1))) {
      int_x(part, id_p);
    }
    if ((part.loc_y[id_p] == 0) || (part.loc_y[id_p] == (num_bloques[1] - 1))) {
      int_y(part, id_p);
    }
    if ((part.loc_z[id_p] == 0) || (part.loc_z[id_p] == (num_bloques[2] - 1))) {
      int_z(part, id_p);
    }
    return 0;
  }

  int mov_part(struct Particula & part, const int & id_p){
    const double paso_tiempo_cuadrado = PASO_TIEMPO * PASO_TIEMPO;
    part.pos_x[id_p] = part.pos_x[id_p] + part.hv_x[id_p] * PASO_TIEMPO +
                       part.acel_x[id_p] * paso_tiempo_cuadrado;
    part.pos_y[id_p] = part.pos_y[id_p] + part.hv_y[id_p] * PASO_TIEMPO +
                       part.acel_y[id_p] * paso_tiempo_cuadrado;
    part.pos_z[id_p] = part.pos_z[id_p] + part.hv_z[id_p] * PASO_TIEMPO +
                       part.acel_z[id_p] * paso_tiempo_cuadrado;

    part.vel_x[id_p] = part.hv_x[id_p] + (part.acel_x[id_p] * PASO_TIEMPO)/2;
    part.vel_y[id_p] = part.hv_y[id_p] + (part.acel_y[id_p] * PASO_TIEMPO)/2;
    part.vel_z[id_p] = part.hv_z[id_p] + (part.acel_z[id_p] * PASO_TIEMPO)/2;

    part.hv_x[id_p] = part.hv_x[id_p] + part.acel_x[id_p] * PASO_TIEMPO;
    part.hv_y[id_p] = part.hv_y[id_p] + part.acel_y[id_p] * PASO_TIEMPO;
    part.hv_z[id_p] = part.hv_z[id_p] + part.acel_z[id_p] * PASO_TIEMPO;
    return 0;
  }

  int col_x(struct Particula & part, const int & id_p){
    const double nueva_x = part.pos_x[id_p] + part.hv_x[id_p] * PASO_TIEMPO;
    double dist_x = TAMANO_PARTICULAS;
    if (part.loc_x[id_p] == 0) {
      dist_x -= (nueva_x - lim_inf_x);
      if (dist_x > distancia_minima) {
        part.acel_x[id_p] += (S_C * dist_x - D_V * part.vel_x[id_p]);
      }
    }
    else {
      dist_x -= (lim_sup_x - nueva_x);
      if (dist_x > distancia_minima) {
        part.acel_x[id_p] -= (S_C * dist_x + D_V * part.vel_x[id_p]);
      }
    }
    return 0;
  }

  int col_y(struct Particula & part, const int & id_p){
    const double nueva_y = part.pos_y[id_p] + part.hv_y[id_p] * PASO_TIEMPO;
      double dist_y = TAMANO_PARTICULAS;
      if (part.loc_y[id_p] == 0) {
        dist_y -= (nueva_y - lim_inf_y);
        if (dist_y > distancia_minima) {
          part.acel_y[id_p] += (S_C * dist_y - D_V * part.vel_y[id_p]);
        }
      }
      else {
        dist_y -= (lim_sup_y - nueva_y);
        if (dist_y > distancia_minima)  {
          part.acel_y[id_p] -= (S_C * dist_y + D_V * part.vel_y[id_p]);
        }
      }
    return 0;
  }

  int col_z(struct Particula & part, const int & id_p){
    const double nueva_z = part.pos_z[id_p] + part.hv_z[id_p] * PASO_TIEMPO;
    double dist_z = TAMANO_PARTICULAS;
    if (part.loc_z[id_p] == 0) {
      dist_z = dist_z - (nueva_z - lim_inf_z);
      if (dist_z > distancia_minima) {
        part.acel_z[id_p] += (S_C * dist_z - D_V * part.vel_z[id_p]);
      }
    }
    else {
      dist_z = dist_z - (lim_sup_z - nueva_z);
      if (dist_z > distancia_minima) {
        part.acel_z[id_p] -= (S_C * dist_z + D_V * part.vel_z[id_p]);
      }
    }
    return 0;
  }

  int int_x(struct Particula & part, const int & id_p){
    if (part.loc_x[id_p] == 0) {
      const double dist_x = part.pos_x[id_p] - lim_inf_x;
      if (dist_x < 0) {
        part.pos_x[id_p] = lim_inf_x - dist_x;
        part.vel_x[id_p] = -part.vel_x[id_p];
        part.hv_x[id_p]  = -part.hv_x[id_p];
      }
    }
    else {
      const double dist_x = lim_sup_x - part.pos_x[id_p];
      if (dist_x < 0) {
        part.pos_x[id_p] = lim_sup_x + dist_x;
        part.vel_x[id_p] = -part.vel_x[id_p];
        part.hv_x[id_p]  = -part.hv_x[id_p];
      }
    }
    return 0;
  }

  int int_y(struct Particula & part, const int & id_p){
    if (part.loc_y[id_p] == 0) {
      const double dist_y = part.pos_y[id_p] - lim_inf_y;
      if (dist_y < 0) {
        part.pos_y[id_p] = lim_inf_y - dist_y;
        part.vel_y[id_p] = -1*part.vel_y[id_p];
        part.hv_y[id_p] = -1*part.hv_y[id_p];
      }
    }
    else {
      const double dist_y = lim_sup_z - part.pos_y[id_p];
      if (dist_y < 0) {
        part.pos_y[id_p] = lim_sup_y + dist_y;
        part.vel_y[id_p] = -1*part.vel_y[id_p];
        part.hv_y[id_p] = -1*part.hv_y[id_p];
      }
    }
    return 0;
  }

  int int_z(struct Particula & part, const int & id_p) {
    if (part.loc_z[id_p] == 0) {
      const double dist_z = part.pos_z[id_p] - lim_inf_z;
      if (dist_z < 0) {
        part.pos_z[id_p] = lim_inf_z - dist_z;
        part.vel_z[id_p] = -part.vel_z[id_p];
        part.hv_z[id_p] = -part.hv_z[id_p];
      }
    }
    else {
      const double dist_z = lim_sup_z - part.pos_z[id_p];
      if (dist_z < 0) {
        part.pos_z[id_p] = lim_sup_z + dist_z;
        part.vel_z[id_p] = -part.vel_z[id_p];
        part.hv_z[id_p] = -part.hv_z[id_p];
      }
    }
    return 0;
  }

  int main_loop(struct Particula & particulas, struct Enclosure3D & malla, struct Constantes & constantes, vector <struct bloque::Bloque> & bloques) {
    for (int time = constantes.nts; time > 0; time--) {
      bloque::loc_particula_bucle(particulas, malla, malla.num_bloques, bloques); //actualizacion
      const int num_bloques_total = malla.num_bloques[0] * malla.num_bloques[1] * malla.num_bloques[2];
      const int it_bloque = num_bloques_total - 1;
      for(int i=malla.nps - 1; i >= 0; i--) {fisica::inicializar_dens_acelera(particulas, i);}
      for (int bloque = it_bloque; bloque >= 0; bloque--) {
        for (const int part_1 : bloques[bloque].lista_particulas) {
          for (const int bloques_cont : bloques[bloque].bloque_contiguo) {
            for (const int part_2 : bloques[bloques_cont].lista_particulas) {
              if (part_1 < part_2) {
                fisica::incremento_densidades(particulas, constantes.operandos[4], part_1, part_2);
              }
            }
          }
        }
      }

      for (int part_1 = malla.nps - 1; part_1 >= 0; part_1--){
        particulas.dens[part_1] = fisica::trans_densidad(particulas.dens[part_1], constantes.operandos[0], constantes.operandos[1]);
      }
      for (int bloque = it_bloque; bloque >= 0; bloque--) {
        for (const int part_1: bloques[bloque].lista_particulas) {
          for (const int bloques_cont: bloques[it_bloque].bloque_contiguo){
            for (const int part_2: bloques[bloques_cont].lista_particulas) {
              if (part_1 < part_2) {
                const vector<int> part = {part_1, part_2};
                fisica::trans_acele(particulas, part, constantes.operandos, constantes.h);
              }
            }
          }
        }
      }

      for (int part_1 = 0; part_1 < malla.nps; ++part_1) {
       fisica::col_mov(particulas, malla.num_bloques, part_1);
       fisica::interaccion(particulas, malla.num_bloques, part_1);
      }
    }
    return 0;}}
