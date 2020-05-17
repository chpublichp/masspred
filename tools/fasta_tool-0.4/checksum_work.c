#include "main.h"

#define SALT "$1$fasta"

_FUNCTION_DECLARATION_BEGIN_
void checksum_work(char* name)
_FUNCTION_DECLARATION_END_
{
  struct crypt_data data;
  char* result;

  data.initialized = 0;
  result = crypt_r(name, SALT, &data);
  printf
  (
    "DIR_1=\"%01x%01x\"\n"
    "DIR_2=\"%01x%01x\"\n",
    result[sizeof SALT+1]&0xf,
    result[sizeof SALT+2]&0xf,
    result[sizeof SALT+3]&0xf,
    result[sizeof SALT+4]&0xf
  );
}
