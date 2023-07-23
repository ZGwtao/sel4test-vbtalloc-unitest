#include <autoconf.h>
#include <sel4vka/gen_config.h>
#include <sel4allocman/gen_config.h>
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
    vka_t vka;
    vspace_t vspace;
    simple_t simple;
};
typedef struct unienv *unienv_t;

#define ALLOCATOR_VIRTUAL_POOL_SIZE ((1ul << (seL4_PageBits + 22)))
#define ALLOCATOR_STATIC_POOL_SIZE ((1ul << seL4_PageBits) * 400)
#define BRK_VIRTUAL_DEFAULT_SIZE ((1ul << (seL4_PageBits + 16)))

struct unienv env;
static sel4utils_alloc_data_t data;
static char allocator_mem_pool[ALLOCATOR_STATIC_POOL_SIZE];
static allocman_t *global_allocator;

extern vspace_t *muslc_this_vspace;
extern reservation_t muslc_brk_reservation;
extern void *muslc_brk_reservation_start;

#define _posix_entry_ __posix_entry

static void init_env(unienv_t env)
{
    allocman_t *allocman;
    reservation_t virtual_reservation;
    int error;

    allocman = bootstrap_use_current_simple(&env->simple, ALLOCATOR_STATIC_POOL_SIZE, allocator_mem_pool);
    if (allocman == NULL)
    {
        ZF_LOGF("Failed to create allocman");
    }

    allocman_make_vka(&env->vka, allocman);

    error = sel4utils_bootstrap_vspace_with_bootinfo_leaky(&env->vspace,
                                                           &data, simple_get_pd(&env->simple),
                                                           &env->vka, platsupport_get_bootinfo());
    if (error)
    {
        ZF_LOGF("Failed to bootstrap vspace");
    }

    sel4utils_res_t *muslc_brk_reservation_memory = allocman_mspace_alloc(allocman, sizeof(sel4utils_res_t), &error);
    if (error)
    {
        ZF_LOGE("Failed to alloc virtual memory for muslc heap describing metadata");
    }

    error = sel4utils_reserve_range_no_alloc(&env->vspace, muslc_brk_reservation_memory,
                                             BRK_VIRTUAL_DEFAULT_SIZE, seL4_AllRights, 1, &muslc_brk_reservation_start);
    if (error)
    {
        ZF_LOGE("Failed to reserve range for muslc heap initialization");
    }

    muslc_this_vspace = &env->vspace;
    muslc_brk_reservation.res = muslc_brk_reservation_memory;

    void *vaddr;
    virtual_reservation = vspace_reserve_range(&env->vspace,
                                               ALLOCATOR_VIRTUAL_POOL_SIZE, seL4_AllRights, 1, &vaddr);
    if (virtual_reservation.res == 0)
    {
        ZF_LOGF("Failed to provide virtual memory for allocator");
    }

    bootstrap_configure_virtual_pool(allocman, vaddr,
                                     ALLOCATOR_VIRTUAL_POOL_SIZE, simple_get_pd(&env->simple));
    
    global_allocator = global_allocator ? global_allocator : allocman;
}

int get_random_size_1()
{
    int a = random() % 1024;
    while (a == 0)
    {
        a = random() % 1024;
    }
    return a;
}

