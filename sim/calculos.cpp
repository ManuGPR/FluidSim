//
// Created by marina on 30/09/23.
//
#include "calculos.hpp"

using namespace std;

namespace fisica {
  int calcular_operandos(struct Constantes & constantes) {
        const double op_1 = ((315 * constantes.masa) / (64 * PI_CONST * pow(constantes.h, 9.0)));
        const double op_2 = pow(constantes.h, 6) * op_1;
        const double op_3 = (15 * constantes.masa *3 * PRESION_DE_RIGIDEZ)/(PI_CONST * pow(constantes.h,6.0)*2 );
        const double op_4 = (45 / (PI_CONST * pow(constantes.h, 6.0))) * VISCOSIDAD * constantes.masa;
        const double h_c = constantes.h*constantes.h;
    constantes.operandos.push_back(op_1);
    constantes.operandos.push_back(op_2);
    constantes.operandos.push_back(op_3);
    constantes.operandos.push_back(op_4);
    constantes.operandos.push_back(h_c);
    return 0;
  }

  int inicializar_dens_acelera(struct Particula & part, int id_p){
    part.acel_x[id_p] = gravedad_x;
    part.acel_y[id_p] = gravedad_y;
    part.acel_z[id_p] = gravedad_z;
    part.dens[id_p] = 0.0;
    return 0;
  }

  void incremento_densidades(struct Particula & part, struct Constantes & constantes, vector<int> id_p) {
    // particula i== id_p[0] y particula j == id_p[1]
        const int cub = 3;
    double incremento = 0;
        const double diferencia = pow(part.pos_x[id_p[0]] - part.pos_x[id_p[1]], 2.0) +
                              pow(part.pos_y[id_p[0]] - part.pos_y[id_p[1]], 2.0) +
                              pow(part.pos_z[id_p[0]] - part.pos_z[id_p[1]], 2.0);

    if (diferencia < constantes.operandos[4]) {
      incremento = pow((constantes.operandos[4] - diferencia), cub);
    }
    part.dens[id_p[0]] += incremento;
    part.dens[id_p[1]] += incremento;
  }

  double trans_densidad(double incremento, struct Constantes & constantes) {
    return incremento * constantes.operandos[1] + constantes.operandos[2];
  }

  void trans_acele(struct Particula & part, vector<int> id_p, struct Constantes & constantes) {

        const double diferencia = pow(part.pos_x[id_p[0]] - part.pos_x[id_p[1]], 2.0)  + pow(part.pos_y[id_p[0]] - part.pos_y[id_p[1]], 2.0)
                              + pow(part.pos_z[id_p[0]] - part.pos_z[id_p[1]], 2.0);

    if (diferencia < constantes.operandos[4]) {
          const double distancia = sqrt(max(diferencia, 1e-12));
          const double operando_1 = constantes.operandos[2] * (pow((constantes.h - distancia), 2.0)  / distancia) *(part.dens[id_p[0]] + part.dens[id_p[1]] - 2 * DENSIDAD_DE_FLUIDO);
          const double denominador = part.dens[id_p[0]]* part.dens[id_p[1]];
          const double acl_x = ((part.pos_x[id_p[0]] - part.pos_x[id_p[1]])   * operando_1 + (part.vel_x[id_p[1]] -  part.vel_x[id_p[0]]) * constantes.operandos[3]) / denominador;
          const double acl_y = ((part.pos_y[id_p[0]] - part.pos_y[id_p[1]])* operando_1+ (part.vel_y[id_p[1]] -  part.vel_y[id_p[0]])* constantes.operandos[3] )/ denominador;
          const double acl_z = ((part.pos_z[id_p[0]] - part.pos_z[id_p[1]]) * operando_1 + (part.vel_z[id_p[1]] -  part.vel_z[id_p[0]])* constantes.operandos[3])/ denominador;

      part.acel_x[id_p[0]] += acl_x;
      part.acel_y[id_p[0]] += acl_y;
      part.acel_z[id_p[0]] += acl_z;
      part.acel_x[id_p[1]] -= acl_x;
      part.acel_y[id_p[1]] -= acl_y;
      part.acel_z[id_p[1]] -= acl_z;
    }

  }

