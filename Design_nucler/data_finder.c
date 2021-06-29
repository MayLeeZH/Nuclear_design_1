

// 在压强为15.5Mp下导入C_p随温度从280度到345度的变化
void import_data()
{

    // 第一项为温度 第二项为定压比热容 第三项为比焓 单位kj/kg 第四项为动力粘度 第五项为导热系 单位w/(m · °C) 第6六项为普朗特常数 第七项为运动粘度 第八项为比容

    FILE *fp;
    double ch;

    if ((fp = fopen("data.txt", "r")) == NULL)
    {
        printf("数据打开失败，请检查数据文件是否存在，文件名是否更改");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            fscanf(fp, "%lf", &data[i][j]);
        }
    }    

    fclose(fp);
}
// 导入积分热导率和温度的关系
void import_data_UO2()
{
    FILE *fp;
    double ch;

    if ((fp = fopen("data_UO2", "r")) == NULL)
    {
        printf("有关UO2积分热导率的数据打开失败，请检查数据文件是否存在，文件名是否更改");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_2; i++)
    {
        fscanf(fp, "%lf", &data_UO2[i][0]);
        fscanf(fp, "%lf", &data_UO2[i][1]);
    }

    fclose(fp);
}

double find_C_p(double f_avg)
{

    for (int i = 0; i < (NUM - 1); i++)
    {
        // printf("%d--%lf\n",i,f_avg);

        // printf("%lf--%lf--%lf\n",data[i][0],f_avg,data[i+1][0]);
        if (f_avg > data[i][0] && f_avg < data[i + 1][0])
        {
            return 1000 * (data[i][1] + data[i + 1][1]) / 2;
        }
        else if (f_avg == data[i][0])
        {
            return 1000 * data[i][1];
        }
    }
    printf("数据有错误，温度超出了合适的范围，导致没有C_p匹配，程序异常结束，请检查\n");
    exit(EXIT_FAILURE);
}

// 查找动力粘度
double find_μ (double t_f_h){

     for (int i = 0; i < (NUM - 1); i++)
    {
        if (t_f_h > data[i][0] && t_f_h < data[i + 1][0])
        {
            return (data[i][6] + data[i + 1][6]) / 2;
        }
        else if (t_f_h == data[i][0])
        {
            return data[i][6];
        }
    }

    printf("数据有错误，温度超出了合适的范围，导致没有数据匹配，程序异常结束，请检查\n");
    exit(EXIT_FAILURE);

}
// 查找导热系数
double find_k(double t_f_h){

     for (int i = 0; i < (NUM - 1); i++)
    {

        if (t_f_h > data[i][0] && t_f_h < data[i + 1][0])
        {
            return (data[i][4] + data[i + 1][4]) / 2;
        }
        else if (t_f_h == data[i][0])
        {
            return data[i][4];
        }
    }

    printf("数据有错误，温度超出了合适的范围，导致没有数据匹配，程序异常结束，请检查\n");
    exit(EXIT_FAILURE);

}

// 查找普朗特数
double find_Pr(double t_f_h){
    for (int i = 0; i < (NUM - 1); i++)
    {

        if (t_f_h > data[i][0] && t_f_h < data[i + 1][0])
        {
            return (data[i][4] + data[i + 1][5]) / 2;
        }
        else if (t_f_h == data[i][0])
        {
            return data[i][5];
        }
    }

    printf("数据有错误，温度超出了合适的范围，导致没有数据匹配，程序异常结束，请检查\n");
    exit(EXIT_FAILURE);

}





double find_UO2_fromT(double f_u_h)
{
    for (int i = 0; i < NUM_2 - 1; i++)
    {
        if (f_u_h > data_UO2[i][0] && f_u_h < data_UO2[i + 1][0])
        {
            return ((f_u_h - data_UO2[i][0]) / (data_UO2[i + 1][0] - data_UO2[i][0]) * (data_UO2[i + 1][1] - data_UO2[i][1])) + data_UO2[i][1];
        }
        else if (f_u_h == data_UO2[i][0])
        {
            return data_UO2[i][1];
        }
    }
    printf("数据有错误，导致积分热导率超出表的范围，请检查");
    exit(EXIT_FAILURE);
}

double find_UO2_fromIHC(double IHC)
{
    for (int i = 0; i < NUM_2 - 1; i++)
    {
        if (IHC > data_UO2[i][1] && IHC < data_UO2[i + 1][1])
        {
            return ((IHC - data_UO2[i][1]) / (data_UO2[i + 1][1] - data_UO2[i][1]) * (data_UO2[i + 1][0] - data_UO2[i][0])) + data_UO2[i][0];
        }
        else if (IHC == data_UO2[i][1])
        {
            return data_UO2[i][0];
        }
    }
    printf("数据有错误，导致积分热导率超出表的范围，请检查");
    exit(EXIT_FAILURE);
}


// 查找15.5Mpa压力下水的密度
double find_ρ(double t_f_h){
     for (int i = 0; i < (NUM - 1); i++)
    {
        // 通过返回比容的倒数获得密度
        if (t_f_h > data[i][0] && t_f_h < data[i + 1][0])
        {
            return  1 / ((data[i][7] + data[i + 1][7]) / 2)   ;
        }
        else if (t_f_h == data[i][0])
        {
            return 1 / data[i][7];
        }
    }

    printf("数据有错误，温度超出了合适的范围，导致没有密度数据匹配，程序异常结束，请检查\n");
    exit(EXIT_FAILURE);

}

// 查找15.5Mpa压力下水的比焓
double find_h(double t_f_h){
     for (int i = 0; i < (NUM - 1); i++)
    {
        // 返回时即转换单位为j/kg
        if (t_f_h > data[i][0] && t_f_h < data[i + 1][0])
        {
            return   1000 * (data[i][2] + data[i + 1][2]) / 2   ;
        }
        else if (t_f_h == data[i][0])
        {
            return  1000 * data[i][2];
        }
    }

    printf("数据有错误，温度超出了合适的范围，导致没有比焓数据匹配，程序异常结束，请检查\n");
    exit(EXIT_FAILURE);

}
// 通过温度查找15.5Mpa压力下对应的比容
double find_υ(double t_f_h){
     for (int i = 0; i < (NUM - 1); i++)
    {
        // 返回时即转换单位为j/kg
        if (t_f_h > data[i][0] && t_f_h < data[i + 1][0])
        {
            return (data[i][7] + data[i + 1][7]) / 2   ;
        }
        else if (t_f_h == data[i][0])
        {
            return data[i][7];
        }
    }

    printf("数据有错误，温度超出了合适的范围，导致没有比容数据匹配，程序异常结束，请检查\n");
    exit(EXIT_FAILURE);

}