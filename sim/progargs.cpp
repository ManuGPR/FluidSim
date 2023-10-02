//
// Created by marina on 27/09/23.
//

#include "progargs.hpp"
#include <iostream>
#include <fstream>

using namespace std;

namespace entry {
    int check_args(int n_args) {
        if (n_args != 4){
            return -1;
        }
        return 0;
    }

    int check_nts(char *nts) {
        if (isdigit(nts[0]) == 0) {
            return -1;
        }
        int number_nts = stoi(nts);
        if (number_nts <= 0){
            return -2;
        }
        return number_nts;
    }

    int check_inputfile(char* input) {
        ifstream fichero(input, ios::binary);
        if (!fichero) {
            return -3;
        }
        fichero.close();
        return 0;
    }

    int check_outputfile(char *output) {
        ofstream fichero(output, ios::binary);
        if (!fichero) {
            std:: cerr << "Cannot open final.fld for writing";
            return -4;
        }
        fichero.close();
        return 0;
    }

    int check_np(int np){
        if (isdigit(np) == 0) {
            std::cerr << "Not a digit";// No se si hay que contemplar el este error
            return -5;// No se que se devuelve (El 0 y los negativos te los da como verdaderos  solo los naturales)
        }
        if (np == 0){
            std:: cerr << "El numero de particulas es 0";
            return -5;
        }
        else if (np < 0){
            std:: cerr << "El numero de particulas es negativo";
            return -5;
        }
        return  0; // No se si devolver el numero de particulas
    }
}
