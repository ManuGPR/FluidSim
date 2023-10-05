//
// Created by manu on 5/10/23.
//

#include <fstream>
#include <cstring>
#include <tuple>
#include "progargs.hpp"
#include "grid.hpp"
#include "block.hpp"


#ifndef AC3_FILE_HPP
#define AC3_FILE_HPP
const vector<double> limite_sup_recinto = {0.065, 0.1, 0.065};
const vector<double> limite_inf_recinto = {-0.065, -0.08, -0.065};
using namespace std;

namespace ficheros {
    //Función que se encarga de leer la cabecera
    tuple <int, double> lectura_cabecera(ifstream & file_in);
    //Función que se encarga de leer un objeto del fichero, hacer el cast a double y lo devuelve
    double lectura_float_to_double (ifstream & fichero); //Meter esta función en un fichero con funciones de lectura
    //Función que se encarga de leer el fichero
    int lectura_file (ifstream & file_in, int np, struct Particula & particulas);
    //Función que se encarga de la escritura del fichero de salida
    int escritura_salida(ofstream & file_out, struct Particula & particulas, double ppm, int np);
    //Función que castea un entero a un char*
    const char* int_to_str(int parameter);
    //Función que castea un doble a un char*
    const char* double_to_str(double parameter);
}


#endif //AC3_FILE_HPP
