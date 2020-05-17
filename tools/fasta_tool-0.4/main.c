#include "main.h"

static void usage(char* name)
{
  fprintf
  (
    stderr,
    "Usage: %s [-h] (-s dir | -i | -c | -l | -g number) [input_file]\n"
    "  -h\t\tHelp\n"
    "  -s\t\tSplit multi fasta format file to dir (default \'%s\')\n"
    "  -i\t\tGet ID from single fasta format file\n"
    "  -c\t\tGet checksum of file name\n"
    "  -l\t\tGet number of proteins in multi fasta format file\n"
    "  -g\t\tGet proteins from multi fasta format file on position number\n"
    "  input_file\tInput file in fasta format (default \'%s\' aka stdin)\n",
    name,
    DEFAULT_SPLIT_OUTPUT_DIRECTORY,
    DEFAULT_INPUT_FILE_NAME
  );
  exit(EXIT_FAILURE);
}

int main(int arguments_number, char* arguments_values[])
{
  model_t model;
  int option;
  char* split_output_directory;
  int get_number;
  char* input_file_name;
  FILE* input_file;

  model = MODEL_UNKNOWN;
  input_file_name = DEFAULT_INPUT_FILE_NAME;
  opterr = 0;
  while(TRUE)
  {
    option = getopt(arguments_number, arguments_values, "hs:iclg:");
    if(option == -1)
      break;
    switch(option)
    {
      case 'h':
        usage(arguments_values[0]);
        break;
      case 's':
        model = MODEL_SPLIT;
        split_output_directory = optarg;
        break;
      case 'i':
        model = MODEL_ID;
        break;
      case 'c':
        model = MODEL_CHECKSUM;
        break;
      case 'l':
        model = MODEL_LENGTH;
        break;
      case 'g':
        model = MODEL_GET;
        get_number = atoi(optarg);
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

  if(model == MODEL_CHECKSUM)
    checksum_work(input_file_name);
  else
  {
    if(strcmp(input_file_name, "-") == 0)
      input_file = stdin;
    else
    {
      input_file = fopen(input_file_name, "r");
      if(input_file == NULL)
        ERROR("Cannot open input file \'%s\'", input_file_name);
    }

    switch(model)
    {
      case MODEL_SPLIT:
        split_work(input_file, input_file_name, split_output_directory);
        break;
      case MODEL_ID:
        id_work(input_file);
        break;
      case MODEL_LENGTH:
        length_work(input_file);
        break;
      case MODEL_GET:
        get_work(input_file, get_number);
        break;
    }
    fclose(input_file);
  }
  return EXIT_SUCCESS;
}
