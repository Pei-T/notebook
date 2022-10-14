python
import sys
sys.path.insert(0, '/home/pei.tang/lx/prebuilts/host/gcc-linaro-6.5.0-2018.12-x86_64_aarch64-linux-gnu/share/gcc-6.5.0/python/')
from libstdcxx.v6.printers import register_libstdcxx_printers
register_libstdcxx_printers (None)
end


skip -gfi /usr/*
skip -gfi /usr/include/c++/9/bits/*.h
skip -gfi /home/pei.tang/boyan_middleware/buildtools/toolchains/gcc-ubuntu-9.3.0-2020.03-x86_64-aarch64-linux-gnu/aarch64-linux-gnu/include/c++/9/bits/*.h
skip -gfi /home/pei.tang/boyan_middleware/buildtools/toolchains/gcc-ubuntu-9.3.0-2020.03-x86_64-aarch64-linux-gnu/aarch64-linux-gnu/include/c++/9/*.h


define j5b
target remote 10.97.109.171:9923
b main
c
end

define j5a
target remote 10.97.109.171:9913
b main
c
end

define j5c
target remote 10.97.109.171:9933
b main
c
end

define log
set logging file gdb.out
set logging on
end


define cbt
c
bt
end

define a
s
bt
end

define c 
  continue
  refresh
end

define n
  next
  refresh
end
