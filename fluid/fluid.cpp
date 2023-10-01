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
    const vector<double> aceleracion_externa = {0.0, -9.8, 0.0};
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
    vector<int> num_bloques(3);
    malla::num_bloques(limite_sup_recinto, limite_inf_recinto, longitud_de_suavizado, num_bloques);
    float aux_float;
    double lectura;
    struct Enclosure3D malla(np, nts, num_bloques);
    struct Particula particulas(np);
    //LECTURA DEL FICHERO
    for (int i = 0; i<np; i++) {
        //SABEMOS QUE SE PUEDE REDUCIR, NO SABEMOS COMO
        file_in.read(reinterpret_cast<char*> (&aux_float), sizeof(float));
        lectura = static_cast<double>(aux_float);
        particulas.pos_x[i] = lectura;
        file_in.read(reinterpret_cast<char*> (&aux_float), sizeof(float));
        lectura = static_cast<double>(aux_float);
        particulas.pos_y[i] = lectura;
        file_in.read(reinterpret_cast<char*> (&aux_float), sizeof(float));
        lectura = static_cast<double>(aux_float);
        particulas.pos_z[i] = lectura;
        file_in.read(reinterpret_cast<char*> (&aux_float), sizeof(float));
        lectura = static_cast<double>(aux_float);
        particulas.hv_x[i] = lectura;
        file_in.read(reinterpret_cast<char*> (&aux_float), sizeof(float));
        lectura = static_cast<double>(aux_float);
        particulas.hv_y[i] = lectura;
        file_in.read(reinterpret_cast<char*> (&aux_float), sizeof(float));
        lectura = static_cast<double>(aux_float);
        particulas.hv_z[i] = lectura;
        file_in.read(reinterpret_cast<char*> (&aux_float), sizeof(float));
        lectura = static_cast<double>(aux_float);
        particulas.vel_x[i] = lectura;
        file_in.read(reinterpret_cast<char*> (&aux_float), sizeof(float));
        lectura = static_cast<double>(aux_float);
        particulas.vel_y[i] = lectura;
        file_in.read(reinterpret_cast<char*> (&aux_float), sizeof(float));
        lectura = static_cast<double>(aux_float);
        particulas.vel_z[i] = lectura;
        particulas.acel_x[i] = aceleracion_externa[0];
        particulas.acel_y[i] = aceleracion_externa[1];
        particulas.acel_z[i]= aceleracion_externa[2];
    }

    // TO DO LIST
    //Comprobar el segmentation fault
    //Mirar la funcion de lectura
    //Comprobar que el numero de particulas leidas son correctas
    //Bucle principal que llame a las funciones de particulas (jueves en principio)

}