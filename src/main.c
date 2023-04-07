
#include <autoconf.h>
#include <sel4test-vbtalloc/gen_config.h>

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>

#include <sel4runtime.h>

#include <allocman/bootstrap.h>
#include <allocman/vka.h>

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
#include <sel4platsupport/platsupport.h>

#include "wrapper.h"
#include "aimbench.h"
#include <sel4/benchmark_utilisation_types.h>

struct unienv {
    /* An initialised vka that may be used by the test. */
    vka_t vka;
    /* virtual memory management interface */
    vspace_t vspace;
    /* abtracts over kernel version and boot environment */
    simple_t simple;
};
typedef struct unienv *unienv_t;

#define ALLOCATOR_VIRTUAL_POOL_SIZE ((1 << seL4_PageBits) * 100)

#define ALLOCATOR_STATIC_POOL_SIZE ((1 << seL4_PageBits) * 20)

#define BRK_VIRTUAL_DEFAULT_SIZE ((1 << seL4_PageBits) * 100)

struct unienv env;
static sel4utils_alloc_data_t data;
static char allocator_mem_pool[ALLOCATOR_STATIC_POOL_SIZE];

extern vspace_t *muslc_this_vspace;
extern reservation_t muslc_brk_reservation;
extern void *muslc_brk_reservation_start;

static void init_env(unienv_t env)
{
    allocman_t *allocman;
    reservation_t virtual_reservation;
    int error;

    allocman = bootstrap_use_current_simple(&env->simple, ALLOCATOR_STATIC_POOL_SIZE, allocator_mem_pool);
    if (allocman == NULL) {
        ZF_LOGF("Failed to create allocman");
    }

    allocman_make_vka(&env->vka, allocman);

    error = sel4utils_bootstrap_vspace_with_bootinfo_leaky(&env->vspace,
                                                           &data, simple_get_pd(&env->simple),
                                                           &env->vka, platsupport_get_bootinfo());
    if (error) {
        ZF_LOGF("Failed to bootstrap vspace");
    }

    sel4utils_res_t *muslc_brk_reservation_memory = allocman_mspace_alloc(allocman, sizeof(sel4utils_res_t), &error);
    if (error) {
        ZF_LOGE("Failed to alloc virtual memory for muslc heap describing metadata");
    }

    error = sel4utils_reserve_range_no_alloc(&env->vspace, muslc_brk_reservation_memory,
                                             BRK_VIRTUAL_DEFAULT_SIZE, seL4_AllRights, 1, &muslc_brk_reservation_start);
    if (error) {
        ZF_LOGE("Failed to reserve range for muslc heap initialization");
    }

    muslc_this_vspace = &env->vspace;
    muslc_brk_reservation.res = muslc_brk_reservation_memory;

    void *vaddr;
    virtual_reservation = vspace_reserve_range(&env->vspace,
                                               ALLOCATOR_VIRTUAL_POOL_SIZE, seL4_AllRights, 1, &vaddr);
    if (virtual_reservation.res == 0) {
        ZF_LOGF("Failed to provide virtual memory for allocator");
    }

    bootstrap_configure_virtual_pool(allocman, vaddr,
                                     ALLOCATOR_VIRTUAL_POOL_SIZE, simple_get_pd(&env->simple));
}

void *__posix_entry(void *arg UNUSED)
{

    printf("\n>>>>>>>> __posix_entry__ <<<<<<<\n");
    printf("*********** Benchmark ***********\n\n");

    uint64_t *ipcbuffer = (uint64_t*) &(seL4_GetIPCBuffer()->msg[0]);
    seL4_BenchmarkResetThreadUtilisation(simple_get_tcb(&env.simple));
    seL4_BenchmarkResetLog();
    seL4_BenchmarkFinalizeLog();
    seL4_BenchmarkGetThreadUtilisation(simple_get_tcb(&env.simple));
    seL4_BenchmarkResetThreadUtilisation(simple_get_tcb(&env.simple));
    seL4_BenchmarkResetLog();

    int error = benchmark_wrapper();

    seL4_BenchmarkFinalizeLog();
    seL4_BenchmarkGetThreadUtilisation(simple_get_tcb(&env.simple));

    //printf("CPU cycles spent: %lld\n", ipcbuffer[BENCHMARK_TCB_UTILISATION] + ipcbuffer[BENCHMARK_TCB_KERNEL_UTILISATION]);
    printf("\n*********** Benchmark ***********\n");
    printf("\nCPU cycles spent: %lld\n", ipcbuffer[BENCHMARK_TCB_UTILISATION]);

    //!if (error != 0) {
    //!    printf("Error occur within benchmark!\n");
    //!} else {
    //!    printf("All benchmark testing passed!\n");
    //!}
}

#define POSIX_ENTRY __posix_entry

static void sel4test_exit(int code)
{
    seL4_TCB_Suspend(seL4_CapInitThreadTCB);
}

int main(void)
{
    sel4runtime_set_exit(sel4test_exit);

    seL4_BootInfo *info = platsupport_get_bootinfo();
    simple_default_init_bootinfo(&env.simple, info);

    init_env(&env);

    void *res;
    int error;

    error = sel4utils_run_on_stack(&env.vspace, POSIX_ENTRY, NULL, &res);
    
    test_assert_fatal(error == 0);
    test_assert_fatal(res == 0);

    return 0;
}