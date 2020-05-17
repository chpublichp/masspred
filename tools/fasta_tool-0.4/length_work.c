#include "main.h"

_FUNCTION_DECLARATION_BEGIN_
void length_work(FILE* input_file)
_FUNCTION_DECLARATION_END_
{
  int length;
  row_t row;

  length = 0;
  while(fgets(row, MAX_ROW_SIZE, input_file) != NULL)
  {
    if(row[0] == '>')
      length++;
  }
  printf("FASTA_LENGTH=\"%d\"\n", length);
}
