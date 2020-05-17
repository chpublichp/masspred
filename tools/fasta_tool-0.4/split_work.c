#include "main.h"

static FILE* split_new_output_file(char* input_file_name, char* output_directory, int output_file_number)
{
  char input_file_name_copy[PATH_MAX];
  char* slash;
  char* old_input_file_name;
  char* dot;
  char new_output_file_name[PATH_MAX];
  FILE* new_output_file;

  snprintf(input_file_name_copy, PATH_MAX, "%s", input_file_name);
  slash = strrchr(input_file_name_copy, '/');
  if(slash == NULL)
    old_input_file_name = input_file_name_copy;
  else
  {
    slash++;
    old_input_file_name = slash;
  }
  dot = strrchr(old_input_file_name, '.');
  if(dot != NULL)
    *dot = '\0';
  snprintf(new_output_file_name, PATH_MAX, "%s/%s_%d.faa", output_directory, old_input_file_name, output_file_number);
  new_output_file = fopen(new_output_file_name, "w");
  if(new_output_file == NULL)
    ERROR("Cannot create output file \'%s\'", new_output_file_name);
  return new_output_file;
}

_FUNCTION_DECLARATION_BEGIN_
void split_work(FILE* input_file, char* input_file_name, char* output_directory)
_FUNCTION_DECLARATION_END_
{
  FILE* output_file;
  int output_file_number;
  row_t row;

  output_file = NULL;
  output_file_number = 1;
  while(fgets(row, MAX_ROW_SIZE, input_file) != NULL)
  {
    if(row[0] == '>')
    {
      if(output_file != NULL)
      {
        fclose(output_file);
        output_file_number++;
      }
      output_file = split_new_output_file(input_file_name, output_directory, output_file_number);
    }
    if(output_file == NULL)
      ERROR("Bad format in input file");
    fputs(row, output_file);
  }
  if(output_file != NULL)
    fclose(output_file);
}
