// 完成对控制体信息的计算

void outlet_T_CV(int);
void out_cladding_T(int);
void in_cladding_T(int);
void out_UO2_T(int);

void  CV_info(int n_CV)
{
    
    outlet_T_CV(n_CV);
    out_cladding_T(n_CV);
    in_cladding_T(n_CV);
    out_UO2_T(n_CV);
}

// 用迭代法求控制体的出口温度
void outlet_T_CV(int n_CV)
{

    double err = 0;
    double C_p = 0;
    double f_avg = 0;
    double f_temp = 0;

    // 假设控制体的出口温度进行迭代计算
    checkinput_out_CVT(n_CV);
    do
    {
        f_avg = f_in + t_out_CV[n_CV];
        C_p = 1000 * (0.04006 * (f_avg - 310) + 5.7437);
        f_temp = f_in + ((q_ave * F_N_R * F_E_dH * F_E_dhm * L / 6 * φ[n_CV] * Pi * d_cs) / (W_h * C_p));
        err = (t_out_CV[n_CV] - f_temp) / t_out_CV[n_CV];
        t_out_CV[n_CV] = f_temp;

    } while (err > 0.001 || err < -0.001);
}

void out_cladding_T(int n_CV)
{

    double Re = 0;
    // 查表得
    double u = 944e-7;
    double Pr = 0.85;
    double k = 575.5e-3;
    double temp_1 = 0;
    double temp_2 = 0;
    double h_z = 0;
    double t_s = 346.31097;

    D_e = 4 * (powf(s, 2) - (Pi / 4 * powf(d_cs, 2))) / (Pi * d_cs);

    Re = (W_h * D_e) / (A_b * u);

    h_z = 0.023 * powf(Re, 0.8) * powf(Pr, 0.4) * k / D_e;
    temp_1 = q_ave * F_N_q * φ[n_CV] * F_E_q / h_z;
    temp_2 = 25 * powf(q_ave * F_N_R * φ[n_CV] * F_E_q / 1000000, 0.25) * exp(-(P*1000000 / 6.2)) + (t_s - temp_1);

    if (temp_1 < temp_2)
    {
        t_cs_h[n_CV] = t_out_CV[n_CV] + temp_1;
    }
    else
    {
        t_cs_h[n_CV] = t_out_CV[n_CV] + temp_2;
    }
}

void in_cladding_T(int n_CV)
{

    double err = 0;
    double t_avg = 0;
    double k = 0;
    double t_temp = 0;
    // 先假设后用迭代法计算
    t_ci_h[n_CV] = 330;

    do
    {
        t_avg = (t_cs_h[n_CV] + t_ci_h[n_CV]) / 2;
        k = 0.457 * (1.8 * t_avg + 32) + 1.3;
        t_temp = t_cs_h[n_CV] + (t_cs_h[n_CV] + q_l_ave * F_N_R * F_E_q * φ[n_CV]) / (2 * Pi * k) * log(d_cs / d_ci);
        err = (t_ci_h[n_CV] - t_temp) / t_temp;
        t_ci_h[n_CV] = t_temp;
    } while (err > 0.001 || err < -0.001);
}

void out_UO2_T(int n_CV)
{

    // 需了解
    double hg = 5678;

    t_u_h[n_CV] = t_ci_h[n_CV] + (  q_l_ave * F_N_R * F_E_q * φ[n_CV] /  (Pi * (d_ci+d_u)/2 * hg) );
}