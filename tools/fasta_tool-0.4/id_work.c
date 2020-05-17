#include "main.h"

static char* id_quote(char* input, char* output, int output_size)
{
  int input_position;
  int output_position;

  input_position = 0;
  output_position = 0;
  while(output_position < output_size-1 && input[input_position] != '\0')
  {
    if
    (
      input[input_position] == '\'' ||
      input[input_position] == '\"' ||
      input[input_position] == '$' ||
      input[input_position] == '`' ||
      input[input_position] == '\\'
    )
    {
      if(output_position >= output_size-3)
        break;
      output[output_position] = '\\';
      output_position++;
    }
    if(output_position >= output_size-2)
      break;
    output[output_position] = input[input_position];
    output_position++;
    input_position++;
  }
  output[output_position] = '\0';
  return output;
}

_FUNCTION_DECLARATION_BEGIN_
void id_work(FILE* input_file)
_FUNCTION_DECLARATION_END_
{
  row_t row;
  char* field_1;
  char* field_2;
  char* field_3;
  char* field_4;
  char* rest;
  char* end;
  row_t helper;

  if(fgets(row, MAX_ROW_SIZE, input_file) == NULL)
    ERROR("Empty input file");
  if(row[0] != '>')
    ERROR("Missing \'>\' in first row");

  field_1 = &row[1];
  field_2 = strchr(field_1, '|');
  field_3 = NULL;
  field_4 = NULL;
  rest = NULL;

  end = strchr(field_1, '\r');
  if(end != NULL)
    *end = '\0';
  end = strchr(field_1, '\n');
  if(end != NULL)
    *end = '\0';

  if(field_2 != NULL)
  {
    *field_2 = '\0';
    field_2++;
    field_3 = strchr(field_2, '|');
    if(field_3 != NULL)
    {
      *field_3 = '\0';
      field_3++;
      field_4 = strchr(field_3, '|');
      if(field_4 != NULL)
      {
        *field_4 = '\0';
        field_4++;
        rest = strchr(field_4, '|');
        if(rest != NULL)
        {
          *rest = '\0';
          rest++;
        }
      }
    }
  }

  printf("FASTA_DB=\"%s\"\n", id_quote(field_1, helper, MAX_ROW_SIZE));
  if(field_2 != NULL)
    printf("FASTA_ID=\"%s\"\n", id_quote(field_2, helper, MAX_ROW_SIZE));
  else
    printf("FASTA_ID=\"\"\n");
  if(field_3 != NULL )
    printf("FASTA_REFERENCE_DB=\"%s\"\n", id_quote(field_3, helper, MAX_ROW_SIZE));
  else
    printf("FASTA_REFERENCE_DB=\"\"\n");
  if(field_4 != NULL)
    printf("FASTA_REFERENCE=\"%s\"\n", id_quote(field_4, helper, MAX_ROW_SIZE));
  else
    printf("FASTA_REFERENCE=\"\"\n");
  if(rest != NULL)
    printf("FASTA_REST=\"%s\"\n", id_quote(rest, helper, MAX_ROW_SIZE));
  else
    printf("FASTA_REST=\"\"\n");
}
