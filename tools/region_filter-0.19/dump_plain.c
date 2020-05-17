#include "main.h"

_FUNCTION_DECLARATION_BEGIN_
void dump_plain(profile_t* profile, char* name, int start, int end, char* order)
_FUNCTION_DECLARATION_END_
{
  if(profile->output_sql != NULL)
  {
    fprintf
    (
      profile->output_sql,
      "INSERT INTO region(protein_id, protein_reference, protein_file_name, begin, end, order, type) VALUES(\'%s\', \'%s\', \'%s\', \'%d\', \'%d\', \'%s\', \'%s\');\n",
      profile->protein_id,
      profile->protein_reference,
      profile->protein_file_name,
      start,
      end,
      order,
      name
    );
    fflush(profile->output_sql);
  }
  fprintf
  (
    profile->output_load,
    "%s\t%s\t%s\t%d\t%d\t%s\t%s\n",
    profile->protein_id,
    profile->protein_reference,
    profile->protein_file_name,
    start,
    end,
    order,
    name
  );
  fflush(profile->output_load);
}
