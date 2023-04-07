
#include <autoconf.h>
#include <sel4test-vbtalloc/gen_config.h>
#include "wrapper.h"

//!
//!
//!
#include "aimbench.h"

#include <stdio.h>

int benchmark_wrapper()
{
    int error = 0;

    //error += aimbench_testcase_ram_copy();
    error += aimbench_testcase_mem_rtns_1();
    //error += aimbench_testcase_mem_rtns_2();
    //error += aimbench_testcase_sieve();
    //error += aimbench_testcase_brk_test();
    ////error += aimbench_testcase_page_test();
    
    //error += aimbench_testcase_add_test();
    //error += aimbench_testcase_div_test();
    
    //error += aimbench_testcase_fun_cal();
    //error += aimbench_testcase_fun_cal1();
    //error += aimbench_testcase_fun_cal2();
    //error += aimbench_testcase_fun_cal15();
    
    //error += aimbench_testcase_mul_test();
    //error += aimbench_testcase_num_rtns_1();
    //error += aimbench_testcase_trig_rtns();
    //error += aimbench_testcase_matrix_rtns();
    //error += aimbench_testcase_array_rtns();
    //error += aimbench_testcase_series_1();

    return error;
}
