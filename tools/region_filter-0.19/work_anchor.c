#include "main.h"

_FUNCTION_DECLARATION_BEGIN_
void work_anchor(profile_t* profile)
_FUNCTION_DECLARATION_END_
{
  char* name;
  row_t row;
  int row_number;
  char aa;
  float probability;
  int status;
  region_t region;
  int region_start;
  int region_end;

  name = "ANCHOR";
  region = REGION_UNKNOWN;
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if(sscanf(row, " %d %c %f %d %*s", &row_number, &aa, &probability, &status) == 4)
      if(profile->numeric == TRUE)
        if(status == 0)
          dump_numeric_o(profile, name, row_number, aa, probability);
        else
          dump_numeric_d(profile, name, row_number, aa, probability);
      else
      {
        if(status == 0)
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
