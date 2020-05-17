#ifndef __MAIN__H__
#define __MAIN__H__

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "default.h"
#include "type.h"

#include "prototype.i"

#define STRING_RAW(x) #x
#define STRING(x) STRING_RAW(x)

#define ERROR(format, ...)                               \
do                                                       \
{                                                        \
  fprintf(stderr, "Error: " format "\n", ##__VA_ARGS__); \
  exit(EXIT_FAILURE);                                    \
}                                                        \
while(FALSE)                                             \

#define dump_plain_o(profile, name, start, end) dump_plain(profile, name, start, end, REGION_ORDER_STRING)
#define dump_plain_d(profile, name, start, end) dump_plain(profile, name, start, end, REGION_DISORDER_STRING)
#define dump_numeric_o(profile, name, position, lettet, value) dump_numeric(profile, name, position, lettet, value, REGION_ORDER_STRING)
#define dump_numeric_d(profile, name, position, lettet, value) dump_numeric(profile, name, position, lettet, value, REGION_DISORDER_STRING)

#define _FUNCTION_DECLARATION_BEGIN_
#define _FUNCTION_DECLARATION_END_

#endif
