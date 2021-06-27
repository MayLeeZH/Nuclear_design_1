

// 在压强为15.5Mp下导入C_p随温度从280度到345度的变化
void import_data_C_p(){

    FILE *fp;
    double ch;
    
    if ((fp = fopen("data_C_p","r"))  == NULL)
    {
        printf("有关C_p的数据打开失败，请检查数据文件是否存在，文件名是否更改");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM; i++)
    {
        fscanf(fp,"%lf",&data[i][0]);
        fscanf(fp,"%lf",&data[i][1]);
    }

    fclose(fp);
}
// 导入积分热导率和温度的关系
void import_data_UO2(){
    FILE *fp;
    double ch;
    
    if ((fp = fopen("data_UO2","r"))  == NULL)
    {
        printf("有关UO2积分热导率的数据打开失败，请检查数据文件是否存在，文件名是否更改");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_2; i++)
    {
        fscanf(fp,"%lf",&data_UO2[i][0]);
        fscanf(fp,"%lf",&data_UO2[i][1]);
    }

    fclose(fp);
}

double find_C_p(double f_avg){
    for (int i = 0; i < (NUM-1); i++)
    {

        if (f_avg > data[i][0] && f_avg < data[i+1][0])
        {
            return 1000 * (data[i][1]+data[i+1][1])/2;
        }
        else if (f_avg == data[i][0])
        {
            return 1000 * data[i][1];
        }
    }
    printf("数据有错误，温度超出了合适的范围，导致没有C_p匹配，程序异常结束，请检查\n");
    exit(EXIT_FAILURE);
    
}
double find_UO2_fromT(double f_u_h){
    for (int i = 0; i < NUM_2 - 1; i++)
    {
        if (f_u_h > data_UO2[i][0] && f_u_h<data_UO2[i+1][0])
        {
            return ( (f_u_h-data_UO2[i][0])/(data_UO2[i+1][0] - data_UO2[i][0])  * (data_UO2[i+1][1] - data_UO2[i][1] ) ) + data_UO2[i][1] ;
        }
        else if (f_u_h == data_UO2[i][0])
        {
            return data_UO2[i][1];
        }
    }
    printf("数据有错误，导致积分热导率超出表的范围，请检查");
    exit(EXIT_FAILURE);
    
}

double find_UO2_fromIHC(double IHC){
    for (int i = 0; i < NUM_2 - 1; i++)
    {
        if (IHC > data_UO2[i][1] && IHC < data_UO2[i+1][1])
        {
            return ( (IHC - data_UO2[i][1])/(data_UO2[i+1][1] - data_UO2[i][1])  * (data_UO2[i+1][0] - data_UO2[i][0]) ) + data_UO2[i][0] ;
        }
        else if (IHC == data_UO2[i][1])
        {
            return data_UO2[i][0];
        } 
    }
    printf("数据有错误，导致积分热导率超出表的范围，请检查");
    exit(EXIT_FAILURE);
}