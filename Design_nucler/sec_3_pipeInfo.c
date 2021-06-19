
void pipe_info(void)
{

    double v_f = 0; // 查标得
    double ρ_f = 0; //平均密度
    double f_avg = 0;
    f_avg = (f_out_S + f_in) / 2;
    A_f = m * (n0 * n0) * (powf(s, 2) - (Pi / 4 * powf(d_cs, 2))) + (4 * n0 * s * δ / 2);
    v_f = 0.00000513 * (f_avg - 310) + 0.0014189;
    ρ_f = 1 / v_f;

    V = (W_kg_s * (1 - ξ)) / (A_f * ρ_f);
    A_b = powf(s, 2) - (Pi / 4 * powf(d_cs, 2));
    W_h = W_kg_s * (1 - ξ) * A_b / A_f;
}