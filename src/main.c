
#include <autoconf.h>
#include <sel4test-vbtalloc/gen_config.h>

#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>

#include <sel4runtime.h>

#include <allocman/bootstrap.h>
#include <allocman/vka.h>

#include <cpio/cpio.h>
#include <platsupport/local_time_manager.h>
#include <sel4platsupport/timer.h>
#include <sel4debug/register_dump.h>
#include <sel4platsupport/device.h>
#include <sel4platsupport/platsupport.h>
#include <sel4utils/vspace.h>
#include <sel4utils/stack.h>
#include <sel4utils/process.h>
#include <sel4test/test.h>
#include <simple/simple.h>
#include <simple-default/simple-default.h>
#include <utils/util.h>
#include <vka/object.h>
#include <vka/capops.h>
#include <vspace/vspace.h>
#include <sel4platsupport/io.h>

//typedef struct env {
//
//    vka_t vka;
//
//    vspace_t vspace;
//
//    simple_t bs_info;
//
//} env_t;
//
//env_t vbtalloc_env;

static void sel4test_exit(int code)
{
    seL4_TCB_Suspend(seL4_CapInitThreadTCB);
}

int main(void)
{
    sel4runtime_set_exit(sel4test_exit);

//    seL4_BootInfo *info = platsupport_get_bootinfo();
//    simple_default_init_bootinfo(&vbtalloc_env.bs_info, info);
//
//    vbtalloc_env.vka = init_allocator();

    return 0;
}