  int col_mov(struct Particula & part, vector<int> const& num_bloques, int id_p){
    col_x(part, num_bloques, id_p);
    col_y(part, num_bloques, id_p);
    col_z(part, num_bloques, id_p);
    mov_part(part, id_p);
    return 0;
  }
  int interaccion(struct Particula & part, vector<int> const&  num_bloques, int id_p){
    int_x(part, num_bloques, id_p);
    int_y(part, num_bloques, id_p);
    int_z(part, num_bloques, id_p);
    return 0;
  }


  int mov_part(struct Particula & part, int id_p){
        const int cuadrado = 2;
    part.pos_x[id_p] = part.pos_x[id_p] + part.hv_x[id_p] * PASO_TIEMPO + part.acel_x[id_p] * pow(PASO_TIEMPO,cuadrado);
    part.pos_y[id_p] = part.pos_y[id_p] + part.hv_y[id_p] * PASO_TIEMPO + part.acel_y[id_p] * pow(PASO_TIEMPO,cuadrado);
    part.pos_z[id_p] = part.pos_z[id_p] + part.hv_z[id_p] * PASO_TIEMPO + part.acel_z[id_p] * pow(PASO_TIEMPO,cuadrado);

    part.vel_x[id_p] = part.hv_x[id_p] + (part.acel_x[id_p] * PASO_TIEMPO)/2;
    part.vel_y[id_p] = part.hv_y[id_p] + (part.acel_y[id_p] * PASO_TIEMPO)/2;
    part.vel_z[id_p] = part.hv_z[id_p] + (part.acel_z[id_p] * PASO_TIEMPO)/2;

    part.hv_x[id_p] = part.hv_x[id_p] + part.acel_x[id_p] * PASO_TIEMPO;
    part.hv_y[id_p] = part.hv_y[id_p] + part.acel_y[id_p] * PASO_TIEMPO;
    part.hv_z[id_p] = part.hv_z[id_p] + part.acel_z[id_p] * PASO_TIEMPO;
    return 0;
  }

  int col_x(struct Particula & part, vector<int> num_bloques, int id_p){
        const double dist_min = 1e-10;
    if ((part.loc_x[id_p] == 0) || (part.loc_x[id_p] == (num_bloques[0] - 1))) {
            const double nueva_x = part.pos_x[id_p] + part.hv_x[id_p] * PASO_TIEMPO;
      double dist_x = TAMANO_PARTICULAS;
      if (part.loc_x[id_p] == 0) {
        dist_x = dist_x - (nueva_x - lim_inf_x);
      }
      else {
        dist_x = dist_x - (lim_sup_x - nueva_x);
      }
      if (dist_x > dist_min) {
        if (part.loc_x[id_p] == 0) {
          part.acel_x[id_p] = part.acel_x[id_p] + (S_C * dist_x - D_V * part.vel_x[id_p]);
        }
        else {
          part.acel_x[id_p] = part.acel_x[id_p] - (S_C * dist_x + D_V * part.vel_x[id_p]);
        }
      }
    }
    return 0;
  }

  int col_y(struct Particula & part, vector<int> num_bloques, int id_p){
        const double dist_min = 1e-10;
    if ((part.loc_y[id_p] == 0) || (part.loc_y[id_p] == (num_bloques[1] - 1))) {
            const double nueva_y = part.pos_y[id_p] + part.hv_y[id_p] * PASO_TIEMPO;
      double dist_y = TAMANO_PARTICULAS;
      if (part.loc_y[id_p] == 0) {
        dist_y = dist_y - (nueva_y - lim_inf_y);
      }
      else {
        dist_y = dist_y - (lim_sup_y - nueva_y);
      }
      if (dist_y > dist_min) {
        if (part.loc_y[id_p] == 0) {
          part.acel_y[id_p] = part.acel_y[id_p] + (S_C * dist_y - D_V * part.vel_y[id_p]);
        }
        else {
          part.acel_y[id_p] = part.acel_y[id_p] - (S_C * dist_y + D_V * part.vel_y[id_p]);
        }
      }
    }
    return 0;
  }

  int col_z(struct Particula & part, vector<int> num_bloques, int id_p){
        const double dist_min = 1e-10;
    if ((part.loc_z[id_p] == 0) || (part.loc_z[id_p] == (num_bloques[2] - 1))) {
            const double nueva_z = part.pos_z[id_p] + part.hv_z[id_p] * PASO_TIEMPO;
      double dist_z = TAMANO_PARTICULAS;
      if (part.loc_z[id_p] == 0) {
        dist_z = dist_z - (nueva_z - lim_inf_z);
      }
      else {
        dist_z = dist_z - (lim_sup_z - nueva_z);
      }
      if (dist_z > dist_min) {
        if (part.loc_z[id_p] == 0) {
          part.acel_z[id_p] = part.acel_z[id_p] + (S_C * dist_z - D_V * part.vel_z[id_p]);
        }
        else {
          part.acel_z[id_p] = part.acel_z[id_p] - (S_C * dist_z + D_V * part.vel_z[id_p]);
        }
      }
    }
    return 0;
  }

