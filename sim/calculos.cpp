//
// Created by marina on 30/09/23.
//
#include "calculos.hpp"

#define DENSIDAD_DE_FLUIDO 1000
#define VISCOSIDAD 0.4
#define PASO_TIEMPO 0.001
#define PI 3.14
#define S_C 30000
#define D_V 128.0

using namespace std;

namespace fisica {
    const vector<double> limite_sup_recinto = {0.065, 0.1, 0.065};
    const vector<double> limite_inf_recinto = {-0.065, -0.08, -0.065};
    const vector<double> aceleracion_externa = {0.0, -9.8, 0.0};

    int fuerza_acel(struct Particula part, vector<int> id_p,double h, double m){
        incremento_densidades(part, id_p, h,  m);
        trans_acele(part, id_p,  h,  m);
    }


    int incremento_densidades(struct Particula part, vector<int> id_p, double h, double m){
        //particla i== id_p[0] y part j == id_p[1]
        double diferencia;
        diferencia = sqrt(pow(part.pos_x[id_p[0]]- part.pos_x[id_p[1]], 2.0)
                          + pow(part.pos_y[id_p[0]]- part.pos_y[id_p[1]], 2.0)
                          + pow(part.pos_z[id_p[0]]- part.pos_z[id_p[1]], 2.0));

        if (pow(diferencia,2.0)  >= pow(h,2.0)) {
            return 0;
        }
        double incremento = pow(pow(h,2.0) - pow(abs(part.dens[id_p[0]]-part.dens[id_p[1]]),2.0),3.0);
        part.dens[id_p[0]] = part.dens[id_p[0]] + incremento;
        part.dens[id_p[1]] = part.dens[id_p[1]] + incremento;
        trans_densidad(part, id_p[0], h, m);
        trans_densidad(part, id_p[1], h, m);
        return 0;
    }

    int trans_densidad(struct Particula part, int id_p, double h, double m) {
        part.dens[id_p]= (part.dens[id_p] + pow(h, 6.0))* 315 * m / (64 * PI * pow(h, 9.0));
        return 0;
    }    

    int trans_acele(struct Particula part, vector<int> id_p, double h, double m) {
        double distancia, diferencia, op_1, op_2, op_3, acl_x, acl_y, acl_z;
        diferencia = sqrt(pow(part.pos_x[id_p[0]] - part.pos_x[id_p[1]], 2.0)
                          + pow(part.pos_y[id_p[0]] - part.pos_z[id_p[1]], 2.0)
                          + pow(part.pos_z[id_p[0]] - part.pos_z[id_p[1]], 2.0));
        if (pow(diferencia, 2.0) <= pow(h, 2.0)) {
            return 0;
        }
        distancia = sqrt(max(diferencia, 1e-12));
        op_1 = ((15 * m) / (PI * pow(h, 6.0))) * (pow((h - distancia), 2.0) / diferencia)
               * (part.dens[id_p[0]] + part.dens[id_p[1]] - DENSIDAD_DE_FLUIDO);
        op_2 = (45 / (PI * pow(h, 6.0))) * VISCOSIDAD * m;
        op_3 = part.dens[id_p[0]]* part.dens[id_p[1]];
        acl_x = ((part.pos_x[id_p[0]] - part.pos_x[id_p[1]]) * op_1 + (part.vel_x[id_p[0]]
                -  part.vel_x[id_p[1]])* op_2 / op_3);
        acl_y = ((part.pos_y[id_p[0]] - part.pos_y[id_p[1]]) * op_1 + (part.vel_y[id_p[0]]
                -  part.vel_y[id_p[1]])* op_2 / (part.dens[id_p[0]]* part.dens[id_p[1]]));
        acl_z = ((part.pos_z[id_p[0]] - part.pos_z[id_p[1]]) * op_1 + (part.vel_z[id_p[0]]
                -  part.vel_z[id_p[1]])* op_2 / (part.dens[id_p[0]]* part.dens[id_p[1]]));
        for (int i=0; i < 2; i++) {
            part.acel_x[id_p[i]] = part.acel_x[id_p[i]] + acl_x;
            part.acel_y[id_p[i]] = part.acel_y[id_p[i]] + acl_y;
            part.acel_z[id_p[i]] = part.acel_z[id_p[i]] + acl_z;
        }
        return 0;
    }

