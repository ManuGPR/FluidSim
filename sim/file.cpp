//
// Created by manu on 5/10/23.
//

#include "file.hpp"



using namespace std;

namespace ficheros {
    tuple <int, double> lectura_cabecera(ifstream & file_in){
        int nps         = 0;
        float ppm_float = 0.0;
        file_in.read(reinterpret_cast<char *> (&ppm_float), sizeof(float));
        const double ppm = static_cast<double>(ppm_float);
        file_in.read(reinterpret_cast<char *> (&nps), sizeof(int));
        //Comprobación del nps
        if (entry::check_np(nps) != 0){return tuple(-5, -5.0);}
        nps = static_cast<double>(nps);
        return tuple(nps, ppm);
    }

    double lectura_float_to_double (ifstream & fichero) {
        /*Función que se encarga de leer un float del fichero y devolver un double
         * param1: fichero del que se lee*/
        float aux_float = 0.0;
        fichero.read(reinterpret_cast<char *> (&aux_float), sizeof(float));
        return static_cast<double>(aux_float);
    }

    int lectura_file(ifstream & file_in, int np, struct Particula & particulas){
        int np_real = 0;
        for (int i = 0; i < np; i++){
            //hay que hacer el checkeo de np (variable que vaya sumando, comprobar al final o poner un if con un break)
            particulas.pos_x[np_real] = ficheros::lectura_float_to_double(file_in);
            particulas.pos_y[np_real] = lectura_float_to_double(file_in);
            particulas.pos_z[np_real] = lectura_float_to_double(file_in);
            particulas.hv_x[np_real] =  lectura_float_to_double(file_in);
            particulas.hv_y[np_real] =  lectura_float_to_double(file_in);
            particulas.hv_z[np_real] =  lectura_float_to_double(file_in);
            particulas.vel_x[np_real] = lectura_float_to_double(file_in);
            particulas.vel_y[np_real] = lectura_float_to_double(file_in);
            particulas.vel_z[np_real] = lectura_float_to_double(file_in);
            particulas.acel_x[np_real] = acel_ex[0];
            particulas.acel_y[np_real] = acel_ex[1];
            particulas.acel_z[np_real]= acel_ex[2];
            //cout << particulas.hv_x[np_real] << "\n";
            np_real ++;
        }
        if (np_real != np){
            cerr << " Number of particles mismatch. Header: " << np <<", Found:" << np_real << "\n";
            return -5;
        }
        return 0;
    }

    int escritura_salida(ofstream& file_out, const struct Particula & particulas, double ppm, int np) {
        auto aux = static_cast<float>(ppm);
        //cout << "Salida nuestra \n";
        //cout << aux << " " << np << endl;
        file_out.write(to_str(aux), sizeof(float));
        file_out.write(to_str(np), sizeof(float));
        for (int i = 0; i < np; i++) {
            aux = static_cast<float>(particulas.pos_x[i]);
            //cout << aux << " ";
            file_out.write(to_str(aux), sizeof(float));
            aux = static_cast<float>(particulas.pos_y[i]);
            //cout << aux << " ";
            file_out.write(to_str((aux)), sizeof(float));
            aux = static_cast<float>(particulas.pos_z[i]);
            //cout << aux << " ";
            file_out.write(to_str(aux), sizeof(float));
            aux = static_cast<float>(particulas.hv_x[i]);
            //cout << aux << " ";
            file_out.write(to_str(aux), sizeof(float));
            aux = static_cast<float>(particulas.hv_y[i]);
            //cout << aux << " ";
            file_out.write(to_str(aux), sizeof(float));
            aux = static_cast<float>(particulas.hv_z[i]);
            //cout << aux << " ";
            file_out.write(to_str(aux), sizeof(float));
            aux = static_cast<float>(particulas.vel_x[i]);
            //cout << aux << " ";
            file_out.write(to_str(aux), sizeof(float));
            aux = static_cast<float>(particulas.vel_y[i]);
            //cout << aux << " ";
            file_out.write(to_str(aux), sizeof(float));
            aux = static_cast<float>(particulas.vel_z[i]);
            //cout << aux << " ";
            //cout << particulas.loc_x[i] << " ";
            //cout << "\n";
            file_out.write(to_str(aux), sizeof(float));
        }
        return 0;
    }

    const char* to_str(int & parameter) {
        const char *value = reinterpret_cast<const char*>(&parameter);
        return value;
    }

    const char* to_str(float & parameter) {
        const char *value = reinterpret_cast<const char *>(&parameter);
        return value;
    }


    /*
     template <typename T>
    requires(std::is_integral_v<T> or std::is_floating_point_v<T>)
    char * as_writable_buffer(T & value) {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        return reinterpret_cast<char *>(&value);
    }

    template <typename T>
    requires(std::is_integral_v<T> or std::is_floating_point_v<T>)
    char const * as_buffer(T const & value) {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        return reinterpret_cast<char const *>(&value);
    }

    template <typename T>
    requires(std::is_integral_v<T> or std::is_floating_point_v<T>)
    void write_binary_value(T value, std::ostream & os) {
        os.write(as_buffer(value), sizeof(value));
    }
     */


}