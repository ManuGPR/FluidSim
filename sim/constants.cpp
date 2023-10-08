//
// Created by manu on 8/10/23.
//

#include "constants.hpp"

namespace constantes {
    int calcular_operandos(double m, double h) {
        op_1 = 315 * m / (64 * PI * pow(h, 9.0));
        op_2 = pow(h, 6) * op_1;
        op_3 = (15 * m) / (PI * pow(h, 6.0));
        op_4 = (45 / (PI * pow(h, 6.0))) * VISCOSIDAD * m;
        return 0;
    }
}