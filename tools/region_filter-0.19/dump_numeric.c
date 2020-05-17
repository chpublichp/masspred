#include "main.h"

_FUNCTION_DECLARATION_BEGIN_
void dump_numeric(profile_t* profile, char* name, int position, char aa, float value, char* order)
_FUNCTION_DECLARATION_END_
{
  if(profile->output_sql != NULL)
  {
    fprintf
    (
      profile->output_sql,
      "INSERT INTO region_numeric(protein_id, protein_reference, protein_file_name, position, aa, value, order, type) VALUES(\'%s\', \'%s\', \'%s\', \'%d\', \'%c\', \'%f\', \'%s\', \'%s\');\n",
      profile->protein_id,
      profile->protein_reference,
      profile->protein_file_name,
      position,
      aa,
      value,
      order,
      name
    );
    fflush(profile->output_sql);
  }
  fprintf
  (
    profile->output_load,
    "%s\t%s\t%s\t%d\t%c\t%f\t%s\t%s\n",
    profile->protein_id,
    profile->protein_reference,
    profile->protein_file_name,
    position,
    aa,
    value,
    order,
    name
  );
  fflush(profile->output_load);
}
