#include "main.h"

_FUNCTION_DECLARATION_BEGIN_
void get_work(FILE* input_file, int get_number)
_FUNCTION_DECLARATION_END_
{
  int position;
  boolean_t found;
  row_t row;

  position = 0;
  found = FALSE;
  while(fgets(row, MAX_ROW_SIZE, input_file) != NULL)
    if(row[0] == '>')
    {
      position++;
      if(position == get_number)
      {
        found = TRUE;
        fputs(row, stdout);
        break;
      }
    }
  if(found == TRUE)
  {
    while(fgets(row, MAX_ROW_SIZE, input_file) != NULL)
    {
      if(row[0] == '>')
        break;
      fputs(row, stdout);
    }
  }
}
