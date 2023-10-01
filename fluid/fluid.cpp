//
// Created by marina on 27/09/23.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "../sim/progargs.hpp"

//CONSTANTES ESCALARES DE SIMULACIÓN

#define RADIO 1.695
#define DENSIDAD_DE_FLUIDO 1000
#define PRECISION_DE_RIGIDEZ 3.0
#define COLISIONES_DE_RIGIDEZ 30000
#define AMORTIGUAMIENTO 128.0
#define VISCOSIDAD 0.4
#define TAMANO_PARTICULAS 0.0002
#define PASO_TIEMPO 0.001

using namespace std;

int main(int argc, char **argv) {
    // Constantes vectoriales de la simulación
    const vector<double> aceleracion_externa = {0.0, 9.8, 0.0};
    const vector<double> limite_sup_recinto = {0.065, 0.1, 0.065};
    const vector<double> limite_inf_recinto = {-0.065, -0.08, -0.065};
    //Variables de la simulación
    //nts = number of time steps, file_in = fichero de entrada, file_out = fichero de salida
    int nts;
    ifstream file_in;
    ofstream file_out;
    //ppm = particulas por metro, np = numero de particulas
    float ppm_float;
    double ppm;
    int np;

    //Checkeo de argumentos de entrada
    if (entry::check_args(argc) == -1) {
        std:: cerr << "Invalid number of arguments: " << argc;
        return -1;
    }

    nts = entry::check_nts(argv[1]);
    if (nts == -1){
        cerr << "Time steps must be numeric.";
        return -1;
    }

    else if (nts == -2) {
        cerr << "Invalid number of time steps.";
        return -2;
    }

    if (entry::check_inputfile(argv[2]) == -3) {
        cerr << "Cannot open " << argv[2] << " for reading" << endl;
        return -3;
    }

    if (entry::check_outputfile(argv[3]) == -4) {
        cerr << "Cannot open " << argv[3] << "for writing" << endl;
        return -4;
    }

    file_in.open(argv[2], ios::binary);

    file_in.read(reinterpret_cast<char*> (&ppm_float), sizeof(float));
    ppm = static_cast<double>(ppm_float);
    file_in.read(reinterpret_cast<char*> (&np), sizeof(int));

    cout << ppm<<endl;
    cout << np<<endl;
    /* if (entry::check_np_h(argv[2]) == -5){
     *  std::cerr << "Invalid number of particles:" << np;
     *  return -5;
     *  }
     *
     * if entry::check_np_equal(argv[2]) == -5){
     *  std::cerr << "Number of particles mismatch. Header:" << np ", Found:" << nps;
     *  return -5;
     *  }
     */

     //LECTURA DEL FICHERO

     double masa = (DENSIDAD_DE_FLUIDO) / (pow(ppm, 3));
     double longitud_de_suavizado = (RADIO / ppm);
     cout << masa << endl;
     cout << longitud_de_suavizado<< endl;
}