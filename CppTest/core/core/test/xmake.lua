add_defines("CORE_TEST")

set_installdir("$(env TARGET_TMPUNITTEST_DIR)/core")

target("core_test")
    set_kind("binary")
    add_includedirs("$(projectdir)/../../third_party/boost/")
    add_files("*.cpp")
    add_syslinks("pthread")
    add_includedirs("$(env TARGET_TMPROOTFS_DIR)/usr/include")
    add_linkdirs("$(env TARGET_TMPROOTFS_DIR)/usr/lib")
    add_links("gtest")
