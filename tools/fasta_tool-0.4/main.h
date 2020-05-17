#ifndef __MAIN__H__
#define __MAIN__H__

#define _GNU_SOURCE

#include <crypt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "default.h"
#include "type.h"

#include "prototype.i"

#define ERROR(format, ...)                               \
do                                                       \
{                                                        \
  fprintf(stderr, "Error: " format "\n", ##__VA_ARGS__); \
  exit(EXIT_FAILURE);                                    \
}                                                        \
while(FALSE)                                             \


#define _FUNCTION_DECLARATION_BEGIN_
#define _FUNCTION_DECLARATION_END_

#endif
