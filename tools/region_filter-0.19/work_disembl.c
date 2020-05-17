#include "main.h"

_FUNCTION_DECLARATION_BEGIN_
void work_disembl(profile_t* profile, int position)
_FUNCTION_DECLARATION_END_
{
  char* name;
  float treshold;
  row_t row;
  int row_number;
  char aa;
  float probability[3];
  region_t region;
  int region_start;
  int region_end;

  switch(position)
  {
    case 1:
      name = "DisEMBL_Loops/coils";
      treshold = 0.43;
      break;
    case 2:
      name = "DisEMBL_Remark-465";
      treshold = 0.5;
      break;
    case 3:
      name = "DisEMBL_Hot-loops";
      treshold = 0.086;
      break;
    default:
      return;
  }
  region = REGION_UNKNOWN;
  row_number = 1;
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if(sscanf(row, " %c %f %f %f %*s", &aa, &probability[0], &probability[1], &probability[2]) == 4)
    {
      if(profile->numeric == TRUE)
        if(probability[position-1] <= treshold)
          dump_numeric_o(profile, name, row_number, aa, probability[position-1]);
        else
          dump_numeric_d(profile, name, row_number, aa, probability[position-1]);
      else
      {
        if(probability[position-1] <= treshold)
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
