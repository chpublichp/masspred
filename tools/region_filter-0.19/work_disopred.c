#include "main.h"

_FUNCTION_DECLARATION_BEGIN_
void work_disopred(profile_t* profile, int position)
_FUNCTION_DECLARATION_END_
{
  char* name;
  row_t row;
  int row_number;
  char aa;
  char status;
  float probability[2];
  region_t region;
  int region_start;
  int region_end;


  switch(position)
  {
    case 0:
      name = "DISOPRED2";
      if(profile->numeric == TRUE)
        return;
      break;
    case 1:
      name = "DISOPRED2-SVM";
      if(profile->numeric != TRUE)
        return;
      break;
    case 2:
      name = "DISOPRED2-Smooth";
      if(profile->numeric != TRUE)
        return;
      break;
    default:
      return;
  }
  region = REGION_UNKNOWN;
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if(sscanf(row, " %d %c %c %f %f %*s", &row_number, &aa, &status, &probability[0], &probability[1]) == 5)
      if(profile->numeric == TRUE)
        if(status == '.')
          dump_numeric_o(profile, name, row_number, aa, probability[position-1]);
        else
          dump_numeric_d(profile, name, row_number, aa, probability[position-1]);
      else
      {
        if(status == '.')
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
