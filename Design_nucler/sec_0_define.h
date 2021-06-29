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
double φ[] = {0.48, 1.02, 1.50, 1.56, 0.96, 0.68};
double D_e = 0; //当量直径

// 雷诺数
double Re = 0;

double t_f_h[6] = {0, 0, 0, 0, 0, 0};
double t_cs_h[6] = {0, 0, 0, 0, 0, 0};
double t_ci_h[6] = {0, 0, 0, 0, 0, 0};
double t_u_h[6] = {0, 0, 0, 0, 0, 0};
double t_o_h[6] = {0, 0, 0, 0, 0, 0};
double q_DNB_h[6] = {0, 0, 0, 0, 0, 0};
double DNBR[6] = {0, 0, 0, 0, 0, 0};

double G = 0; //质量流密度   = 密度 * 流速
double hg = 5678;

#define LIM 8
#define NUM 1200
double data[NUM][LIM];

#define NUM_2 23
double data_UO2[NUM_2][2];

double h_fs = 1629.55 * 1000; // 15.5Mpa下的饱和水蒸汽比焓  单位J/kg 数据查表得
// 链接 https://wenku.baidu.com/view/bbd968030975f46526d3e13e.html

double h_f_in = 1268.52 * 1000; // 15.5Mpa下进口温度287°C下的水的比焓，由软件包计算得

double h_fg = 965.5 * 1000; //15.5Mpa下的水的气化潜热 单位J/g 数据查表得
                            // 链接 https://wenku.baidu.com/view/bbd968030975f46526d3e13e.html



// sec_5中使用
double d_P_f = 0;
double d_P_a = 0;
double d_P_el = 0;
double d_P_in = 0;
double d_P_out = 0;
double d_P_gr = 0;
double d_P = 0;
double g = 9.8;