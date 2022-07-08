{
    files = {
        "build/.objs/test/linux/x86_64/release/gtest.cpp.o",
        "build/.objs/test/linux/x86_64/release/test.cpp.o"
    },
    values = {
        "/usr/bin/g++",
        {
            "-m64",
            "-lgtest",
            "-lpthread"
        }
    }
}