int get_random_size_2()
{
    int a[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int b = random() % 11;
    return a[b];
}

int get_random_size_3()
{
    int a[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int b = (random() % 1024) + 1;
    if (b == 1)
    {
        return a[10];
    }
    else if (b == 2)
    {
        return a[9];
    }
    else if (2 < b && b <= 4)
    {
        return a[8];
    }
    else if (4 < b && b <= 8)
    {
        return a[7];
    }
    else if (8 < b && b <= 16)
    {
        return a[6];
    }
    else if (16 < b && b <= 32)
    {
        return a[5];
    }
    else if (32 < b && b <= 64)
    {
        return a[4];
    }
    else if (64 < b && b <= 128)
    {
        return a[3];
    }
    else if (128 < b && b <= 256)
    {
        return a[2];
    }
    else if (256 < b && b <= 512)
    {
        return a[1];
    }
    else if (512 < b && b <= 1024)
    {
        return a[0];
    }
}

int get_random_time(int a)
{
    int b = random() % a;
    while (b == 0)
    {
        b = random() % a;
    }
    return b;
}

#define MCMC_ITERATION_TIME 50000
#define MCMC_FREE_FREQUENCY 5000

typedef struct mcmc_memory_block {
    size_t time_stamp;
    seL4_Word origin_ut;
    seL4_CPtr frame_cptr_base;
    size_t frame_number;
 /* vka_object_t block; */
} mcmc_memory_block_t;

mcmc_memory_block_t mcmc_memory_block_array[MCMC_ITERATION_TIME];
vka_object_t mcmc_compressed_block_array[BIT(10) * MCMC_ITERATION_TIME];

/**
 * Monte Carlo experiment simulation function:
 *  1. (TODO)
 *  2. (TOFO)
 */
static int mcmc_exp_simulation()
{
#undef MCMC_SIZE_PRINT
#define MCMC_SIZE_PRINT(SZ) (CTZL(SZ)+(seL4_PageBits))
#undef MCMC_TIME_MATCH
#define MCMC_TIME_MATCH(X1,X2) (X1 == X2)
    vka_t *vka = &env.vka;
    size_t memory_footprint = 0;
    int mcmc_errno = seL4_NoError;
    int i;
    /**
     * ta: to-allocate;
     * tf: to-free;
     * time_stamp: a point within the MCMC time serie.
     * frame_count: number of frames to alloc/free at this time.
     */
    size_t ta_time_stamp, ta_frame_count;
    size_t tf_time_stamp, tf_frame_count;

    //vka_object_t *tx= (vka_object_t *)malloc(sizeof(vka_object_t));

    for (i = 0; i < MCMC_ITERATION_TIME; i++)
    {
        //memset(tx, 0, sizeof(vka_object_t));
        ta_frame_count = get_random_size_2();
        ta_time_stamp = get_random_time(MCMC_FREE_FREQUENCY) + i;

        memory_footprint += ta_frame_count;

        //printf("[ TIME ] :: %d >> ", i);

        //mcmc_errno = vka_alloc_frame(vka, seL4_PageBits, tx);
        mcmc_errno = vka_alloc_frame(vka, seL4_PageBits, &mcmc_compressed_block_array[i * 1024]);
        if (mcmc_errno != seL4_NoError) {
            ZF_LOGE("Failed to allocate memory block of size: %d", MCMC_SIZE_PRINT(ta_frame_count));
            goto stub;
        }
        //seL4_CPtr tmp_cptr = tx->cptr;
        //seL4_Word tmp_ut = tx->ut;
        seL4_CPtr tmp_cptr = mcmc_compressed_block_array[i * 1024].cptr;
        seL4_Word tmp_ut = mcmc_compressed_block_array[i * 1024].ut;
        mcmc_memory_block_array[i].time_stamp = ta_time_stamp;
        mcmc_memory_block_array[i].origin_ut = tmp_ut;
        mcmc_memory_block_array[i].frame_cptr_base = tmp_cptr;
        mcmc_memory_block_array[i].frame_number = ta_frame_count;

        for (int offset = 1; offset < ta_frame_count; ++offset) {
            /**
             * Try to allocate offset (0 < offset < size) frames per 'mcmc_allocate'
             * (FIXME) what does 1024 mean?
             */
            //mcmc_errno = vka_alloc_frame(vka, seL4_PageBits, tx);
            mcmc_errno = vka_alloc_frame(vka, seL4_PageBits, &mcmc_compressed_block_array[i * 1024 + offset]);
            if (mcmc_errno != seL4_NoError)
            {
                ZF_LOGE("Failed to allocate memory block of size: %d", MCMC_SIZE_PRINT(ta_frame_count));
                goto stub;
            }
        }
        //printf("[ ALLOC ] :: alloc_block { ta_frame_count: %d, ta_time_stamp: %d }", MCMC_SIZE_PRINT(mcmc_memory_block_array[i].frame_number), ta_time_stamp);
        for (int j = 0; j < i; j++)
        {
            tf_time_stamp = mcmc_memory_block_array[j].time_stamp;
            tf_frame_count = mcmc_memory_block_array[j].frame_number;
            /**
             * Free it when you match it.
             * i: (current time)
             * j: (any time before i)
             * We need to collect all allocated blocks before timestamp[i] that holds a 'i' value time_stamp
             */
            if (MCMC_TIME_MATCH(tf_time_stamp, i))
            {
                //tx->size_bits = seL4_PageBits;
                //tx->cptr = mcmc_memory_block_array[j].frame_cptr_base;
                for (int offset = 0; offset < tf_frame_count; ++offset) {
                    /**
                     * Like 'alloc', all frames should be freed one by one.
                    */
                    //printf("\n%d, %d, %d, %d\n", tx->cptr, tx->size_bits, tx->type, tx->ut);
                    //vka_free_object(vka, tx);
                    vka_free_object(vka, &mcmc_compressed_block_array[j * 1024 + offset]);
                }
                //printf(" [ FREE ] :: free_block { ta_frame_count: %d, time: %ld } ", MCMC_SIZE_PRINT(tf_frame_count), tf_time_stamp);
            }
        }
        //printf("\n");
    }
stub:
    //free(tx);
    printf("current memory footprint: %ld, %d\n", memory_footprint, i);
    return mcmc_errno;

#undef MCMC_TIME_MATCH
#undef MCMC_SIZE_PRINT
}

void *__posix_entry(void *arg UNUSED)
{
    printf("\n>>>>>>>> __posix_entry__ <<<<<<<\n");
    printf("*********** Benchmark ***********\n\n");

    int error;
    unsigned long long time[50];
    unsigned long long start = 0, end = 0;

    uint64_t *ipcbuffer = (uint64_t *)&(seL4_GetIPCBuffer()->msg[0]);

    seL4_BenchmarkResetThreadUtilisation(simple_get_tcb(&env.simple));
    seL4_BenchmarkResetLog();

    error = mcmc_exp_simulation();

    seL4_BenchmarkFinalizeLog();
    seL4_BenchmarkGetThreadUtilisation(simple_get_tcb(&env.simple));

    printf("\n*********** Benchmark ***********\n");
    printf("\nCPU cycles spent: %ld\n", ipcbuffer[BENCHMARK_TCB_UTILISATION]);
}

static void sel4test_exit(int code)
{
    seL4_TCB_Suspend(seL4_CapInitThreadTCB);
}

int main(void)
{
    sel4runtime_set_exit(sel4test_exit);

    seL4_BootInfo *info = platsupport_get_bootinfo();
    simple_default_init_bootinfo(&env.simple, info);
    simple_print(&env.simple);
    init_env(&env);

    void *res;
    int error;

    error = sel4utils_run_on_stack(&env.vspace, _posix_entry_, NULL, &res);

    test_assert_fatal(error == 0);
    test_assert_fatal(res == 0);

    return 0;
}
