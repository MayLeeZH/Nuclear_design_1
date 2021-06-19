// #include "system_parameter.h"

// 该函数有些冗杂，需要优化，并且有漏洞
void checkinput_outT(void)
{
    printf("假设出口温度:（310°C —— 330°C)\n");
    while ((scanf("%lf", &f_out_S) != 1) || (f_out_S < 310 || f_out_S > 330))
    {
        printf("输入因为数字且介于310 —— 330之间\n");
        printf("请重新输入:");
        fflush(stdin);
    }
}
// 代码风格有些不统一了，需要优化
void checkinput_out_CVT(int n_CV)
{
    printf("假设%d控制体出口温度:\n", n_CV + 1);
    while ((scanf("%lf", &t_out_CV[n_CV]) != 1) || (t_out_CV[n_CV] < 270 || t_out_CV[n_CV] > 330))
    {
        printf("温度不符合，请重新输入:");
        fflush(stdin);
    }
}

void output_info(void)
{
    printf("堆芯出口温度为:%lf\n", f_out_S);
    printf("燃料棒表面平均热流密度:%lf W/m2\n", q_ave);
    printf("燃料棒表面最大热流密度:%lf W/m2\n", q_max);
    printf("燃料棒平均线功率为:%lf W/m2\n", q_l_ave);
    printf("燃料棒最大线功率为:%lf W/m2\n", q_l_max);
    printf("平均管流速:%lf m/s\n", V);
    printf("单元通道内流量:%lf kg/s\n", W_h);
    printf("单元通道面积:%lf m2\n", A_b);

    for (int n_CV = 0; n_CV < s_CV; n_CV++)
    {
        printf("\n");
        printf("----------------第%d控制体输出-----------------\n",n_CV);

        printf("第%d控制体出口流温度%lf\n", n_CV + 1, t_out_CV[n_CV]);
        printf("第%d控制体出处的包壳外壁温%lf\n", n_CV + 1, t_cs_h[n_CV]);
        printf("第%d控制体出处的包壳内壁温%lf\n", n_CV + 1, t_ci_h[n_CV]);
        printf("第%d控制体出处的UO2芯快外表面温度%lf\n", n_CV + 1, t_u_h[n_CV]);
        printf("--------------------------------------------\n");

    }
}