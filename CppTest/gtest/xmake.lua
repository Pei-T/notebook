--[[
 Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 Unauthorized copying of this file, via any medium is strictly prohibited
 Proprietary and confidential
--]]

-- set_installdir("$(env TARGET_SDK_DIR)/core")

target("test")
  set_kind("binary")
  add_files("*.cpp")
  add_includedirs("$(projectdir)/../../common/core/include/")
  -- add_includedirs("$(projectdir)/../../third_party/boost/")
  -- add_includedirs("/home/pei.tang/.local/include/")
  add_syslinks("pthread")
  add_links("gtest")