//
// Created by marina on 27/09/23.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "../sim/progargs.hpp"
#include "../sim/grid.hpp"
#include "../sim/file.hpp"

//CONSTANTES ESCALARES DE SIMULACIÓN (hay que poner const no define)
const double RADIO = 1.695;
const int DENSIDAD_DE_FLUIDO = 1000;
const double PRECISION_DE_RIGIDEZ = 3.0;
const int S_C = 30000;
const double D_V = 128.0;
const double VISCOSIDAD = 0.4;
const double TAMANO_PARTICULAS = 0.0002;
const double PASO_TIEMPO = 0.001;

//CONSTANTES VECTORIALES DE LA SIMULACIÓN
const vector<double> aceleracion_ex = {0.0, -9.8, 0.0};
const vector<double> limite_sup_recinto = {0.065, 0.1, 0.065};
const vector<double> limite_inf_recinto = {-0.065, -0.08, -0.065};

const char* input_file = "in.fld";
const char* output_file = "out.fld";

using namespace std;

int main(int argc, char **argv) {
    int nts,np; //nts = numero de pasos de tiempo, np = numero de particulas
    double ppm,np_d; //ppm = partículas por metro
    ifstream file_in; //file_in = fichero de entrada
    ofstream file_out; //file_out = fichero de salida

    //Funcion de checkeo maestra de parametros
    nts = entry::check_param(argc, argv);
    if (nts < 0) {return nts;}

    //Apertura del fichero y cabecera
    file_in.open(argv[2], ios::binary);
    np_d, ppm  = ficheros::lectura_cabecera(file_in);
    np = static_cast<int>(np_d);



    //Cálculos de m y h
    double masa = (DENSIDAD_DE_FLUIDO) / (pow(ppm, 3));
    double longitud_de_suavizado = (RADIO / ppm);

    //Calculo del numero de bloques
    vector<int> num_bloques(3);
    malla::num_bloques(limite_sup_recinto, limite_inf_recinto, longitud_de_suavizado, num_bloques);

    //Inicialización de los objetos
    struct Particula particulas(np);
    struct Enclosure3D malla(np, nts, num_bloques);

    //LECTURA DEL FICHERO (Mover esta lectura a una función file_read en el fichero de ficheros)

    ficheros::lectura_file(file_in, np, particulas);

    /*
     * if entry::check_np_equal(argv[2]) == -5){
     *  std::cerr << "Number of particles mismatch. Header:" << np ", Found:" << nps;
     *  return -5;
     *  }
     */

}