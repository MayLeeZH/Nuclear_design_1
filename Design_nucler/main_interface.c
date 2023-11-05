// 核反应堆热工分析

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "system_parameter.h"
#include "sec_0_define.h"
#include "data_finder.c"
#include "utility.c"
#include "sec_1_outlet_temperature.c"
#include "sec_2_fuel_rod.c"
#include "sec_3_pipeInfo.c"
#include "sec_4_CV.c"
#include "sec_5_Pdrop.c"

#define VERSION "v 1.0.3"

int main(void)
{
    import_data();
    import_data_UO2();
    outlet_TEMP();
    fuel_serface_info();
    pipe_info();
    for (int n_CV = 0; n_CV < s_CV; n_CV++)
    {
        CV_info(n_CV);
    }
    pressureDrop();
    output_info();
    show_info();
    // system("python3 data_export.py");
    return 0;
}