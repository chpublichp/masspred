#include "main.h"

_FUNCTION_DECLARATION_BEGIN_
FILE* open_file(char* output_file_prefix, char* output_file_suffix)
_FUNCTION_DECLARATION_END_
{
  char name[PATH_MAX];
  FILE* file;

  snprintf(name, PATH_MAX, "%s.%s", output_file_prefix, output_file_suffix);
  file = fopen(name, "a");
  if(file == NULL)
    ERROR("Cannot create output file \'%s\'", name);
  return file;
}
