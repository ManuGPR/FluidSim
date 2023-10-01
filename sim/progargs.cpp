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
}
