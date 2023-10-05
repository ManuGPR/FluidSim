//
// Created by marina on 27/09/23.
//

#include "progargs.hpp"


using namespace std;

namespace entry {
    int check_args(int n_args) {
        if (n_args != 4){
            cerr << "Invalid number of arguments " << n_args << endl;
            return -1;
        }
        return 0;
    }

    int check_nts(char *nts) {
        if (isdigit(nts[0]) == 0) {
            cerr << "Time steps must be numeric." << endl;
            return -1;
        }
        int number_nts = stoi(nts);
        if (number_nts <= 0){
            cerr << "Invalid number of time steps." << endl;
            return -2;
        }
        return number_nts;
    }

    int check_inputfile(char* input) {
        ifstream fichero(input, ios::binary);
        if (!fichero) {
            cerr << "Cannot open " << input << " for reading" << endl;
            return -3;
        }
        fichero.close();
        return 0;
    }

    int check_outputfile(char *output) {
        ofstream fichero(output, ios::binary);
        if (!fichero) {
            std:: cerr << "Cannot open " << output << " for writing";
            return -4;
        }
        fichero.close();
        return 0;
    }

    int check_param(int argc, char **argv){
        int nts;
        if (entry::check_args(argc) == -1) {return -1;} //Checkeo de lor argumentos
        nts = entry::check_nts(argv[1]); //Checkeo de nts
        if (nts < 0) {return nts;}
        if (entry::check_inputfile(argv[2]) == -3) {return -3;} //Checkeo fichero entrada
        if (entry::check_outputfile(argv[3]) == -4) {return -4;} //Checkeo fichero salida
        return nts;
    }

    int check_np(int np){
        if (isdigit(np) == 0) {
            if (np == 0) {
                std::cerr << "El numero de particulas es 0";
                return -5;
            } else if (np < 0) {
                std::cerr << "El numero de particulas es negativo";
                return -5;
            }
        }
        return  0; // No se si devolver el numero de particulas
    }
}
