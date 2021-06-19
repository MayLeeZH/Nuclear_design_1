//单位换算
double W_kg_s = W_t_h * 1000 / 3600;

//此处的为具有外部连接的变量
//sec_1 中使用
double f_out_S = 0; // 堆芯出口温度

//sec_2 中使用
double q_ave = 0;   // 燃料表面平均热流密度
double F_total = 0; // 堆芯内燃料棒的总传热面积
double q_max = 0;   // 燃料棒表面的最大热流密度
double q_l_ave = 0; // 平均线功率
double q_l_max = 0; // 最大线功率

//sec_3 中使用
double A_f = 0; // 堆芯内总流通面积 m2
double V = 0;   // 平均管流速 m/s
double A_b = 0; // 单元通道面积 m2
double W_h = 0; // 单元通道内流量 kg/s

//sec_4 中使用
double φ[] = {0.80,1.50,0.70,0.96,0.48,1.56};
double D_e = 0 ; //当量直径



double t_out_CV[6] = { 0, 0 ,0 ,0 ,0 ,0};
double t_cs_h[6] = { 0, 0 ,0 ,0 ,0 ,0};
double t_ci_h[6] = { 0, 0 ,0 ,0 ,0 ,0};
double t_u_h[6] = { 0, 0 ,0 ,0 ,0 ,0};


double G = 0; //质量流密度   = 密度 * 流速
