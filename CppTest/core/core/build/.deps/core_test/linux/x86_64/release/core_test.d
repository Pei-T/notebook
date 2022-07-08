{
    files = {
        "build/.objs/core_test/linux/x86_64/release/test/errorcode_test.cpp.o",
        "build/.objs/core_test/linux/x86_64/release/test/errordomain_test.cpp.o",
        "build/.objs/core_test/linux/x86_64/release/test/instancespecifier_test.cpp.o",
        "build/.objs/core_test/linux/x86_64/release/test/main.cpp.o",
        "build/.objs/core_test/linux/x86_64/release/test/result_test.cpp.o"
    },
    values = {
        "/usr/bin/g++-9",
        {
            "-m64",
            "-L/mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/lib",
            "-s",
            "-lgtest",
            "-lpthread"
        }
    }
}