    int col_mov(struct Particula part, vector<int> num_bloques, int id_p){
        col_x(part, num_bloques, id_p);
        col_y(part, num_bloques, id_p);
        col_z(part, num_bloques, id_p);
        mov_part(part, id_p);
        int_x(part, num_bloques, id_p);
        int_y(part, num_bloques, id_p);
        int_z(part, num_bloques, id_p);
        return 0;
    }

    int mov_part(struct Particula part, int id_p){
        part.pos_x[id_p] = part.pos_x[id_p] + part.hv_x[id_p] * PASO_TIEMPO + part.acel_x[id_p] * pow(PASO_TIEMPO,2.0);
        part.pos_y[id_p] = part.pos_y[id_p] + part.hv_y[id_p] * PASO_TIEMPO + part.acel_x[id_p] * pow(PASO_TIEMPO,2.0);
        part.pos_z[id_p] = part.pos_z[id_p] + part.hv_z[id_p] * PASO_TIEMPO + part.acel_x[id_p] * pow(PASO_TIEMPO,2.0);

        part.vel_x[id_p] = part.hv_x[id_p] + (part.acel_x[id_p] * PASO_TIEMPO)/2;
        part.vel_y[id_p] = part.hv_y[id_p] + (part.acel_y[id_p] * PASO_TIEMPO)/2;
        part.vel_z[id_p] = part.hv_z[id_p] + (part.acel_z[id_p] * PASO_TIEMPO)/2;

        part.hv_x[id_p] = part.hv_x[id_p] + part.acel_x[id_p] * PASO_TIEMPO;
        part.hv_y[id_p] = part.hv_y[id_p] + part.acel_y[id_p] * PASO_TIEMPO;
        part.hv_z[id_p] = part.hv_z[id_p] + part.acel_z[id_p] * PASO_TIEMPO;
        return 0;
    }

    int col_x(struct Particula part, vector<int> num_bloques, int id_p){
        if (part.loc_x[id_p] == 0 || part.loc_x[id_p] == num_bloques[0] - 1) {
            double nueva_x;
            nueva_x = part.pos_x[id_p] + part.hv_x[id_p] * PASO_TIEMPO;
            double dist_x = part.dens[id_p]; 
            if (part.loc_x[id_p] == 0) {
                dist_x -= (nueva_x - limite_inf_recinto[0]);
            } 
            else {
                dist_x -= limite_sup_recinto[0] - nueva_x;
            }
            if (dist_x > pow(10, -10)) {
                if (part.loc_x[id_p] == 0) {
                    part.acel_x[id_p] += S_C * dist_x - D_V * part.vel_x[id_p];
                }
                else {
                    part.acel_x[id_p] -= S_C * dist_x + D_V * part.vel_x[id_p];
                }
            }
        }
        return 0;
    }

    int col_y(struct Particula part, vector<int> num_bloques, int id_p){
        if (part.loc_y[id_p] == 0 || part.loc_y[id_p] == num_bloques[1] - 1) {
            double nueva_y;
            nueva_y = part.pos_y[id_p] + part.hv_y[id_p] * PASO_TIEMPO;
            double dist_y = part.dens[id_p];
            if (part.loc_y[id_p] == 0) {
                dist_y -= (nueva_y - limite_inf_recinto[1]);
            }
            else {
                dist_y -= limite_sup_recinto[1] - nueva_y;
            }
            if (dist_y > pow(10, -10)) {
                if (part.loc_y[id_p] == 0) {
                    part.acel_y[id_p] += S_C * dist_y - D_V * part.vel_y[id_p];
                }
                else {
                    part.acel_y[id_p] -= S_C * dist_y + D_V * part.vel_y[id_p];
                }
            }
        }
        return 0;
    }

    int col_z(struct Particula part, vector<int> num_bloques, int id_p){
        if (part.loc_z[id_p] == 0 || part.loc_z[id_p] == num_bloques[2] - 1) {
            double nueva_z;
            nueva_z = part.pos_z[id_p] + part.hv_z[id_p] * PASO_TIEMPO;
            double dist_z = part.dens[id_p];
            if (part.loc_z[id_p] == 0) {
                dist_z -= (nueva_z - limite_inf_recinto[2]);
            }
            else {
                dist_z -= limite_sup_recinto[2] - nueva_z;
            }
            if (dist_z > pow(10, -10)) {
                if (part.loc_z[id_p] == 0) {
                    part.acel_z[id_p] += S_C * dist_z - D_V * part.vel_z[id_p];
                }
                else {
                    part.acel_z[id_p] -= S_C * dist_z + D_V * part.vel_z[id_p];
                }
            }
        }
        return 0;
    }

