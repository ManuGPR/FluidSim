//
// Created by manu on 5/10/23.
//

#include <fstream>
#include <string.h>
#include "progargs.hpp"
#include "grid.hpp"


#ifndef AC3_FILE_HPP
#define AC3_FILE_HPP

using namespace std;

namespace ficheros {
    //Función que se encarga de leer la cabecera
    double lectura_cabecera(ifstream & file_in);
    //Función que se encarga de leer un objeto del fichero, hacer el cast a double y lo devuelve
    double lectura_float_to_double (ifstream & fichero); //Meter esta función en un fichero con funciones de lectura
    //Función que se encarga de leer el fichero
    int lectura_file (ifstream & file_in, struct Particula particulas);
    //Función que se encarga de la escritura del fichero de salida
    int escritura_salida(ofstream & file_out, struct Particula particulas);
    //Función que castea un entero a un char*
    const char* int_to_str(int parameter);
    //Función que castea un doble a un char*
    const char* double_to_str(double parameter);
}


#endif //AC3_FILE_HPP
