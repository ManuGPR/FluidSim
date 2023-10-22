//
// Created by marina on 27/09/23.
//
#include <iostream>
#include <fstream>
#include "vector"

#ifndef ARQUITECTURA_PROGARGS_HPP
#define ARQUITECTURA_PROGARGS_HPP

namespace entry {
    int check_args(std::vector<std::string> const &  arguments);
    int check_nts(std::vector<std::string> const &  arguments);
    int check_inputfile(std::vector<std::string> const &  arguments);
    int check_outputfile(std::vector<std::string> const &  arguments);
    int check_np(int np);
    int check_param(std::vector<std::string> const &  arguments);

}

#endif //ARQUITECTURA_PROGARGS_HPP
