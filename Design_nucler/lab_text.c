#include "stdio.h"
#include "math.h"

int main(void){


    double res_1 = 0;
    double res_2 = 0;
    double res = 0;
    double num1 = 0.68626e-6;


    // printf("%lf",num1 * 1000000000000000000);

    res_1 = (148.28 - 18.14) * (214.23 - 2.99);
    res_2 = 6.2 - 2 * num1 * (148.28 - 18.14) * 214.23 - 0.51;
    res = res_1/res_2;


    printf("%lf",res);


    return 0;
}