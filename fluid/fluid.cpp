//
// Created by marina on 27/09/23.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <span>
#include "../sim/constants.hpp"
#include "../sim/progargs.hpp"
#include "../sim/grid.hpp"
#include "../sim/file.hpp"
#include "../sim/block.hpp"
#include "../sim/calculos.hpp"

using namespace std;

int main(int argc, char **argv) {
    span args{argv, static_cast<size_t>(argc)};
    int nts, np; //nts = numero de pasos de tiempo, np = numero de particulas
    double ppm; //ppm = partículas por metro
    ifstream file_in; //file_in = fichero de entrada
    ofstream file_out; //file_out = fichero de salida
    nts = entry::check_param(argc, argv); //Función de checkeo maestra
    if (nts < 0) { return nts; }
    file_in.open(argv[2], ios::binary);//Apertura del fichero y cabecera
    tie(np, ppm) = ficheros::lectura_cabecera(file_in);
    double masa = (DENSIDAD_DE_FLUIDO) / (pow(ppm, 3)); //Cálculos de m y h
    double longitud_de_suavizado = (RADIO / ppm);
    fisica::calcular_operandos(masa, longitud_de_suavizado);
    vector<int> num_bloques(3); //Calculo del numero de bloques
    vector<double> tam_bloques(3); //Calculo del tamaño de los bloques
    bloque::num_bloques(limite_sup_recinto, limite_inf_recinto, longitud_de_suavizado, num_bloques);
    bloque::tam_bloques(limite_sup_recinto, limite_inf_recinto, num_bloques, tam_bloques);

    struct Particula particulas(np); //Inicialización de los objetos
    struct Enclosure3D malla(np, nts, num_bloques);
    ficheros::lectura_file(file_in, np, particulas); //Lectura del fichero
    //double nts_d = static_cast<double>(nts), iterations_d = nts_d/PASO_TIEMPO;
    //int iterations = static_cast<int>(iterations_d);

    for (int t = 0; t < nts; t++) {
        bloque::loc_particula(particulas, np, num_bloques, tam_bloques); //actualizacion
        for (int i = 0; i < np; i++) {
            for (int j = i + 1; j < np; j++) {
                if (bloque::particula_contigua(particulas, i, j) == 1) {
                    vector<int> part = {i, j};
                    fisica::incremento_densidades(particulas, part, longitud_de_suavizado);
                }
            }
            particulas.dens[i] = fisica::trans_densidad(particulas.dens[i]);
        }

        for(int i = 0; i < np; i++) {
            for (int j = i + 1; j < np; j++) {
                if (bloque::particula_contigua(particulas, i, j) == 1) {
                    vector<int> part = {i, j};
                    fisica::trans_acele(particulas, part, longitud_de_suavizado, masa);
                }
            }
        }

        for (int i = 0; i < np; i++){
            fisica::col_mov(particulas, num_bloques, i);
        }

        for (int i = 0; i < np; i++) {
            fisica::interacion(particulas, num_bloques, i);
        }
    }

    //output_file("file_out", ios::binary);
    file_out.open("out.fld", ios::binary);
    ficheros::escritura_salida(file_out, particulas, ppm, np);
    ifstream fichero_comp;
    fichero_comp.open("small-1.fld", ios::binary);
    cout << "Fichero de comprobación" << "\n";
    float cabecera_1;
    int cabecera_2;
    fichero_comp.read(reinterpret_cast<char *> (&cabecera_1), sizeof(float));
    fichero_comp.read(reinterpret_cast<char *> (&cabecera_2), sizeof(int));

    cout << cabecera_1 << " " << cabecera_2 << "\n";


    for (int i = 1; i <= np*9; i++){
        float aux;
        fichero_comp.read(reinterpret_cast<char *> (&aux), sizeof(float));
        cout << aux << " ";
        if (i % 9 == 0) {
            cout << "\n";
        }
    }
}