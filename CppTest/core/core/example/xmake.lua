set_installdir("$(env TARGET_SDK_DIR)/core")

target("core_example")
  set_kind("binary")
  add_files("*.cpp")
  add_includedirs("$(projectdir)", "$(projectdir)/../../third_party/boost/")