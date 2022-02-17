# std common func
## std::printf
```cpp
#include <cstdio>
#include <limits>
#include <cstdint>
#include <cinttypes>
 
int main()
{
    std::printf("Strings:\n");
 
    const char* s = "Hello";
    std::printf("\t[%10s]\n\t[%-10s]\n\t[%*s]\n\t[%-10.*s]\n\t[%-*.*s]\n",
        s, s, 10, s, 4, s, 10, 4, s);
 
    std::printf("Characters:\t%c %%\n", 65);
 
    std::printf("Integers\n");
    std::printf("Decimal:\t%i %d %.6i %i %.0i %+i %u\n", 1, 2, 3, 0, 0, 4, -1);
    std::printf("Hexadecimal:\t%x %x %X %#x\n", 5, 10, 10, 6);
    std::printf("Octal:\t%o %#o %#o\n", 10, 10, 4);
 
    std::printf("Floating point\n");
    std::printf("Rounding:\t%f %.0f %.32f\n", 1.5, 1.5, 1.5);
    std::printf("Padding:\t%05.2f %.2f %5.2f\n", 1.5, 1.5, 1.5);
    std::printf("Scientific:\t%E %e\n", 1.5, 1.5);
    std::printf("Hexadecimal:\t%a %A\n", 1.5, 1.5);
    std::printf("Special values:\t0/0=%g 1/0=%g\n", 0.0/0.0, 1.0/0.0);
 
    std::printf("Variable width control:\n");
    std::printf("right-justified variable width: '%*c'\n", 5, 'x');
    int r = std::printf("left-justified variable width : '%*c'\n", -5, 'x');
    std::printf("(the last printf printed %d characters)\n", r);
 
    // fixed-width types
    std::uint32_t val = std::numeric_limits<std::uint32_t>::max();
    std::printf("Largest 32-bit value is %" PRIu32 " or %#" PRIx32 "\n", val, val);
}
/*
Strings:
        [     Hello]
        [Hello     ]
        [     Hello]
        [Hell      ]
        [Hell      ]
Characters:     A %
Integers
Decimal:        1 2 000003 0  +4 4294967295
Hexadecimal:    5 a A 0x6
Octal:  12 012 04
Floating point
Rounding:       1.500000 2 1.30000000000000004440892098500626
Padding:        01.50 1.50  1.50
Scientific:     1.500000E+00 1.500000e+00
Hexadecimal:    0x1.8p+0 0X1.8P+0
Special values: 0/0=nan 1/0=inf
Variable width control:
right-justified variable width: '    x'
left-justified variable width : 'x    '
(the last printf printed 40 characters)
Largest 32-bit value is 4294967295 or 0xffffffff
*/
```

```cpp
/*
显示：0(默认)、1(粗体/高亮)、22(非粗体)、4(单条下划线)、24(无下划线)、5(闪烁)、25(无闪烁)、7(反显、翻转前景色和背景色)、27(无反显)
颜色值：0(黑)、1(红)、2(绿)、 3(黄)、4(蓝)、5(紫)、6(深绿)、7(白)
颜色分为背景色和字体色，30~39（30+颜色值）用来设置字体色（前景色），40~49（40+颜色值）设置背景（背景色）：如31表示前景色为红色，41表示背景色为红色。
*/
#define COLOR_NONE "\033[0;m"
#define RED "\033[0;31m"
#define LIGHT_RED "\033[1;31m"        //红色高亮
#define LIGHT_RED_INV "\033[5;7;31m"  //红色高亮，并反白显示，字体闪烁
#define GREEN "\033[0;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;34m"
#define LIGHT_BLUE "\033[1;34m"  //蓝色高亮
#define DRAY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define YELLOW "\033[0;33m"
#define LIGHT_YELLOW "\033[1;33m"  //黄色高亮
#define WHITE "\033[0;37m"
#define LIGHT_WHITE "\033[1;37m"  //白色高亮

/*
日志级别定义，数值越小，级别越高
*/
#define LOGGER_FATAL_LEVEL 1  //致命错误，不可恢复
#define LOGGER_ERROR_LEVEL 2  //一般错误，可恢复
#define LOGGER_WARN_LEVEL 3   //警告
#define LOGGER_INFO_LEVEL 4   //信息
#define LOGGER_DEBUG_LEVEL 5  //调试

/*
当前日志级别配置
*/
#define LOGGER_CFG_LEVEL LOGGER_DEBUG_LEVEL

#define logger_level_printf(level, fmt, arg...)          \
  do {                                                   \
    if (level <= LOGGER_CFG_LEVEL) {                     \
      printf("[%s,%d] " fmt, __FILE__, __LINE__, ##arg); \
    }                                                    \
  } while (0)

#define logger_fatal(fmt, arg...) \
  logger_level_printf(LOGGER_FATAL_LEVEL, LIGHT_RED_INV fmt COLOR_NONE, ##arg)
#define logger_error(fmt, arg...) \
  logger_level_printf(LOGGER_ERROR_LEVEL, LIGHT_RED fmt COLOR_NONE, ##arg)
#define logger_warn(fmt, arg...) \
  logger_level_printf(LOGGER_WARN_LEVEL, LIGHT_YELLOW fmt COLOR_NONE, ##arg)
#define logger_info(fmt, arg...) \
  logger_level_printf(LOGGER_INFO_LEVEL, LIGHT_BLUE fmt COLOR_NONE, ##arg)
#define logger_debug(fmt, arg...) \
  logger_level_printf(LOGGER_DEBUG_LEVEL, LIGHT_WHITE fmt COLOR_NONE, ##arg)

```