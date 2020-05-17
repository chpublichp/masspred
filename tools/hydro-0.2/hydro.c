#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_OUTPUT_FILE_PREFIX           "hy_out"
#define DEFAULT_OUTPUT_FILE_NAME_SQL_SUFFIX  "sql"
#define DEFAULT_OUTPUT_FILE_NAME_LOAD_SUFFIX "load"
#define DEFAULT_PROTEIN_ID                   ""
#define DEFAULT_PROTEIN_REFERENCE            ""
#define DEFAULT_PROTEIN_FILE_NAME            ""
#define DEFAULT_INPUT_FILE_NAME              "-"

typedef enum boolean_t
{
  FALSE = 0,
  TRUE  = 1
} boolean_t;

#define MAX_ROW_SIZE 8192
typedef char row_t[MAX_ROW_SIZE+1];

#define INIT_AA_HYDRO 0.0

#define ERROR(format, ...)                               \
do                                                       \
{                                                        \
  fprintf(stderr, "Error: " format "\n", ##__VA_ARGS__); \
  exit(EXIT_FAILURE);                                    \
}                                                        \
while(FALSE)                                             \

FILE* open_sql_file(char* output_file_prefix)
{
  char name[PATH_MAX];
  FILE* file;

  snprintf(name, PATH_MAX, "%s.%s", output_file_prefix, DEFAULT_OUTPUT_FILE_NAME_SQL_SUFFIX);
  file = fopen(name, "a");
  if(file == NULL)
    ERROR("Cannot create output file \'%s\'", name);
  return file;
}

FILE* open_load_file(char* output_file_prefix)
{
  char name[PATH_MAX];
  FILE* file;

  snprintf(name, PATH_MAX, "%s.%s", output_file_prefix, DEFAULT_OUTPUT_FILE_NAME_LOAD_SUFFIX);
  file = fopen(name, "a");
  if(file == NULL)
    ERROR("Cannot create output file \'%s\'", name);
  return file;
}

void dump(FILE* output_sql, FILE* output_load, char* protein_id, char* protein_reference, char* protein_file_name, char aa, int position, float hydro_kd, float hydro_hw)
{
  if(output_sql != NULL)
  {
    fprintf
    (
      output_sql,
      "INSERT INTO hydro(protein_id, protein_reference, protein_file_name, position, aa, hydro_kd, hydro_hw) VALUES(\'%s\', \'%s\', \'%s\', \'%d\', \'%c\', \'%.1f\', \'%.1f\');\n",
      protein_id,
      protein_reference,
      protein_file_name,
      position,
      aa,
      hydro_kd,
      hydro_hw
    );
    fflush(output_sql);
  }
  fprintf
  (
    output_load,
    "%s\t%s\t%s\t%d\t%c\t%.1f\t%.1f\n",
    protein_id,
    protein_reference,
    protein_file_name,
    position,
    aa,
    hydro_kd,
    hydro_hw
  );
  fflush(output_load);
}

float hydro_kd(char code)
{
  static float table[] =
  {
     1.8,  0.0,  2.5, -3.5, -3.5,  2.8, -0.4, -3.2,  4.5,  0.0, -3.9,  3.8,  1.9,
    -3.5,  0.0, -1.6, -3.5, -4.5, -0.8, -0.7,  0.0,  4.2, -0.9,  0.0, -1.3,  0.0
  };

  if(code < 'A' || code > 'Z')
    return INIT_AA_HYDRO;
  return table[code-'A'];
}

float hydro_hw(char code)
{
  static float table[] =
  {
    -0.5,  0.0, -1.0,  3.0,  3.0, -2.5,  0.0, -0.5, -1.8,  0.0,  3.0, -1.8, -1.3,
     0.2,  0.0,  0.0,  0.2,  3.0,  0.3, -0.4,  0.0, -1.5, -3.4,  0.0, -2.3,  0.0
  };

  if(code < 'A' || code > 'Z')
    return INIT_AA_HYDRO;
  return table[code-'A'];
}

void work(FILE* input, FILE* output_sql, FILE* output_load, char* protein_id, char* protein_reference, char* protein_file_name)
{
  row_t row;
  int aa_position;
  int row_position;
  char aa;

  aa_position = 1;
  while(fgets(row, MAX_ROW_SIZE, input) != NULL)
    if(row[0] != '>')
    {
      row_position = 0;
      while(row[row_position] != '\0')
      {
        aa = toupper(row[row_position]);
        row_position++;
        if(aa >= 'A' && aa <= 'Z')
        {
          dump(output_sql, output_load, protein_id, protein_reference, protein_file_name, aa, aa_position, hydro_kd(aa), hydro_hw(aa));
          aa_position++;
        }
      }
    }
}

void usage(char* name)
{
  fprintf
  (
    stderr,
    "Usage: %s [-h] [-s] [-o output_file_prefix] [-p protein_id] [-r protein_reference] [-f protein_file_name] [input_file]\n"
    "  -h\t\tHelp\n"
    "  -s\t\tGenerate SQL\n"
    "  -o\t\tOutput file prefix (default \'%s\')\n"
    "  -p\t\tProtein ID (default \'%s\')\n"
    "  -r\t\tProtein reference (default \'%s\')\n"
    "  -f\t\tProtein file name (default \'%s\')\n"
    "  input_file\tInput file (default \'%s\' aka stdin)\n",
    name,
    DEFAULT_OUTPUT_FILE_PREFIX,
    DEFAULT_PROTEIN_ID,
    DEFAULT_PROTEIN_REFERENCE,
    DEFAULT_PROTEIN_FILE_NAME,
    DEFAULT_INPUT_FILE_NAME
  );
  exit(EXIT_FAILURE);
}

int main(int arguments_number, char* arguments_values[])
{
  int option;
  boolean_t generate_sql;
  char* output_file_prefix;
  char* protein_id;
  char* protein_reference;
  char* protein_file_name;
  char* input_file_name;
  FILE* input;
  FILE* output_sql;
  FILE* output_load;

  generate_sql = FALSE;
  output_file_prefix = DEFAULT_OUTPUT_FILE_PREFIX;
  protein_id = DEFAULT_PROTEIN_ID;
  protein_reference = DEFAULT_PROTEIN_REFERENCE;
  protein_file_name = DEFAULT_PROTEIN_FILE_NAME;
  input_file_name = DEFAULT_INPUT_FILE_NAME;
  opterr = 0;
  while(TRUE)
  {
    option = getopt(arguments_number, arguments_values, "hso:p:r:f:");
    if(option == -1)
      break;
    switch(option)
    {
      case 'h':
        usage(arguments_values[0]);
        break;
      case 's':
        generate_sql = TRUE;
        break;
      case 'o':
        output_file_prefix = optarg;
        break;
      case 'p':
        protein_id = optarg;
        break;
      case 'r':
        protein_reference = optarg;
        break;
      case 'f':
        protein_file_name = optarg;
        break;
      default:
        usage(arguments_values[0]);
    }
  }
  if(optind == arguments_number-1)
    input_file_name = arguments_values[optind];
  else if(optind != arguments_number)
    usage(arguments_values[0]);

  if(strcmp(input_file_name, "-") == 0)
    input = stdin;
  else
  {
    input = fopen(input_file_name, "r");
    if(input == NULL)
      ERROR("Cannot open input file \'%s\'", input_file_name);
  }
  if(generate_sql == TRUE)
    output_sql = open_sql_file(output_file_prefix);
  else
    output_sql = NULL;
  output_load = open_load_file(output_file_prefix);
  work(input, output_sql, output_load, protein_id, protein_reference, protein_file_name);
  fclose(input);
  if(output_sql != NULL)
    fclose(output_sql);
  fclose(output_load);
  return EXIT_SUCCESS;
}
