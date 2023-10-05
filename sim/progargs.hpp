//
// Created by marina on 27/09/23.
//
#include <iostream>
#include <fstream>

#ifndef ARQUITECTURA_PROGARGS_HPP
#define ARQUITECTURA_PROGARGS_HPP

namespace entry {
    int check_args(int n_args);
    int check_nts(char* nts);
    int check_inputfile(char* input);
    int check_outputfile(char* output);
    int check_np(int np);
    int check_param(int argc, char **argv);

}

#endif //ARQUITECTURA_PROGARGS_HPP
