#ifndef TWCOMMON_HPP
#define TWCOMMON_HPP

#ifndef BUILD_TWRPTAR_MAIN
#include "gui/gui.h"
#define LOGERR(fmt, ...) gui_print_color("error", "E:[%s:%d]" fmt, __FILE__/*__FUNCTION__*/, __LINE__, ##__VA_ARGS__)
#define LOGINFO(fmt, ...) fprintf(stdout, "I:[%s:%d]" fmt, __FILE__/*__FUNCTION__*/, __LINE__, ##__VA_ARGS__)
#else
#include <stdio.h>
#define LOGERR(...) printf("E:" __VA_ARGS__)
#define LOGINFO(...) printf("I:" __VA_ARGS__)
#define gui_print(...) printf( __VA_ARGS__ )
#endif

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

#endif  // TWCOMMON_HPP
