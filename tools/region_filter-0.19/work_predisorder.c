#include "main.h"

_FUNCTION_DECLARATION_BEGIN_
void work_predisorder(profile_t* profile)
_FUNCTION_DECLARATION_END_
{
  char* name;
  row_t row_aa;
  row_t row_status;
  float probability[MAX_ROW_SIZE];
  int position;
  int row_number;
  region_t region;
  int region_start;
  int region_end;

  if(fgets(row_aa, MAX_ROW_SIZE, profile->input) == NULL)
    return;
  if(fgets(row_status, MAX_ROW_SIZE, profile->input) == NULL)
    return;
  position = 0;
  while(row_status[position] != '\0')
  {
    if(row_status[position] == 'O' || row_status[position] == 'D')
      if(fscanf(profile->input, "%f", &probability[position]) != 1)
        return;
    position++;
  }
  name = "PreDisorder";
  region = REGION_UNKNOWN;
  position = 0;
  row_number = 1;
  while(row_status[position] != '\0')
  {
    if(row_status[position] == 'O' || row_status[position] == 'D')
    {
      if(profile->numeric == TRUE)
        if(row_status[position] == 'O')
          dump_numeric_o(profile, name, row_number, row_aa[position], probability[position]);
        else
          dump_numeric_d(profile, name, row_number, row_aa[position], probability[position]);
      else
      {
        if(row_status[position] == 'O')
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
    position++;
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