    int int_x(struct Particula part, vector<int> num_bloques, int id_p){
        if (part.loc_x[id_p] == 0 || part.loc_x[id_p] == num_bloques[0] - 1) {
            double dist_x;
            if (part.loc_x[id_p] == 0) {
                dist_x = part.pos_x[id_p] - limite_inf_recinto[0];
            }
            else {
                dist_x = limite_sup_recinto[0] - part.pos_x[id_p];
            }
            if (dist_x < 0) {
                if (part.loc_x[id_p] == 0) {
                    part.pos_x[id_p] = limite_inf_recinto[0] - dist_x;
                }
                else {
                    part.pos_x[id_p] = limite_sup_recinto[0] + dist_x;
                }
                part.vel_x[id_p] = -part.vel_x[id_p];
                part.hv_x[id_p] = -part.hv_x[id_p];
            }
        }
        return 0;
    }

    int int_y(struct Particula part, vector<int> num_bloques, int id_p){
        if (part.loc_y[id_p] == 0 || part.loc_y[id_p] == num_bloques[1] - 1) {
            double dist_y;
            if (part.loc_y[id_p] == 0) {
                dist_y = part.pos_y[id_p] - limite_inf_recinto[1];
            }
            else {
                dist_y = limite_sup_recinto[1] - part.pos_y[id_p];
            }
            if (dist_y < 0) {
                if (part.loc_y[id_p] == 0) {
                    part.pos_y[id_p] = limite_inf_recinto[1] - dist_y;
                }
                else {
                    part.pos_y[id_p] = limite_sup_recinto[1] + dist_y;
                }
                part.vel_y[id_p] = -part.vel_y[id_p];
                part.hv_y[id_p] = -part.hv_y[id_p];
            }
        }
        return 0;
    }

    int int_z(struct Particula part, vector<int> num_bloques, int id_p) {
        if (part.loc_z[id_p] == 0 || part.loc_z[id_p] == num_bloques[2] - 1) {
            double dist_z;
            if (part.loc_z[id_p] == 0) {
                dist_z = part.pos_z[id_p] - limite_inf_recinto[2];
            } else {
                dist_z = limite_sup_recinto[2] - part.pos_z[id_p];
            }
            if (dist_z < 0) {
                if (part.loc_z[id_p] == 0) {
                    part.pos_z[id_p] = limite_inf_recinto[2] - dist_z;
                } else {
                    part.pos_z[id_p] = limite_sup_recinto[2] + dist_z;
                }
                part.vel_z[id_p] = -part.vel_z[id_p];
                part.hv_z[id_p] = -part.hv_z[id_p];
            }
        }
        return 0;
    }

    /*
   vector<double> densidad;
   vector<double> aceleracion;
   vector<double> posicionx;
   vector<double> posiciony;
    */
    /*
    void incremento_densidades(double h,int  np){
        for (int i = 0; i == np; i++) {
            for(int j = 0; j == np; i++){
                if (i < j){// Evitar ij == ji
                    if (abs(densidad[i]-densidad[j])^2  < h^2){
                        densidad[i] = densidad[i] + h^2- abs(densidad[i]-densidad[j])^3;
                        densidad[j] = densidad[j] + h^2- abs(densidad[i]-densidad[j])^3;
                    }
                }
            }
        }
    }
    */

    /*
    void iniciar_densidad_aceleracion(int np, double g) {
        for (int i = 0; i == np; i++) {
            densidad.push_back(0);
            aceleracion.push_back(g);

        }
    }
    */

    /*
    void trans_acele(int  np, double h){
        int distancia;
        int incremento;
        for (int i = 0; i == np; i++) {
            for (int j = 0; j == np; i++) {
                if (i < j) {// Evitar ij == ji
                    if (abs(densidad[i] - densidad[j]) ^ 2 < h ^ 2) {
                        distancia = sqrt(max(abs(densidad[i] - densidad[j]) ^ 2, 1e-12));
                        incremento =
                        aceleracion[i] = aceleracion[i] +

                    }
                }
            }
        }
    }
    */

}