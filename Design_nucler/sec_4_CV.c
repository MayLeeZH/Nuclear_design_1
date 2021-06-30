// 对控制体信息的计算

void outlet_T_CV(int);
void out_cladding_T(int);
void in_cladding_T(int);
void outside_UO2_T(int);
void inside_UO2_T(int);
void get_q_DNBh(int);
void get_DNBR(int);



void  CV_info(int n_CV)
{
    
    outlet_T_CV(n_CV);
    out_cladding_T(n_CV);
    in_cladding_T(n_CV);
    outside_UO2_T(n_CV);
    inside_UO2_T(n_CV);
    get_q_DNBh(n_CV);
    get_DNBR(n_CV);
}

// 用迭代法求控制体的出口温度
void outlet_T_CV(int n_CV)
{

    double err = 0;
    double C_p = 0;
    double f_avg = 0;
    double f_temp = 0;

        double t_in = 0;
        if (n_CV == 0){
            t_in = f_in;
        }
        else
        {
            t_in = t_f_h[n_CV - 1];
        }
        
    // 假设控制体的出口温度进行迭代计算
    checkinput_out_CVT(n_CV);
    do
    {
        f_avg = (t_in + t_f_h[n_CV])/2;
        C_p = find_C_p(f_avg);
        f_temp = t_in + ((q_ave * F_N_R * F_E_dH * F_E_dhm * φ[n_CV] * L/s_CV * Pi * d_cs) / (W_h * C_p));
        err = (t_f_h[n_CV] - f_temp) / t_f_h[n_CV];
        t_f_h[n_CV] = f_temp;

    } while (err > 0.001 || err < -0.001);
}

void out_cladding_T(int n_CV)
{

    
    // 查表得
    double μ = find_μ(t_f_h[n_CV]);
    double Pr = find_Pr(t_f_h[n_CV]);
    double k = find_k(t_f_h[n_CV]);

    double temp_1 = 0;
    double temp_2 = 0;
    double h_z = 0;
    // 15.5Mpa 下的水的饱和温度，查表得：https://wenku.baidu.com/view/bc8e0eddf08583d049649b6648d7c1c709a10bd7.html
    double t_s = 345.72;

    D_e = 4 * (powf(s, 2) - (Pi / 4 * powf(d_cs, 2))) / (Pi * d_cs);

    Re = (W_h * D_e) / (A_b * μ);

    h_z = 0.023 * powf(Re, 0.8) * powf(Pr, 0.4) * k / D_e;
    temp_1 = q_ave * F_N_q * φ[n_CV] * F_E_q / h_z;
    temp_2 = 25 * powf(q_ave * F_N_R * φ[n_CV] * F_E_q / 1000000, 0.25) * exp(-(P/ 6.2)) + (t_s - t_f_h[n_CV]);
    if (temp_1 < temp_2)
    {
        t_cs_h[n_CV] = t_f_h[n_CV] + temp_1;

    }
    else
    {
        t_cs_h[n_CV] = t_f_h[n_CV] + temp_2;

    }
}

void in_cladding_T(int n_CV)
{

    double err = 0;
    double t_avg = 0;
    double k = 0;
    double t_temp = 0;
    // 先假设 后用迭代法计算
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

void outside_UO2_T(int n_CV)
{

    // hg为包壳与芯快间的气息等效传热系数取 5678 W/(m^2·°C)
    double temp =   q_l_ave * F_N_R * F_E_q * φ[n_CV] /  (Pi * (d_ci+d_u)/2 * hg) ;
    t_u_h[n_CV] = t_ci_h[n_CV] + temp;

}
void inside_UO2_T(int n_CV){
    // 数据为查表所得，关键在于查找算法
    double t_part1 = 0;
    double t_part2 = 0;
    double IHC = 0;

    t_part1 = find_UO2_fromT(t_u_h[n_CV]);
    t_part2 = (q_l_ave * F_N_R * F_E_q * φ[n_CV]) /  ( 4 * Pi * 100 );
    IHC = t_part1 + t_part2;
    t_o_h[n_CV] = find_UO2_fromIHC(IHC);
}

void get_q_DNBh(int n_CV){

    double h = find_h(t_f_h[n_CV]);
    double ρ = find_ρ(t_f_h[n_CV]);
    double x_e = (h - h_fs) / h_fg;
    double G = ρ * V * 3600;
    double part_1 = (2.022 -  (6.238 * 1e-8 * P * 1000000) ) + (0.1722 - (1.43 * 1e-8 * P * 1000000) ) * exp(  (  18.177 - 5.987 * 1e-7 * P*  1000000) * x_e );
    double part_2 = (0.1484 - 1.596 * x_e + 0.1729 * x_e * fabs(x_e) ) * (0.2049 * G / 1e6) + 1.037;
    double part_3 = (1.157 - 0.869 * x_e) * (0.2664 + 0.8357 * exp(-124 * D_e)) * (0.8258 + 0.341 *(h_fs - h_f_in) / 1e6 );
    q_DNB_h[n_CV] = 3.154 * 1e6 * part_1 * part_2 * part_3;
}
void get_DNBR(int n_CV){
    DNBR[n_CV] = q_DNB_h[n_CV] / (q_ave * F_N_R * F_E_q * φ[n_CV]);
}