  int int_x(struct Particula & part, vector<int> num_bloques, int id_p){
    if ((part.loc_x[id_p] == 0) || (part.loc_x[id_p] == (num_bloques[0] - 1))) {
      double dist_x = 0.0;
      if (part.loc_x[id_p] == 0) {
        dist_x = part.pos_x[id_p] - lim_inf_x;
      }
      else {
        dist_x = lim_sup_x - part.pos_x[id_p];
      }
      if (dist_x < 0) {
        if (part.loc_x[id_p] == 0) {
          part.pos_x[id_p] = lim_inf_x - dist_x;
        }
        else {
          part.pos_x[id_p] = lim_sup_x + dist_x;
        }
        part.vel_x[id_p] = -1*part.vel_x[id_p];
        part.hv_x[id_p] = -1*part.hv_x[id_p];
      }
    }
    return 0;
  }

  int int_y(struct Particula & part, vector<int> num_bloques, int id_p){
    if ((part.loc_y[id_p] == 0) || (part.loc_y[id_p] == (num_bloques[1] - 1))) {
      double dist_y = 0.0;
      if (part.loc_y[id_p] == 0) {
        dist_y = part.pos_y[id_p] - lim_inf_y;
      }
      else {
        dist_y = lim_sup_z - part.pos_y[id_p];
      }
      if (dist_y < 0) {
        if (part.loc_y[id_p] == 0) {
          part.pos_y[id_p] = lim_inf_y - dist_y;
        }
        else {
          part.pos_y[id_p] = lim_sup_y + dist_y;
        }
        part.vel_y[id_p] = -1*part.vel_y[id_p];
        part.hv_y[id_p] = -1*part.hv_y[id_p];
      }
    }
    return 0;
  }

  int int_z(struct Particula & part, vector<int> num_bloques, int id_p) {
    if ((part.loc_z[id_p] == 0) || (part.loc_z[id_p] == (num_bloques[2] - 1))) {
      double dist_z = 0;
      if (part.loc_z[id_p] == 0) {
        dist_z = part.pos_z[id_p] - lim_inf_z;
      } else {
        dist_z = lim_sup_z - part.pos_z[id_p];
      }
      if (dist_z < 0) {
        if (part.loc_z[id_p] == 0) {
          part.pos_z[id_p] = lim_inf_z - dist_z;
        } else {
          part.pos_z[id_p] = lim_sup_z + dist_z;
        }
        part.vel_z[id_p] = -1*part.vel_z[id_p];
        part.hv_z[id_p] = -1*part.hv_z[id_p];
      }
    }
    return 0;
  }

  int main_loop(struct Particula & particulas, struct Enclosure3D & malla, struct Constantes & constantes) {
    for (int time = 0; time < constantes.nts; time++) {
      bloque::loc_particula(particulas, malla); //actualizacion
      for(int i=0; i< malla.nps; i++) { fisica::inicializar_dens_acelera(particulas, i);}
      for (int i = 0; i < malla.nps; i++) {
        for (int j = i + 1; j < malla.nps; j++) {
          if (bloque::particula_contigua(particulas, i, j) == 1) {
                      const vector<int> part = {i, j};
            fisica::incremento_densidades(particulas, constantes, part);
          }
        }
        particulas.dens[i] = fisica::trans_densidad(particulas.dens[i], constantes);
      }
      //Mirar bucle de abajo para meter arriba
      for(int i = 0; i < malla.nps; i++) {
        for (int j = i + 1; j < malla.nps; j++) {
          if (bloque::particula_contigua(particulas, i, j) == 1) {
                      const vector<int> part = {i, j};
            fisica::trans_acele(particulas, part, constantes);} } }

      for (int i = 0; i < malla.nps; i++){
        fisica::col_mov(particulas, malla.num_bloques, i);
        fisica::interaccion(particulas, malla.num_bloques, i);}
    }
    return 0;}}