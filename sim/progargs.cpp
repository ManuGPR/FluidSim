//
// Created by marina on 27/09/23.
//

#include "progargs.hpp"


using namespace std;

namespace entry {
  int check_args(vector<std::string> const &  arguments) {
        const size_t size = arguments.size();
    if (size != 3){
      cerr << "Invalid number of arguments " << size  << '\n';
      return -1;
    }
    return 0;
  }

  int check_nts(vector<std::string> const &  arguments) {
    for (auto digit: arguments[0]) {
      if (isdigit(digit) == 0) {
        cerr << "Time steps must be numeric." << '\n';
        return -1;}
    }
    int const number_nts = stoi(arguments[0]);
    if (number_nts <= 0){
      cerr << "Invalid number of time steps." << '\n';
      return -2;
    }
    return number_nts;
  }
  /*
  int check_nts(char *nts) {
      if (isdigit(nts[0]) == 0) {
          cerr << "Time steps must be numeric." << '\n';
          return -1;
      }
      int const number_nts = stoi(nts);
      if (number_nts <= 0){
          cerr << "Invalid number of time steps." << '\n';
          return -2;
      }
      return number_nts;
  }
   */

  int check_inputfile(vector<std::string> const &  arguments) {
    ifstream fichero(arguments[1], ios::binary);
    if (!fichero) {
      cerr << "Cannot open " << arguments[1] << " for reading" << '\n';
      return -3;
    }
    fichero.close();
    return 0;
  }

  int check_outputfile(vector<std::string> const &  arguments) {
    ofstream fichero(arguments[2], ios::binary);
    if (!fichero) {
      std:: cerr << "Cannot open " << arguments[2] << " for writing";
      return -4;
    }
    fichero.close();
    return 0;
  }

  [[maybe_unused]] int check_param(vector<std::string> const &  arguments){
    if (entry::check_args(arguments) != 0) {return -1;} //Checkeo de lor argumentos
        const int nts = entry::check_nts(arguments); //Checkeo de nts
    if (nts < 0) {return nts;}
    if (entry::check_inputfile(arguments) == -3) {return -3;} //Checkeo fichero entrada
    if (entry::check_outputfile(arguments) == -4) {return -4;} //Checkeo fichero salida
    return nts;
  }

  [[maybe_unused]] int check_np(int np){
        const int bad_return = -5;
    if (np == 0) {
      std::cerr << "El numero de particulas es 0";
      return bad_return;
    }
    if (np < 0) {
      std::cerr << "El numero de particulas es negativo";
      return bad_return;
    }
    return  0; // No se si devolver el numero de particulas
  }
}