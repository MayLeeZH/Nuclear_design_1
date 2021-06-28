// 完成对控制体信息的计算

void outlet_T_CV(int);
void out_cladding_T(int);
void in_cladding_T(int);
void outside_UO2_T(int);
void inside_UO2_T(int);
void get_q_DNBh(int);
#define X1 1.2
#define G 1


void  CV_info(int n_CV)
{
    
    outlet_T_CV(n_CV);
    out_cladding_T(n_CV);
    in_cladding_T(n_CV);
    outside_UO2_T(n_CV);
    inside_UO2_T(n_CV);
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
        f_avg = (f_in + t_f_h[n_CV])/2;
        C_p = find_C_p(f_avg);
        f_temp = f_in + ((q_ave * F_N_R * F_E_dH * F_E_dhm * L / 6 * φ[n_CV] *n_CV * Pi * d_cs) / (W_h * C_p));
        err = (t_f_h[n_CV] - f_temp) / t_f_h[n_CV];
        t_f_h[n_CV] = f_temp;

    } while (err > 0.001 || err < -0.001);
}

void out_cladding_T(int n_CV)
{

    double Re = 0;
    // 查表得
    double μ = find_μ(t_f_h[n_CV]);
    double Pr = find_Pr(t_f_h[n_CV]);
    double k = find_k(t_f_h[n_CV]);

    double temp_1 = 0;
    double temp_2 = 0;
    double h_z = 0;
    double t_s = 346.31097;

    D_e = 4 * (powf(s, 2) - (Pi / 4 * powf(d_cs, 2))) / (Pi * d_cs);

    Re = (W_h * D_e) / (A_b * μ);

    h_z = 0.023 * powf(Re, 0.8) * powf(Pr, 0.4) * k / D_e;
    temp_1 = q_ave * F_N_q * φ[n_CV] * F_E_q / h_z;
    temp_2 = 25 * powf(q_ave * F_N_R * φ[n_CV] * F_E_q / 1000000, 0.25) * exp(-(P*1000000 / 6.2)) + (t_s - temp_1);

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

void outside_UO2_T(int n_CV)
{

    // hg为包壳与芯快间的气息等效传热系数取 5678 W/(m^2·°C)
    

    printf("t_ci_h--%lf",t_ci_h[n_CV]);

    printf("t_u_h--%lf\n",t_u_h[n_CV]);
    double temp =   q_l_ave * F_N_R * F_E_q * φ[n_CV] /  (Pi * (d_ci+d_u)/2 * hg) ;
    t_u_h[n_CV] = t_ci_h[n_CV] + temp;
    printf("temp:%lf\n",temp);

    printf("t_ci_h--%lf",t_ci_h[n_CV]);

    printf("t_u_h--%lf\n",t_u_h[n_CV]);

}
void inside_UO2_T(int n_CV){
    // 数据为查表所得，关键在于查找算法
    double t_part1 = 0;
    double t_part2 = 0;
    double IHC = 0;


    

    t_part1 = find_UO2_fromT(t_u_h[n_CV]);
    printf("--\n");
    t_part2 = (q_l_ave * F_N_R * F_E_q * φ[n_CV]) /  ( 4 * Pi * 100 );
    IHC = t_part1 + t_part2;
    t_o_h[n_CV] = find_UO2_fromIHC(IHC);
    printf("--\n");

}

void get_q_DNBh(int n_CV){

    double x_e = (h_f_in - h_fs) / h_fg;
    // double G = 

    double part_1 = (2.022 - 6.238 * 10e-8 * P) + (0.1722 - 1.43 * 10e-8 * P) * exp(  (  18.177 - 5.987 * 10e-7 *P) * X1 );
    double part_2 = (0.1484 - 1.596 * X1 + 0.1729 * X1 * fabs(X1) ) * (0.2049 * G / 10e6) + 1.037;
    double part_3 = (1.157 - 0.869 * X1) * (0.2664 + 0.8357 * exp(-124 * D_e)) * (0.8258 + 0.341 * 10e-6*(h_fs - h_f_in));
    q_DNB_h[n_CV] = 3.154 * 10e6 * part_1 * part_2 * part_3;

}