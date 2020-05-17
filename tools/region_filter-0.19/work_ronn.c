#include "main.h"

_FUNCTION_DECLARATION_BEGIN_
void work_ronn(profile_t* profile)
_FUNCTION_DECLARATION_END_
{
  char* name;
  row_t row;
  int row_number;
  char aa;
  float probability;
  region_t region;
  int region_start;
  int region_end;

  name = "RONN";
  region = REGION_UNKNOWN;
  row_number = 1;
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if(sscanf(row, " %c %f %*s", &aa, &probability) == 2)
    {
      if(profile->numeric == TRUE)
        if(probability <= 0.5)
          dump_numeric_o(profile, name, row_number, aa, probability);
        else
          dump_numeric_d(profile, name, row_number, aa, probability);
      else
      {
        if(probability <= 0.5)
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
      row_number++;
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
