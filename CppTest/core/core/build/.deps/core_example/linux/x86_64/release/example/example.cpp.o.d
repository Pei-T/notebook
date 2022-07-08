{
    values = {
        "/usr/bin/gcc-9",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++14",
            "-Iinclude",
            "-I/mnt/d/src/horizon/boyan_middleware/common/core",
            "-I/mnt/d/src/horizon/boyan_middleware/common/core/../../third_party/boost",
            "-DNDEBUG"
        }
    },
    depfiles_gcc = "example.o: example/example.cpp  /mnt/d/src/horizon/boyan_middleware/common/core/example/example.h  include/core/instance_specifier.h include/core/core_error_demain.h  include/core/error_code.h include/core/error_domain.h  include/core/string_view.h include/core/result.h include/core/optional.h  /mnt/d/src/horizon/boyan_middleware/common/core/example/example_error_domain.h\
",
    files = {
        "example/example.cpp"
    }
}