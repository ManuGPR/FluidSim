//
// Created by marina on 27/09/23.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "../sim/progargs.hpp"
#include "../sim/grid.hpp"

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

using namespace std;

int main(int argc, char **argv) {
    // Constantes vectoriales de la simulación (hay que sacarlas)
    const vector<double> aceleracion_externa = {0.0, -9.8, 0.0};
    const vector<double> limite_sup_recinto = {0.065, 0.1, 0.065};
    const vector<double> limite_inf_recinto = {-0.065, -0.08, -0.065};

    //Variables de fluid
    int nts, np; //nts = numero de pasos de tiempo, np = numero de particulas
    float ppm_float; //ppm_float = variable auxiliar para convertir ppm a double
    double ppm; //ppm = partículas por metro
    ifstream file_in; //file_in = fichero de entrada
    ofstream file_out; //file_out = fichero de salida

    //Funciones de checkeo (Podríamos hacer una función check general, que llame a estas para ahorrar líneas)
    if (entry::check_args(argc) == -1) {return -1;} //Checkeo de lor argumentos
    nts = entry::check_nts(argv[1]); //Checkeo de nts
    if (nts < 0) {return nts;}
    if (entry::check_inputfile(argv[2]) == -3) {return -3;} //Checkeo fichero entrada
    if (entry::check_outputfile(argv[3]) == -4) {return -4;} //Checkeo fichero salida

    //Apertura del fichero y cabecera
    file_in.open(argv[2], ios::binary);
    file_in.read(reinterpret_cast<char*> (&ppm_float), sizeof(float));
    ppm = static_cast<double>(ppm_float);
    file_in.read(reinterpret_cast<char*> (&np), sizeof(int));

    //Comprobación del np
    if (entry::check_np(np) != 0){return -5;}

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
    for (int i = 0; i<np; i++) {
        //hay que hacer el checkeo de np (variable que vaya sumando, comprobar al final o poner un if con un break)
        particulas.pos_x[i] = malla::lectura_float_to_double(file_in);
        particulas.pos_y[i] = malla::lectura_float_to_double(file_in);
        particulas.pos_z[i] = malla::lectura_float_to_double(file_in);
        particulas.hv_x[i] =  malla::lectura_float_to_double(file_in);
        particulas.hv_y[i] =  malla::lectura_float_to_double(file_in);
        particulas.hv_z[i] =  malla::lectura_float_to_double(file_in);
        particulas.vel_x[i] = malla::lectura_float_to_double(file_in);
        particulas.vel_y[i] = malla::lectura_float_to_double(file_in);
        particulas.vel_z[i] = malla::lectura_float_to_double(file_in);
        particulas.acel_x[i] = aceleracion_externa[0];
        particulas.acel_y[i] = aceleracion_externa[1];
        particulas.acel_z[i]= aceleracion_externa[2];
    }

    /*
     * if entry::check_np_equal(argv[2]) == -5){
     *  std::cerr << "Number of particles mismatch. Header:" << np ", Found:" << nps;
     *  return -5;
     *  }
     */

}