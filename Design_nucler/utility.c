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
    while ((scanf("%lf", &t_f_h[n_CV]) != 1) || (t_f_h[n_CV] < 270 || t_f_h[n_CV] > 370))
    {
        printf("温度不符合，请重新输入:");
        fflush(stdin);
    }
}

void show_info(void)
{
    printf("堆芯出口温度为:%lf\n", f_out_S);
    printf("燃料棒表面平均热流密度:%lf W/m2\n", q_ave);
    printf("燃料棒表面最大热流密度:%lf W/m2\n", q_max);
    printf("燃料棒平均线功率为:%lf W/m\n", q_l_ave);
    printf("燃料棒最大线功率为:%lf W/m\n", q_l_max);
    printf("平均管流速:%lf m/s\n", V);
    printf("单元通道内流量:%lf kg/s\n", W_h);
    printf("单元通道面积:%lf m2\n", A_b);

    for (int n_CV = 0; n_CV < s_CV; n_CV++)
    {
        printf("\n");
        printf("----------------第%d控制体输出-----------------\n", n_CV + 1);

        printf("第%d控制体出口流温度%lf\n", n_CV + 1, t_f_h[n_CV]);
        printf("第%d控制体出口处的包壳外壁温%lf\n", n_CV + 1, t_cs_h[n_CV]);
        printf("第%d控制体出口处的包壳内壁温%lf\n", n_CV + 1, t_ci_h[n_CV]);
        printf("第%d控制体出口处的UO2芯快外表面温度%lf\n", n_CV + 1, t_u_h[n_CV]);
        printf("第%d控制体出口处的UO2芯快内表面温度%lf\n", n_CV + 1, t_o_h[n_CV]);
        printf("热管中的q_DNB_h(L%d)%elf\n", n_CV + 1, q_DNB_h[n_CV]);
        printf("DNBR:%lf\n", DNBR[n_CV]);
        printf("--------------------------------------------\n");
    }

    printf("单相流体摩擦压降: %lf Pa\n", d_P_f);
    printf("单相流体加速压降: %lf Pa\n", d_P_a);
    printf("单相流体提升压降: %lf Pa\n", d_P_el);
    printf("堆芯进口局部压降: %lf Pa\n", d_P_in);
    printf("堆芯出口局部压降: %lf Pa\n", d_P_out);
    printf("定位格架出口压降: %lf Pa\n", d_P_gr);
    printf("总的压降: %lf Pa\n", d_P);
}
void output_info(void)
{

    FILE *fp;
    if ((fp = fopen("result.txt", "w")) == NULL)
    {
        printf("结果数据导出错误\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%lf\n", f_out_S);
    fprintf(fp, "%lf\n", q_ave);
    fprintf(fp, "%lf\n", q_max);
    fprintf(fp, "%lf\n", q_l_ave);
    fprintf(fp, "%lf\n", q_l_max);
    fprintf(fp, "%lf\n", V);
    fprintf(fp, "%lf\n", W_h);
    fprintf(fp, "%lf\n", A_b);

    for (int n_CV = 0; n_CV < s_CV; n_CV++)
    {
        fprintf(fp,"%lf\n", t_f_h[n_CV]);
        fprintf(fp,"%lf\n", t_cs_h[n_CV]);
        fprintf(fp,"%lf\n", t_ci_h[n_CV]);
        fprintf(fp,"%lf\n", t_u_h[n_CV]);
        fprintf(fp,"%lf\n", t_o_h[n_CV]);
        fprintf(fp,"%lf\n", q_DNB_h[n_CV]/1e6);
        fprintf(fp,"%lf\n", DNBR[n_CV]);
    }

    fprintf(fp,"%lf\n", d_P_f);
    fprintf(fp,"%lf\n", d_P_a);
    fprintf(fp,"%lf\n", d_P_el);
    fprintf(fp,"%lf\n", d_P_in);
    fprintf(fp,"%lf\n", d_P_out);
    fprintf(fp,"%lf\n", d_P_gr);
    fprintf(fp,"%lf\n", d_P);
}

