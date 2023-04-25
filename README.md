# CapBuddy unitests executing framework based on sel4test
The aim of this project is to provide a executing framework for all testing programs that employ CapBuddy, and are implemented with seL4 LibOS. We refer to the build method of **apps** in [sel4test](https://github.com/seL4/sel4test) and use the utils in CapBuddy related [seL4_Libs](https://github.com/ZGwtao/seL4_libs-vbtalloc-extension) to set up the overall working framework for this project.

*System requirements:*
**This project will use utils from seL4_Libs, thus, following requirements should be meet.**
When building a project with the support of CapBuddy in libsel4allocman and libsel4vka, one can use the building method provided by [sel4test](https://github.com/seL4/sel4test-manifest.git) and [seL4 Buildsystem](https://docs.sel4.systems/projects/buildsystem/using.html). Some CMake options should also be added:

* -DLibVKAAllowPoolOperations=ON (CapBuddy support)
* -DLibAllocmanAllowPoolOperations=ON (CapBuddy support)
* -DKernelRetypeFanOutLimit=1024 (4M -> pre-allocation 1024 4K)
* -DKernelRootCNodeSizeBits=18 (or larger, just for recommendation)
* -DLibSel4MuslcSysMorecoreBytes=0 (for libsel4muslcsys, when pager is missing, and we still want a dynamic heap)

*Codebase structure:*
* src/
*   ├── aimbench.c  (*example POSIX layer testing program => part of aimbench*)
*   ├── aimbench.h  (*aimbench's header file*)
*   ├── main.c      (*entry of sel4test-vbtalloc testbench framework*)
*   ├── sel4test-vbtalloc-MURbench (*submodule => including Monte Carlo experiment and some micro-benchmarks for CapBuddy*)
*   │   ├── README.md
*   │   └── benchmark_test.c (*replace src/main.c to work*)
*   ├── wrapper.c   (*wrapper function for POSIX*)
*   └── wrapper.h   (*wrapper's header*)
