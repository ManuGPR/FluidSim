#include "progargs.hpp"

using namespace std;

namespace entry {
  // Función que checkea los argumentos de entrada
  int check_args(vector<std::string> const & arguments) {
    size_t const size = arguments.size();
    if (size != 3) {
      cerr << "Invalid number of arguments " << size << '\n';
      return -1;
    }
    return 0;
  }

  // Función que checkea el número de pasos de tiempo
  int check_nts(string const & arguments) {
    for (auto digit : arguments) {
      if (isdigit(digit) == 0) {
        if ('-' == digit) {
          cerr << "Invalid number of time steps.\n";
          return -2;
        }
        cerr << "Time steps must be numeric.\n";
        return -1;
      }
    }
    int const number_nts = stoi(arguments);
    if (number_nts <= 0) {
      cerr << "Invalid number of time steps.\n";
      return -2;
    }
    return number_nts;
  }

  // Función que checkea el fichero de entrada
  int check_inputfile(string const & arguments) {
    ifstream fichero(arguments, ios::binary);
    if (!fichero) {
      cerr << "Cannot open " << arguments << " for reading\n";
      return -3;
    }
    fichero.close();
    return 0;
  }

  // Función que checkea el fichero de salida
  int check_outputfile(string const & arguments) {
    ofstream fichero(arguments, ios::binary);
    if (!fichero) {
      std::cerr << "Cannot open " << arguments << " for writing\n";
      return -4;
    }
    fichero.close();
    return 0;
  }

  // Función que checkea el número de partículas del fichero
  [[maybe_unused]] int check_np(int np) {
    int const bad_return = -5;
    if (np == 0) {
      std::cerr << "El numero de particulas es 0\n";
      return bad_return;
    }
    if (np < 0) {
      std::cerr << "El numero de particulas es negativo\n";
      return bad_return;
    }
    return 0;  // No se si devolver el numero de particulas
  }

  // Función de checkeo maestra, que llama al resto de funciones
  [[maybe_unused]] int check_param(vector<std::string> const & arguments) {
    if (entry::check_args(arguments) != 0) { return -1; }  // Checkeo de lor argumentos
    int const nts = entry::check_nts(arguments[0]);        // Checkeo de nts
    if (nts < 0) { return nts; }
    if (entry::check_inputfile(arguments[1]) == -3) { return -3; }   // Checkeo fichero entrada
    if (entry::check_outputfile(arguments[2]) == -4) { return -4; }  // Checkeo fichero salida
    return nts;
  }

}  // namespace entry