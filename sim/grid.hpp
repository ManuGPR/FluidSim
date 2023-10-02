//
// Created by marina on 27/09/23.
//

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

#ifndef ARQUITECTURA_GRID_HPP
#define ARQUITECTURA_GRID_HPP

using namespace std;

namespace malla {
    int num_bloques (vector<double> lim_sup, vector<double> lim_inf, double h, vector<int> result);
    int tam_bloques (vector<double> lim_sup, vector<double> lim_inf, vector<int> num_bloques, vector<double> result);
    int pos_particula_x (double pos_x, double xmin, double tam_bloque_x);
    int pos_particula_y (double pos_y, double ymin, double tam_bloque_y);
    int pos_particula_z (double pos_z, double zmin, double tam_bloque_z);
}

struct Enclosure3D{
    /*class members*/
    int np;
    vector<int> num_bloques;
    double iterations;

    /*member functions*/
    /* initialize all the vector arrays in the constructor */
    explicit Enclosure3D(int np, double iterations, vector<int> num_bloq) {
        /*constructor using parameters specified in cmd*/
        Enclosure3D::np = np;
        Enclosure3D::iterations = iterations;
        Enclosure3D::num_bloques[0] = num_bloq[0];
        Enclosure3D::num_bloques[1] = num_bloq[1];
        Enclosure3D::num_bloques[2] = num_bloq[2];
    }
    /* rest of member functions*/
};


struct Particula {
    /*class attributes*/
    vector<double> pos_x;
    vector<double> pos_y;
    vector<double> pos_z;
    vector<double> hv_x;
    vector<double> hv_y;
    vector<double> hv_z;
    vector<double> vel_x;
    vector<double> vel_y;
    vector<double> vel_z;
    vector<double> acel_x;
    vector<double> acel_y;
    vector<double> acel_z;
    vector<double> dens;
    vector<int> c_x;
    vector<int> c_y;
    vector<int> c_z;
    /*class methods*/
    explicit Particula(int np) : pos_x(np), pos_y(np), pos_z(np),
                                       hv_x(np), hv_y(np), hv_z(np),
                                       vel_x(np), vel_y(np), vel_z(np),
                                       acel_x(np),acel_y(np),acel_z(np),
                                       dens(np, 0.0),c_x(np),
                                       c_y(np), c_z(np){};
};
#endif //ARQUITECTURA_GRID_HPP
