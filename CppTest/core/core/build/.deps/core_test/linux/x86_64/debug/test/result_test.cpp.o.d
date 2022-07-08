{
    depfiles_gcc = "result_test.o: test/result_test.cpp include/core/result.h  include/core/error_code.h include/core/error_domain.h  include/core/string_view.h include/core/optional.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/gtest.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/internal/gtest-internal.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/internal/gtest-port.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/internal/custom/gtest-port.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/internal/gtest-port-arch.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/gtest-message.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/internal/gtest-filepath.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/internal/gtest-string.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/internal/gtest-type-util.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/gtest-death-test.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/internal/gtest-death-test-internal.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/gtest-matchers.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/gtest-printers.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/internal/custom/gtest-printers.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/gtest-param-test.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/internal/gtest-param-util.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/gtest-test-part.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/gtest_prod.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/gtest-typed-test.h  /mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include/gtest/gtest_pred_impl.h\
",
    values = {
        "/usr/bin/gcc-9",
        {
            "-m64",
            "-g",
            "-O0",
            "-std=c++14",
            "-Iinclude",
            "-I/mnt/d/src/horizon/boyan_middleware/common/core/../../third_party/boost",
            "-I/mnt/d/src/horizon/boyan_middleware/out/tmprootfs/usr/include",
            "-DCORE_TEST",
            "-DNDEBUG"
        }
    },
    files = {
        "test/result_test.cpp"
    }
}