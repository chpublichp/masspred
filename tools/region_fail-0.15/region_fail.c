#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_OUTPUT_FILE_PREFIX           "rf_fail_out"
#define DEFAULT_OUTPUT_FILE_NAME_SQL_SUFFIX  "sql"
#define DEFAULT_OUTPUT_FILE_NAME_LOAD_SUFFIX "load"
#define DEFAULT_PROTEIN_ID                   ""
#define DEFAULT_PROTEIN_REFERENCE            ""
#define DEFAULT_PROTEIN_FILE_NAME            ""

typedef enum boolean_t
{
  FALSE = 0,
  TRUE  = 1
} boolean_t;

typedef enum model_t
{
  MODEL_ANCHOR,
  MODEL_DISEMBL,
  MODEL_DISOPRED,
  MODEL_ISUNSTRUCT,
  MODEL_IUPRED_LONG,
  MODEL_IUPRED_SHORT,
  MODEL_OND,
  MODEL_PREDISORDER,
  MODEL_RONN,
  MODEL_VSL2,
  MODEL_UNKNOWN
} model_t;

#define MAX_ROW_SIZE 1024
typedef char row_t[MAX_ROW_SIZE+1];

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

void dump(FILE* output_sql, FILE* output_load, char* name, char* protein_id, char* protein_reference, char* protein_file_name)
{
  if(output_sql != NULL)
  {
    fprintf
    (
      output_sql,
      "INSERT INTO region_fail(protein_id, protein_reference, protein_file_name, type) VALUES(\'%s\', \'%s\', \'%s\', \'%s\');\n",
      protein_id,
      protein_reference,
      protein_file_name,
      name
    );
    fflush(output_sql);
  }
  fprintf
  (
    output_load,
    "%s\t%s\t%s\t%s\n",
    protein_id,
    protein_reference,
    protein_file_name,
    name
  );
  fflush(output_load);
}

void usage(char* name)
{
  fprintf
  (
    stderr,
    "Usage: %s [-h] -m model [-s] [-o output_file_prefix] [-p protein_id] [-r protein_reference] [-f protein_file_name]\n"
    "  -h\tHelp\n"
    "  -m\tModel\n"
    "\t\'a\'  for anchor format\n"
    "\t\'d\'  for disopred format\n"
    "\t\'e\'  for disembl format\n"
    "\t\'il\' for iupred long format\n"
    "\t\'is\' for iupred short format\n"
    "\t\'o\'  for ond format\n"
    "\t\'p\'  for predisorder format\n"
    "\t\'r\'  for ronn format\n"
    "\t\'u\'  for isunstruct format\n"
    "\t\'v\'  for vsl2 format\n"
    "  -s\tGenerate SQL\n"
    "  -o\tOutput file prefix (default \'%s\')\n"
    "  -p\tProtein ID (default \'%s\')\n"
    "  -r\tProtein reference (default \'%s\')\n"
    "  -f\tProtein file name (default \'%s\')\n",
    name,
    DEFAULT_OUTPUT_FILE_PREFIX,
    DEFAULT_PROTEIN_ID,
    DEFAULT_PROTEIN_REFERENCE,
    DEFAULT_PROTEIN_FILE_NAME
  );
  exit(EXIT_FAILURE);
}

int main(int arguments_number, char* arguments_values[])
{
  int option;
  model_t model;
  boolean_t generate_sql;
  char* output_file_prefix;
  char* protein_id;
  char* protein_reference;
  char* protein_file_name;
  char* input_file_name;
  FILE* output_sql;
  FILE* output_load;

  model = MODEL_UNKNOWN;
  generate_sql = FALSE;
  output_file_prefix = DEFAULT_OUTPUT_FILE_PREFIX;
  protein_id = DEFAULT_PROTEIN_ID;
  protein_reference = DEFAULT_PROTEIN_REFERENCE;
  protein_file_name = DEFAULT_PROTEIN_FILE_NAME;
  opterr = 0;
  while(TRUE)
  {
    option = getopt(arguments_number, arguments_values, "hm:so:p:r:f:");
    if(option == -1)
      break;
    switch(option)
    {
      case 'h':
        usage(arguments_values[0]);
        break;
      case 'm':
        switch(optarg[0])
        {
          case 'a':
            model = MODEL_ANCHOR;
            break;
          case 'd':
            model = MODEL_DISOPRED;
            break;
          case 'e':
            model = MODEL_DISEMBL;
            break;
          case 'i':
            switch(optarg[1])
            {
              case 'l':
                model = MODEL_IUPRED_LONG;
                break;
              case 's':
                model = MODEL_IUPRED_SHORT;
                break;
            }
            break;
          case 'o':
            model = MODEL_OND;
            break;
          case 'p':
            model = MODEL_PREDISORDER;
            break;
          case 'r':
            model = MODEL_RONN;
            break;
          case 'u':
            model = MODEL_ISUNSTRUCT;
            break;
          case 'v':
            model = MODEL_VSL2;
            break;
        }
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
  if(optind != arguments_number)
    usage(arguments_values[0]);

  if(model == MODEL_UNKNOWN)
    usage(arguments_values[0]);
  if(generate_sql == TRUE)
    output_sql = open_sql_file(output_file_prefix);
  else
    output_sql = NULL;
  output_load = open_load_file(output_file_prefix);
  switch(model)
  {
    case MODEL_ANCHOR:
      dump(output_sql, output_load, "ANCHOR", protein_id, protein_reference, protein_file_name);
      break;
    case MODEL_DISEMBL:
      dump(output_sql, output_load, "DisEMBL", protein_id, protein_reference, protein_file_name);
      break;
    case MODEL_DISOPRED:
      dump(output_sql, output_load, "DISOPRED2", protein_id, protein_reference, protein_file_name);
      break;
    case MODEL_ISUNSTRUCT:
      dump(output_sql, output_load, "IsUnstruct", protein_id, protein_reference, protein_file_name);
      break;
    case MODEL_IUPRED_LONG:
      dump(output_sql, output_load, "IUPred-L", protein_id, protein_reference, protein_file_name);
      break;
    case MODEL_IUPRED_SHORT:
      dump(output_sql, output_load, "IUPred-S", protein_id, protein_reference, protein_file_name);
      break;
    case MODEL_OND:
      dump(output_sql, output_load, "OnDCRF", protein_id, protein_reference, protein_file_name);
      break;
    case MODEL_PREDISORDER:
      dump(output_sql, output_load, "PreDisorder", protein_id, protein_reference, protein_file_name);
      break;
    case MODEL_RONN:
      dump(output_sql, output_load, "RONN", protein_id, protein_reference, protein_file_name);
      break;
    case MODEL_VSL2:
      dump(output_sql, output_load, "VSL2b", protein_id, protein_reference, protein_file_name);
      break;
  }
  if(output_sql != NULL)
    fclose(output_sql);
  fclose(output_load);
  return EXIT_SUCCESS;
}
