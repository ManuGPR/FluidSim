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

  int check_nts(const string & arguments) {
    for (auto digit: arguments) {
      if (isdigit(digit) == 0) {
        cerr << "Time steps must be numeric." << '\n';
        return -1;}
    }
    int const number_nts = stoi(arguments);
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

  int check_inputfile(const string & arguments) {
    ifstream fichero(arguments, ios::binary);
    if (!fichero) {
      cerr << "Cannot open " << arguments << " for reading" << '\n';
      return -3;
    }
    fichero.close();
    return 0;
  }

  int check_outputfile(const string & arguments) {
    ofstream fichero(arguments, ios::binary);
    if (!fichero) {
      std:: cerr << "Cannot open " << arguments << " for writing";
      return -4;
    }
    fichero.close();
    return 0;
  }

  [[maybe_unused]] int check_param(vector<std::string> const &  arguments){
    if (entry::check_args(arguments) != 0) {return -1;} //Checkeo de lor argumentos
        const int nts = entry::check_nts(arguments[0]); //Checkeo de nts
    if (nts < 0) {return nts;}
    if (entry::check_inputfile(arguments[1]) == -3) {return -3;} //Checkeo fichero entrada
    if (entry::check_outputfile(arguments[2]) == -4) {return -4;} //Checkeo fichero salida
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