-- define project
set_project("core")

-- set common config
add_rules("mode.debug", "mode.release")
set_languages("c99", "cxx14")
--set_warnings("all", "error")
add_cxflags("-DNDEBUG")
add_includedirs("./include")
set_installdir("$(env TARGET_TMPROOTFS_DIR)/usr")
add_installfiles("include/(core/*.h)", {prefixdir = "include"})

if is_mode("debug") then
  set_symbols("debug")
  set_optimize("none")
  print('debug mode')
end

if is_mode("release") then
  set_optimize("fastest")
  set_strip("all")
  print('release mode')
end

if is_arch("x86_64") then
    print('arch: x86_64')
    set_toolchains("gcc-9")
    set_config("sdk", "/usr/")
    set_config("bin", "/usr/bin/")
    set_config("p", "linux")
    set_config("a", "x86_64")
    set_config("cc", "gcc")
    set_config("cxx", "g++")
end

-- includes sub-projects
includes("test", "example")


