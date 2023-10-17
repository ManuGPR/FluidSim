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

/*
void f(std::vector<std::string> const &  arguments) {
  for (size_t i = 0; i<arguments.size(); ++i) {
    std::cout << "argument: " << i << " -> " << arguments[i] << '\n';
  }
}
*/


int main(int argc, char **argv) {
    const span args{argv, static_cast<size_t>(argc)};
    const std::vector<std::string> args_str{args.begin() +1, args.end()};
    //f(args_str);
    //return 0;
    int nps    = 0; //nts = numero de pasos de tiempo, nps = numero de particulas
    double ppm = 0.0; //ppm = partículas por metro
    ifstream file_in; //file_in = fichero de entrada
    ofstream file_out; //file_out = fichero de salida
    const int nts = entry::check_param(argc, argv); //Función de checkeo maestra
    if (nts < 0) { return nts; }
    file_in.open(argv[2], ios::binary);//Apertura del fichero y cabecera
    tie(nps, ppm) = ficheros::lectura_cabecera(file_in);
    const double masa = (DENSIDAD_DE_FLUIDO) / (pow(ppm, 3)); //Cálculos de m y h
    const double longitud_de_suavizado = (RADIO / ppm);
    fisica::calcular_operandos(masa, longitud_de_suavizado);
    vector<int> num_bloques(3); //Calculo del numero de bloques
    vector<double> tam_bloques(3); //Calculo del tamaño de los bloques
    bloque::num_bloques(limite_sup_recinto, limite_inf_recinto, longitud_de_suavizado, num_bloques);
    bloque::tam_bloques(limite_sup_recinto, limite_inf_recinto, num_bloques, tam_bloques);

    struct Particula particulas(nps); //Inicialización de los objetos
    const struct Enclosure3D malla(nps, nts, num_bloques);
    ficheros::lectura_file(file_in, nps, particulas); //Lectura del fichero

    for (int time = 0; time < nts; time++) {
        bloque::loc_particula(particulas, nps, num_bloques, tam_bloques); //actualizacion
        for(int i=0; i< nps; i++) { fisica::inicializar_dens_acelera(particulas, i);}
        for (int i = 0; i < nps; i++) {
          for (int j = i + 1; j < nps; j++) {
              if (bloque::particula_contigua(particulas, i, j) == 1) {
                  const vector<int> part = {i, j};
                  fisica::incremento_densidades(particulas, part);
              }
          }
          particulas.dens[i] = fisica::trans_densidad(particulas.dens[i]);
        }
        for(int i = 0; i < nps; i++) {
            for (int j = i + 1; j < nps; j++) {
                if (bloque::particula_contigua(particulas, i, j) == 1) {
                    const vector<int> part = {i, j};
                    fisica::trans_acele(particulas, part, longitud_de_suavizado);
                }
            }
        }
        for (int i = 0; i < nps; i++){
            fisica::col_mov(particulas, num_bloques, i);
        }
        for (int i = 0; i < nps; i++) {
            fisica::interaccion(particulas, num_bloques, i);
        }
    }

    //output_file("file_out", ios::binary);

    file_out.open("out.fld", ios::binary);
    ficheros::escritura_salida(file_out, particulas, ppm, nps);
    /*
    ifstream fichero_comp;
    ofstream fichero_comp_salida("salida.txt");


    fichero_comp.open("boundint-base-1.trz", ios::binary);
    int cabecera = 0;
    fichero_comp.read(reinterpret_cast<char *> (&cabecera), sizeof(int));
    fichero_comp_salida << cabecera << "\n";
    int num_bloque = 0;
    while(!fichero_comp.eof()){
        long int num_p;
        fichero_comp.read(reinterpret_cast<char*> (&num_p), sizeof(long int));
        fichero_comp_salida << num_bloque << " " << num_p <<"\n";
        for (int j = 0; j < num_p; j++){
          long int id;
          fichero_comp.read(reinterpret_cast<char *>(&id), sizeof(long int));
          fichero_comp_salida << id << " ";
          double aux;
          for (int k = 0; k < 3; k++) {
                fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
                fichero_comp_salida << aux << " ";
                fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
                fichero_comp_salida << aux << " ";
                fichero_comp.read(reinterpret_cast<char *>(&aux), sizeof(double));
                fichero_comp_salida << aux << " ";
          }
          fichero_comp.read(reinterpret_cast<char*> (&aux), sizeof(double));
          fichero_comp_salida << aux << " ";
          for (int k = 0; k < 3; k++){
                fichero_comp.read(reinterpret_cast<char*> (&aux), sizeof(double));
                fichero_comp_salida << aux << " ";
          }
          fichero_comp_salida <<"\n";
        }
        num_bloque ++;
        fichero_comp_salida << "\n";

    }
     */
}
// NOLINTBEGIN
// NOLINTEND