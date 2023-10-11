//
// Created by marina on 27/09/23.
//

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "constants.hpp"

#ifndef ARQUITECTURA_GRID_HPP
#define ARQUITECTURA_GRID_HPP

using namespace std;

//NameSpace que tiene funciones sobre la malla
namespace malla {

}

struct Enclosure3D{
    /*class members*/
    int np;
    vector<int> num_bloques;
    double iterations;

    /*member functions*/
    /* initialize all the vector arrays in the constructor */
    explicit Enclosure3D(int np, double iterations, vector<int> & num_bloq) {
        /*constructor using parameters specified in cmd*/
        Enclosure3D::np = np;
        Enclosure3D::iterations = iterations;
        Enclosure3D::num_bloques.push_back(num_bloq[0]);
        Enclosure3D::num_bloques.push_back(num_bloq[1]);
        Enclosure3D::num_bloques.push_back(num_bloq[2]);
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
    vector<int> loc_x;
    vector<int> loc_y;
    vector<int> loc_z;
    /*class methods*/
    explicit Particula(int np) : pos_x(np, 0.0), pos_y(np, 0.0), pos_z(np, 0.0),
                                 hv_x(np, 0.0), hv_y(np, 0.0), hv_z(np, 0.0),
                                 vel_x(np, 0.0), vel_y(np, 0.0), vel_z(np, 0.0),
                                 acel_x(np, acel_ex[0]), acel_y(np, acel_ex[1]),
                                 acel_z(np, acel_ex[2]), dens(np, 0.0),
                                 loc_x(np, 0), loc_y(np, 0), loc_z(np, 0){};
};
#endif //ARQUITECTURA_GRID_HPP