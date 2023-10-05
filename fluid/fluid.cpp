//
// Created by marina on 27/09/23.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <span>
#include "../sim/progargs.hpp"
#include "../sim/grid.hpp"
#include "../sim/file.hpp"
#include "../sim/block.hpp"
#include "../sim/calculos.hpp"

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
//const vector<double> acel_ex = {0.0, -9.8, 0.0};
//const vector<double> limite_sup_recinto = {0.065, 0.1, 0.065};
//const vector<double> limite_inf_recinto = {-0.065, -0.08, -0.065};

const char* input_file = "in.fld";
const char* output_file = "out.fld";

using namespace std;

int main(int argc, char **argv) {
    span args{argv, static_cast<size_t>(argc)};
    int nts,np; //nts = numero de pasos de tiempo, np = numero de particulas
    double ppm; //ppm = partículas por metro
    ifstream file_in; //file_in = fichero de entrada
    ofstream file_out; //file_out = fichero de salida
    nts = entry::check_param(argc, argv); //Función de checkeo maestra
    if (nts < 0) {return nts;}
    file_in.open(argv[2], ios::binary);//Apertura del fichero y cabecera
    tie(np, ppm)  = ficheros::lectura_cabecera(file_in);
    double masa = (DENSIDAD_DE_FLUIDO) / (pow(ppm, 3)); //Cálculos de m y h
    double longitud_de_suavizado = (RADIO / ppm);
    vector<int> num_bloques(3); //Calculo del numero de bloques
    vector<double> tam_bloques(3); //Calculo del tamaño de los bloques
    bloque::num_bloques(limite_sup_recinto, limite_inf_recinto, longitud_de_suavizado, num_bloques);
    bloque::tam_bloques(limite_sup_recinto, limite_inf_recinto, num_bloques, tam_bloques);
    struct Particula particulas(np); //Inicialización de los objetos
    struct Enclosure3D malla(np, nts, num_bloques);
    ficheros::lectura_file(file_in, np, particulas); //Lectura del fichero
    //double nts_d = static_cast<double>(nts), iterations_d = nts_d/PASO_TIEMPO;
    //int iterations = static_cast<int>(iterations_d);
    for (int t = 0; t < nts; t++){
        cout << t << endl;
        bloque::loc_particula(particulas,np,limite_inf_recinto,tam_bloques); //actualizacion
        for(int i = 0; i < np; i++) {
            for (int j = i + 1; j < np; j++) {
                if (bloque::particula_contigua(particulas, i, j) == 1) {
                    vector<int> part;
                    part = {i, j};
                    fisica::fuerza_acel(particulas, part, longitud_de_suavizado, masa);
                }
            }
            fisica::col_mov(particulas, num_bloques, i);
        }
    }
    file_out.open(output_file, ios::binary);
    ficheros::escritura_salida(file_out, particulas, ppm, np);
}