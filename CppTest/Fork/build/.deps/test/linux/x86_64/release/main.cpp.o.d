{
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-I/home/pei.tang/boyan_middleware/.tmp/Fork/../../common/core/include"
        }
    },
    depfiles_gcc = "main.o: main.cpp Fork.hpp\
",
    files = {
        "main.cpp"
    }
}