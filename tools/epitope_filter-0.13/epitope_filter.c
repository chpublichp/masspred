#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_OUTPUT_FILE_PREFIX           "ef_out"
#define DEFAULT_OUTPUT_FILE_NAME_SQL_SUFFIX  "sql"
#define DEFAULT_OUTPUT_FILE_NAME_LOAD_SUFFIX "load"
#define DEFAULT_ALLELE                       ""
#define DEFAULT_LENGTH                       ""
#define DEFAULT_PROTEIN_ID                   ""
#define DEFAULT_PROTEIN_REFERENCE            ""
#define DEFAULT_PROTEIN_FILE_NAME            ""
#define DEFAULT_INPUT_FILE_NAME              "-"

typedef enum boolean_t
{
  FALSE = 0,
  TRUE  = 1
} boolean_t;

#define STRING_MAX_LENGTH (64+1)
typedef char string_t[STRING_MAX_LENGTH];

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

typedef struct profile_t
{
  boolean_t numeric;
  FILE*     input;
  FILE*     output_sql;
  FILE*     output_load;
  char*     allele;
  char*     length;
  char*     protein_id;
  char*     protein_reference;
  char*     protein_file_name;
} profile_t;

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
  profile_t* profile,
  char* name,
  int position,
  char* epitope,
  int pos,
  char* core,
  float aff_1,
  float aff_2,
  float rank,
  char* binding
)
{
  string_t pos_string;
  string_t rank_string;
  string_t binding_string_sql;
  char* table;
  string_t binding_string_load;

  if(pos < 0)
    snprintf(pos_string, STRING_MAX_LENGTH, "NULL");
  else
    snprintf(pos_string, STRING_MAX_LENGTH, "%d", pos);
  if(rank < 0.0)
    snprintf(rank_string, STRING_MAX_LENGTH, "NULL");
  else
    snprintf(rank_string, STRING_MAX_LENGTH, "%0.2f", rank);

  if(profile->output_sql != NULL)
  {
    if(binding == NULL)
      snprintf(binding_string_sql, STRING_MAX_LENGTH, "NULL");
    else
      snprintf(binding_string_sql, STRING_MAX_LENGTH, "\'%s\'", binding);
    if(profile->numeric == TRUE)
      table = "epitope_numeric";
    else
      table = "epitope";
    fprintf
    (
      profile->output_sql,
      "INSERT INTO %s(protein_id, protein_reference, protein_file_name, position, epitope, pos, core, aff_log, aff, rank, binding, type, allele, length) VALUES(\'%s\', \'%s\', \'%s\', \'%d\', \'%s\', %s, \'%s\', \'%0.3f\', \'%0.2f\', %s, %s, \'%s\', \'%s\', \'%s\');\n",
      table,
      profile->protein_id,
      profile->protein_reference,
      profile->protein_file_name,
      position,
      epitope,
      pos_string,
      core,
      aff_1,
      aff_2,
      rank_string,
      binding_string_sql,
      name,
      profile->allele,
      profile->length
    );
    fflush(profile->output_sql);
  }
  if(binding == NULL)
    snprintf(binding_string_load, STRING_MAX_LENGTH, "NULL");
  else
    snprintf(binding_string_load, STRING_MAX_LENGTH, "%s", binding);
  fprintf
  (
    profile->output_load,
    "%s\t%s\t%s\t%d\t%s\t%s\t%s\t%0.3f\t%0.2f\t%s\t%s\t%s\t%s\t%s\n",
    profile->protein_id,
    profile->protein_reference,
    profile->protein_file_name,
    position,
    epitope,
    pos_string,
    core,
    aff_1,
    aff_2,
    rank_string,
    binding_string_load,
    name,
    profile->allele,
    profile->length
  );
  fflush(profile->output_load);
}

