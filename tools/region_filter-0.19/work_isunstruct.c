#include "main.h"

#define DUMP_SIZE 32

_FUNCTION_DECLARATION_BEGIN_
void work_isunstruct(profile_t* profile)
_FUNCTION_DECLARATION_END_
{
  char* name;
  row_t row;
  int row_number;
  char aa;
  char status;
  char dump[DUMP_SIZE+1];
  float probability;
  region_t region;
  int region_start;
  int region_end;

  name = "IsUnstruct";
  region = REGION_UNKNOWN;
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if(sscanf(row, " %d %c %c%" STRING(DUMP_SIZE) "[^0-9]%f %*s", &row_number, &aa, &status, dump, &probability) == 5)
      if(profile->numeric == TRUE)
        if(status == 's')
          dump_numeric_o(profile, name, row_number, aa, probability);
        else
          dump_numeric_d(profile, name, row_number, aa, probability);
      else
      {
        if(status == 's')
        {
          if(region == REGION_D)
            dump_plain_d(profile, name, region_start, region_end);
          if(region != REGION_O)
            region_start = row_number;
          region = REGION_O;
        }
        else
        {
          if(region == REGION_O)
            dump_plain_o(profile, name, region_start, region_end);
          if(region != REGION_D)
            region_start = row_number;
          region = REGION_D;
        }
        region_end = row_number;
      }
  if(profile->numeric != TRUE)
    switch(region)
    {
      case REGION_O:
        dump_plain_o(profile, name, region_start, region_end);
        break;
      case REGION_D:
        dump_plain_d(profile, name, region_start, region_end);
        break;
    }
}
