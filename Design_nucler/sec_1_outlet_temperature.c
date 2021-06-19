
void outlet_TEMP(void)
{

    double C_p = 0;
    double f_avg = 0;
    double f_temp = 0;
    double err = 0;
    
    checkinput_outT();

    do
    {
        f_avg = (f_in + f_out_S) / 2;
        C_p = 1000 * (0.04006 * (f_avg - 310) + 5.7437);
        f_temp = f_in + ((F_a * Nt * 1000000) / (W_kg_s * (1 - ξ) * C_p));
        err = (f_out_S - f_temp) / f_out_S;
        f_out_S = f_temp; // 进行迭代

    } while (err > 0.001 || err < -0.001);

    
}