void work_netmhc30c(profile_t* profile)
{
  char* name;
  row_t row;
  int row_number;
  string_t epitope;
  float aff_1;
  float aff_2;
  string_t bind_place;
  string_t bind;
  string_t identify;
  string_t hla;

  name = "netmhc-3.0c";
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if
    (
      sscanf
      (
        row,
        " %d %64[^ \t] %f %f%11[ a-zA-Z] %64[^ \t] %64s",
        &row_number,
        epitope,
        &aff_1,
        &aff_2,
        bind_place,
        identify,
        hla
      ) == 7
    )
    {
      if(sscanf(bind_place, "%s", bind) != 1)
        snprintf(bind, STRING_MAX_LENGTH, "");
      if(strcmp(bind, "SB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          -1.0,
          "SB"
        );
      else if(strcmp(bind, "WB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          -1.0,
          "WB"
        );
      else if(profile->numeric == TRUE)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          -1.0,
          NULL
        );
    }
    else if
    (
      sscanf
      (
        row,
        " %d %64[^ \t] %f%11[ a-zA-Z] %64[^ \t] %64s",
        &row_number,
        epitope,
        &aff_1,
        bind_place,
        identify,
        hla
      ) == 6
    )
    {
      if(sscanf(bind_place, "%s", bind) != 1)
        snprintf(bind, STRING_MAX_LENGTH, "");
      if(strcmp(bind, "SB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          -1.0,
          -1.0,
          "SB"
        );
      else if(strcmp(bind, "WB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          -1.0,
          -1.0,
          "WB"
        );
      else if(profile->numeric == TRUE)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          -1.0,
          -1.0,
          NULL
        );
    }
}

void work_netmhc34a(profile_t* profile)
{
  char* name;
  row_t row;
  int row_number;
  string_t epitope;
  float aff_1;
  float aff_2;
  string_t bind_place;
  string_t bind;
  string_t identify;
  string_t hla;

  name = "netmhc-3.4a";
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if
    (
      sscanf
      (
        row,
        " %d %64[^ \t] %f %f%11[ a-zA-Z] %64[^ \t] %64s",
        &row_number,
        epitope,
        &aff_1,
        &aff_2,
        bind_place,
        identify,
        hla
      ) == 7
    )
    {
      if(sscanf(bind_place, "%s", bind) != 1)
        snprintf(bind, STRING_MAX_LENGTH, "");
      if(strcmp(bind, "SB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          -1.0,
          "SB"
        );
      else if(strcmp(bind, "WB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          -1.0,
          "WB"
        );
      else if(profile->numeric == TRUE)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          -1.0,
          NULL
        );
    }
}

void work_netmhcii22(profile_t* profile)
{
  char* name;
  row_t row;
  string_t hla;
  int row_number;
  string_t epitope;
  string_t core;
  float aff_1;
  float aff_2;
  string_t bind_place;
  string_t bind;
  float rank;
  string_t identify;

  name = "netmhcii-2.2";
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if
    (
      sscanf
      (
        row,
        " %64[^ \t] %d %64[^ \t] %64[^ \t] %f %f%11[ a-zA-Z] %f %64s",
        hla,
        &row_number,
        epitope,
        core,
        &aff_1,
        &aff_2,
        bind_place,
        &rank,
        identify
      ) == 9
    )
    {
      if(sscanf(bind_place, "%s", bind) != 1)
        snprintf(bind, STRING_MAX_LENGTH, "");
      if(strcmp(bind, "SB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          core,
          aff_1,
          aff_2,
          rank,
          "SB"
        );
      else if(strcmp(bind, "WB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          core,
          aff_1,
          aff_2,
          rank,
          "WB"
        );
      else if(profile->numeric == TRUE)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          core,
          aff_1,
          aff_2,
          rank,
          NULL
        );
    }
}

void work_netmhcpan20c(profile_t* profile)
{
  char* name;
  row_t row;
  int row_number;
  string_t hla;
  string_t epitope;
  string_t identify;
  float aff_1;
  float aff_2;
  string_t bind_place;
  string_t bind;

  name = "netmhcpan-2.0c";
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if
    (
      sscanf
      (
        row,
        " %d %64[^ \t] %64[^ \t] %64[^ \t] %f %f%64[ <=a-zA-Z\n]",
        &row_number,
        hla,
        epitope,
        identify,
        &aff_1,
        &aff_2,
        bind_place
      ) == 7
    )
    {
      if(sscanf(bind_place, " <= %s", bind) != 1)
        snprintf(bind, STRING_MAX_LENGTH, "");
      if(strcmp(bind, "SB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          -1.0,
          "SB"
        );
      else if(strcmp(bind, "WB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          -1.0,
          "WB"
        );
      else if(profile->numeric == TRUE)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          -1.0,
          NULL
        );
    }
}

void work_netmhcpan24a(profile_t* profile)
{
  char* name;
  row_t row;
  int row_number;
  string_t hla;
  string_t epitope;
  string_t identify;
  float aff_1;
  float aff_2;
  float rank;
  string_t bind_place;
  string_t bind;

  name = "netmhcpan-2.4a";
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if
    (
      sscanf
      (
        row,
        " %d %64[^ \t] %64[^ \t] %64[^ \t] %f %f %f%64[ <=a-zA-Z\n]",
        &row_number,
        hla,
        epitope,
        identify,
        &aff_1,
        &aff_2,
        &rank,
        bind_place
      ) == 8
    )
    {
      if(sscanf(bind_place, " <= %s", bind) != 1)
        snprintf(bind, STRING_MAX_LENGTH, "");
      if(strcmp(bind, "SB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          rank,
          "SB"
        );
      else if(strcmp(bind, "WB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          rank,
          "WB"
        );
      else if(profile->numeric == TRUE)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          rank,
          NULL
        );
    }
}

void work_netmhcpan28a(profile_t* profile)
{
  char* name;
  row_t row;
  int row_number;
  string_t hla;
  string_t epitope;
  string_t identify;
  float aff_1;
  float aff_2;
  float rank;
  string_t bind_place;
  string_t bind;

  name = "netmhcpan-2.8a";
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if
    (
      sscanf
      (
        row,
        " %d %64[^ \t] %64[^ \t] %64[^ \t] %f %f %f%64[ <=a-zA-Z\n]",
        &row_number,
        hla,
        epitope,
        identify,
        &aff_1,
        &aff_2,
        &rank,
        bind_place
      ) == 8
    )
    {
      if(sscanf(bind_place, " <= %s", bind) != 1)
        snprintf(bind, STRING_MAX_LENGTH, "");
      if(strcmp(bind, "SB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          rank,
          "SB"
        );
      else if(strcmp(bind, "WB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          rank,
          "WB"
        );
      else if(profile->numeric == TRUE)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          -1,
          "",
          aff_1,
          aff_2,
          rank,
          NULL
        );
      }
}

void work_netmhciipan10b(profile_t* profile)
{
  char* name;
  row_t row;
  int row_number;
  string_t hla;
  string_t epitope;
  string_t identify;
  int pos;
  string_t core;
  float aff_1;
  float aff_2;
  string_t bind_place;
  string_t bind;

  name = "netmhciipan-1.0b";
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if
    (
      sscanf
      (
        row,
        " %d %64[^ \t] %64[^ \t] %64[^ \t] %d %64[^ \t] %f %f%64[ <=a-zA-Z\n]",
        &row_number,
        hla,
        epitope,
        identify,
        &pos,
        core,
        &aff_1,
        &aff_2,
        bind_place
      ) == 9
    )
    {
      if(sscanf(bind_place, " <= %s", bind) != 1)
        snprintf(bind, STRING_MAX_LENGTH, "");
      if(strcmp(bind, "SB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          pos,
          core,
          aff_1,
          aff_2,
          -1.0,
          "SB"
        );
      else if(strcmp(bind, "WB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          pos,
          core,
          aff_1,
          aff_2,
          -1.0,
          "WB"
        );
      else if(profile->numeric == TRUE)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          pos,
          core,
          aff_1,
          aff_2,
          -1.0,
          NULL
        );
    }
}

void work_netmhciipan20b(profile_t* profile)
{
  char* name;
  row_t row;
  int row_number;
  string_t hla;
  string_t epitope;
  string_t identify;
  int pos;
  string_t core;
  float aff_1;
  float aff_2;
  float rank;
  string_t bind_place;
  string_t bind;

  name = "netmhciipan-2.0b";
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if
    (
      sscanf
      (
        row,
        " %d %64[^ \t] %64[^ \t] %64[^ \t] %d %64[^ \t] %f %f %f%64[ <=a-zA-Z\n]",
        &row_number,
        hla,
        epitope,
        identify,
        &pos,
        core,
        &aff_1,
        &aff_2,
        &rank,
        bind_place
      ) == 10
    )
    {
      if(sscanf(bind_place, " <= %s", bind) != 1)
        snprintf(bind, STRING_MAX_LENGTH, "");
      if(strcmp(bind, "SB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          pos,
          core,
          aff_1,
          aff_2,
          rank,
          "SB"
        );
      else if(strcmp(bind, "WB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          pos,
          core,
          aff_1,
          aff_2,
          rank,
          "WB"
        );
      else if(profile->numeric == TRUE)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          pos,
          core,
          aff_1,
          aff_2,
          rank,
          NULL
        );
    }
}

void work_netmhciipan30c(profile_t* profile)
{
  char* name;
  row_t row;
  int row_number;
  string_t hla;
  string_t epitope;
  string_t identify;
  int pos;
  string_t core;
  float aff_1;
  float aff_2;
  float rank;
  string_t bind_place;
  string_t bind;

  name = "netmhciipan-3.0c";
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if
    (
      sscanf
      (
        row,
        " %d %64[^ \t] %64[^ \t] %64[^ \t] %d %64[^ \t] %f %f %f%64[ <=a-zA-Z\n]",
        &row_number,
        hla,
        epitope,
        identify,
        &pos,
        core,
        &aff_1,
        &aff_2,
        &rank,
        bind_place
      ) == 10
    )
    {
      if(sscanf(bind_place, " <= %s", bind) != 1)
        snprintf(bind, STRING_MAX_LENGTH, "");
      if(strcmp(bind, "SB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          pos,
          core,
          aff_1,
          aff_2,
          rank,
          "SB"
        );
      else if(strcmp(bind, "WB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          pos,
          core,
          aff_1,
          aff_2,
          rank,
          "WB"
        );
      else if(profile->numeric == TRUE)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          pos,
          core,
          aff_1,
          aff_2,
          rank,
          NULL
        );
    }
}

void work_netmhciipan31a(profile_t* profile)
{
  char* name;
  row_t row;
  int row_number;
  string_t hla;
  string_t epitope;
  string_t identify;
  int pos;
  string_t core;
  float core_rel;
  float aff_1;
  float aff_2;
  float rank;
  float exp_bind;
  string_t bind_place;
  string_t bind;

  name = "netmhciipan-3.1a";
  while(fgets(row, MAX_ROW_SIZE, profile->input) != NULL)
    if
    (
      sscanf
      (
        row,
        " %d %64[^ \t] %64[^ \t] %64[^ \t] %d %64[^ \t] %f %f %f %f %f%64[ <=a-zA-Z\n]",
        &row_number,
        hla,
        epitope,
        identify,
        &pos,
        core,
        &core_rel,
        &aff_1,
        &aff_2,
        &rank,
        &exp_bind,
        bind_place
      ) == 12
    )
    {
      if(sscanf(bind_place, " <= %s", bind) != 1)
        snprintf(bind, STRING_MAX_LENGTH, "");
      if(strcmp(bind, "SB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          pos,
          core,
          aff_1,
          aff_2,
          rank,
          "SB"
        );
      else if(strcmp(bind, "WB") == 0)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          pos,
          core,
          aff_1,
          aff_2,
          rank,
          "WB"
        );
      else if(profile->numeric == TRUE)
        dump
        (
          profile,
          name,
          row_number+1,
          epitope,
          pos,
          core,
          aff_1,
          aff_2,
          rank,
          NULL
        );
    }
}

void usage(char* name)
{
  fprintf
  (
    stderr,
    "Usage: %s [-h] -m model [-s] [-o output_file_prefix] [-p protein_id] [-r protein_reference] [-f protein_file_name] [input_file]\n"
    "  -h\t\tHelp\n"
    "  -m\t\tModel:\n"
    "\t\'1-3.0c\' for netMHC-3.0c\n"
    "\t\'2-2.2\' for netMHCII-2.2\n"
    "\t\'pan_1-2.0c\' for netMHCpan-2.0c\n"
    "\t\'pan_1-2.4a\' for netMHCpan-2.4a\n"
    "\t\'pan_1-2.8a\' for netMHCpan-2.8a\n"
    "\t\'pan_2-1.0b\' for netMHCIIpan-1.0b\n"
    "\t\'pan_2-2.0b\' for netMHCIIpan-2.0b\n"
    "\t\'pan_2-3.0c\' for netMHCIIpan-3.0c\n"
    "\t\'pan_2-3.1a\' for netMHCIIpan-3.1a\n"
    "  -s\t\tGenerate SQL\n"
    "  -n\t\tGenerate numeric format\n"
    "  -o\t\tOutput file prefix (default \'%s\')\n"
    "  -a\t\tAllele (default \'%s\')\n"
    "  -l\t\tLenth (default \'%s\')\n"
    "  -p\t\tProtein ID (default \'%s\')\n"
    "  -r\t\tProtein reference (default \'%s\')\n"
    "  -f\t\tProtein file name (default \'%s\')\n"
    "  input_file\tInput file (default \'%s\' aka stdin)\n",
    name,
    DEFAULT_OUTPUT_FILE_PREFIX,
    DEFAULT_ALLELE,
    DEFAULT_LENGTH,
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
  model_t model;
  boolean_t generate_sql;
  char* output_file_prefix;
  char* input_file_name;
  profile_t profile;

  model = MODEL_UNKNOWN;
  generate_sql = FALSE;
  profile.numeric = FALSE;
  output_file_prefix = DEFAULT_OUTPUT_FILE_PREFIX;
  profile.allele = DEFAULT_ALLELE;
  profile.length = DEFAULT_LENGTH;
  profile.protein_id = DEFAULT_PROTEIN_ID;
  profile.protein_reference = DEFAULT_PROTEIN_REFERENCE;
  profile.protein_file_name = DEFAULT_PROTEIN_FILE_NAME;
  input_file_name = DEFAULT_INPUT_FILE_NAME;
  opterr = 0;
  while(TRUE)
  {
    option = getopt(arguments_number, arguments_values, "hm:sno:a:l:p:r:f:");
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
          model = MODEL_NETMHCIIPAN31A;
        break;
      case 's':
        generate_sql = TRUE;
        break;
      case 'n':
        profile.numeric = TRUE;
        break;
      case 'o':
        output_file_prefix = optarg;
        break;
      case 'a':
        profile.allele = optarg;
        break;
      case 'l':
        profile.length = optarg;
        break;
      case 'p':
        profile.protein_id = optarg;
        break;
      case 'r':
        profile.protein_reference = optarg;
        break;
      case 'f':
        profile.protein_file_name = optarg;
        break;
      default:
        usage(arguments_values[0]);
    }
  }
  if(optind == arguments_number-1)
    input_file_name = arguments_values[optind];
  else if(optind != arguments_number)
    usage(arguments_values[0]);

  if(model == MODEL_UNKNOWN)
    usage(arguments_values[0]);
  if(strcmp(input_file_name, "-") == 0)
    profile.input = stdin;
  else
  {
    profile.input = fopen(input_file_name, "r");
    if(profile.input == NULL)
      ERROR("Cannot open input file \'%s\'", input_file_name);
  }
  if(generate_sql == TRUE)
    profile.output_sql = open_sql_file(output_file_prefix);
  else
    profile.output_sql = NULL;
  profile.output_load = open_load_file(output_file_prefix);
  switch(model)
  {
    case MODEL_NETMHC30C:
      work_netmhc30c(&profile);
      break;
    case MODEL_NETMHC34A:
      work_netmhc34a(&profile);
      break;
    case MODEL_NETMHCII22:
      work_netmhcii22(&profile);
      break;
    case MODEL_NETMHCPAN20C:
      work_netmhcpan20c(&profile);
      break;
    case MODEL_NETMHCPAN24A:
      work_netmhcpan24a(&profile);
      break;
    case MODEL_NETMHCPAN28A:
      work_netmhcpan28a(&profile);
      break;
    case MODEL_NETMHCIIPAN10B:
      work_netmhciipan10b(&profile);
      break;
    case MODEL_NETMHCIIPAN20B:
      work_netmhciipan20b(&profile);
      break;
    case MODEL_NETMHCIIPAN30C:
      work_netmhciipan30c(&profile);
      break;
    case MODEL_NETMHCIIPAN31A:
      work_netmhciipan31a(&profile);
      break;
  }
  fclose(profile.input);
  if(profile.output_sql != NULL)
    fclose(profile.output_sql);
  fclose(profile.output_load);
  return EXIT_SUCCESS;
}
