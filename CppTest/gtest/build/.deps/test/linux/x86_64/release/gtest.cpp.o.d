{
    files = {
        "gtest.cpp"
    },
    depfiles_gcc = "gtest.o: gtest.cpp header.h\
",
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-I/home/pei.tang/boyan_middleware/.tmp/gtest/../../common/core/include"
        }
    }
}