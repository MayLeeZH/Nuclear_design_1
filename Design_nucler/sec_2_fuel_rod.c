// #include "system_parameter.h"

void fuel_serface_info(void)
{
    F_total = m * n * d_cs * L * Pi;
    q_ave = (F_a * 1000000 * Nt)/ F_total;
    q_max = q_ave * F_E_q * F_N_q;
    q_l_ave = q_ave * Pi * d_cs ;
    q_l_max = q_l_ave * F_N_q * F_E_q;
}


