#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_OUTPUT_FILE_PREFIX           "ef_fail_out"
#define DEFAULT_OUTPUT_FILE_NAME_SQL_SUFFIX  "sql"
#define DEFAULT_OUTPUT_FILE_NAME_LOAD_SUFFIX "load"
#define DEFAULT_ALLELE                       ""
#define DEFAULT_LENGTH                       ""
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
  MODEL_NETMHC30C,
  MODEL_NETMHC34A,
  MODEL_NETMHCII22,
  MODEL_NETMHCPAN20C,
  MODEL_NETMHCPAN24A,
  MODEL_NETMHCPAN28A,
  MODEL_NETMHCIIPAN10B,
  MODEL_NETMHCIIPAN20B,
  MODEL_NETMHCIIPAN30C,
  MODEL_NETMHCIIPAN31A,
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

void dump
(
  FILE* output_sql,
  FILE* output_load,
  char* name,
  char* allele,
  char* length,
  char* protein_id,
  char* protein_reference,
  char* protein_file_name
)
{
  if(output_sql != NULL)
  {
    fprintf
    (
      output_sql,
      "INSERT INTO epitope_fail(protein_id, protein_reference, protein_file_name, type, allele, length) VALUES(\'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\');\n",
      protein_id,
      protein_reference,
      protein_file_name,
      name,
      allele,
      length
    );
    fflush(output_sql);
  }
  fprintf
  (
    output_load,
    "%s\t%s\t%s\t%s\t%s\t%s\n",
    protein_id,
    protein_reference,
    protein_file_name,
    name,
    allele,
    length
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
    "  -m\tModel:\n"
    "\t\'1-3.0c\' for netMHC-3.0c\n"
    "\t\'1-3.4a\' for netMHC-3.4a\n"
    "\t\'2-2.2\' for netMHCII-2.2\n"
    "\t\'pan_1-2.0c\' for netMHCpan-2.0c\n"
    "\t\'pan_1-2.4a\' for netMHCpan-2.4a\n"
    "\t\'pan_1-2.8a\' for netMHCpan-2.8a\n"
    "\t\'pan_2-1.0b\' for netMHCIIpan-1.0b\n"
    "\t\'pan_2-2.0b\' for netMHCIIpan-2.0b\n"
    "\t\'pan_2-3.0c\' for netMHCIIpan-3.0c\n"
    "\t\'pan_2-3.1a\' for netMHCIIpan-3.1a\n"
    "  -s\tGenerate SQL\n"
    "  -o\tOutput file prefix (default \'%s\')\n"
    "  -a\tAllele (default \'%s\')\n"
    "  -l\tLenth (default \'%s\')\n"
    "  -p\tProtein ID (default \'%s\')\n"
    "  -r\tProtein reference (default \'%s\')\n"
    "  -f\tProtein file name (default \'%s\')\n",
    name,
    DEFAULT_OUTPUT_FILE_PREFIX,
    DEFAULT_ALLELE,
    DEFAULT_LENGTH,
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
  char* allele;
  char* length;
  char* protein_id;
  char* protein_reference;
  char* protein_file_name;
  char* input_file_name;
  FILE* output_sql;
  FILE* output_load;

  model = MODEL_UNKNOWN;
  generate_sql = FALSE;
  output_file_prefix = DEFAULT_OUTPUT_FILE_PREFIX;
  allele = DEFAULT_ALLELE;
  length = DEFAULT_LENGTH;
  protein_id = DEFAULT_PROTEIN_ID;
  protein_reference = DEFAULT_PROTEIN_REFERENCE;
  protein_file_name = DEFAULT_PROTEIN_FILE_NAME;
  opterr = 0;
  while(TRUE)
  {
    option = getopt(arguments_number, arguments_values, "hm:so:a:l:p:r:f:");
    if(option == -1)
      break;
    switch(option)
    {
      case 'h':
        usage(arguments_values[0]);
        break;
      case 'm':
        if(strcasecmp(optarg, "1-3.0c") == 0)
          model = MODEL_NETMHC30C;
        else if(strcasecmp(optarg, "1-3.4a") == 0)
          model = MODEL_NETMHC34A;
        else if(strcasecmp(optarg, "2-2.2") == 0)
          model = MODEL_NETMHCII22;
        else if(strcasecmp(optarg, "pan_1-2.0c") == 0)
          model = MODEL_NETMHCPAN20C;
        else if(strcasecmp(optarg, "pan_1-2.4a") == 0)
          model = MODEL_NETMHCPAN24A;
        else if(strcasecmp(optarg, "pan_1-2.8a") == 0)
          model = MODEL_NETMHCPAN28A;
        else if(strcasecmp(optarg, "pan_2-1.0b") == 0)
          model = MODEL_NETMHCIIPAN10B;
        else if(strcasecmp(optarg, "pan_2-2.0b") == 0)
          model = MODEL_NETMHCIIPAN20B;
        else if(strcasecmp(optarg, "pan_2-3.0c") == 0)
          model = MODEL_NETMHCIIPAN30C;
        else if(strcasecmp(optarg, "pan_2-3.1a") == 0)
          model = MODEL_NETMHCIIPAN30C;
        break;
      case 's':
        generate_sql = TRUE;
        break;
      case 'o':
        output_file_prefix = optarg;
        break;
      case 'a':
        allele = optarg;
        break;
      case 'l':
        length = optarg;
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
    case MODEL_NETMHC30C:
      dump
      (
        output_sql,
        output_load,
        "netmhc-3.0c",
        allele,
        length,
        protein_id,
        protein_reference,
        protein_file_name
      );
      break;
    case MODEL_NETMHC34A:
      dump
      (
        output_sql,
        output_load,
        "netmhc-3.0c",
        allele,
        length,
        protein_id,
        protein_reference,
        protein_file_name
      );
      break;
    case MODEL_NETMHCII22:
      dump
      (
        output_sql,
        output_load,
        "netmhcii-2.2",
        allele,
        length,
        protein_id,
        protein_reference,
        protein_file_name
      );
      break;
    case MODEL_NETMHCPAN20C:
      dump
      (
        output_sql,
        output_load,
        "netmhcpan-2.0c",
        allele,
        length,
        protein_id,
        protein_reference,
        protein_file_name
      );
      break;
    case MODEL_NETMHCPAN24A:
      dump
      (
        output_sql,
        output_load,
        "netmhcpan-2.4a",
        allele,
        length,
        protein_id,
        protein_reference,
        protein_file_name
      );
      break;
    case MODEL_NETMHCPAN28A:
      dump
      (
        output_sql,
        output_load,
        "netmhcpan-2.8a",
        allele,
        length,
        protein_id,
        protein_reference,
        protein_file_name
      );
      break;
    case MODEL_NETMHCIIPAN10B:
      dump
      (
        output_sql,
        output_load,
        "netmhciipan-1.0b",
        allele,
        length,
        protein_id,
        protein_reference,
        protein_file_name
      );
      break;
    case MODEL_NETMHCIIPAN20B:
      dump
      (
        output_sql,
        output_load,
        "netmhciipan-2.0b",
        allele,
        length,
        protein_id,
        protein_reference,
        protein_file_name
      );
      break;
    case MODEL_NETMHCIIPAN30C:
      dump
      (
        output_sql,
        output_load,
        "netmhciipan-3.0c",
        allele,
        length,
        protein_id,
        protein_reference,
        protein_file_name
      );
      break;
    case MODEL_NETMHCIIPAN31A:
      dump
      (
        output_sql,
        output_load,
        "netmhciipan-3.1a",
        allele,
        length,
        protein_id,
        protein_reference,
        protein_file_name
      );
      break;
  }
  if(output_sql != NULL)
    fclose(output_sql);
  fclose(output_load);
  return EXIT_SUCCESS;
}
