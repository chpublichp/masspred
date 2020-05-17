#include "main.h"

static void usage(char* name)
{
  fprintf
  (
    stderr,
    "Usage: %s [-h] -m model [-s] [-n] [-o output_file_prefix] [-p protein_id] [-r protein_reference] [-f protein_file_name] [input_file]\n"
    "  -h\t\tHelp\n"
    "  -m\t\tModel\n"
    "\t\'a\'  for anchor format\n"
    "\t\'d\'  for disopred format\n"
    "\t\'d1\' for disopred format - svm (only for numeric)\n"
    "\t\'d2\' for disopred format - smooth (only for numeric)\n"
    "\t\'e1\' for disembl format - coils\n"
    "\t\'e2\' for disembl format - rem465\n"
    "\t\'e3\' for disembl format - hotloops\n"
    "\t\'il\' for iupred long format\n"
    "\t\'is\' for iupred short format\n"
    "\t\'o\'  for ond format\n"
    "\t\'p\'  for predisorder format\n"
    "\t\'r\'  for ronn format\n"
    "\t\'u\'  for isunstruct format\n"
    "\t\'v\'  for vsl2 format\n"
    "  -s\t\tGenerate SQL\n"
    "  -n\t\tGenerate numeric format\n"
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
  model_t model;
  boolean_t generate_sql;
  char* output_file_prefix;
  char* input_file_name;
  profile_t profile;

  model = MODEL_UNKNOWN;
  generate_sql = FALSE;
  output_file_prefix = DEFAULT_OUTPUT_FILE_PREFIX;
  profile.numeric = FALSE;
  profile.protein_id = DEFAULT_PROTEIN_ID;
  profile.protein_reference = DEFAULT_PROTEIN_REFERENCE;
  profile.protein_file_name = DEFAULT_PROTEIN_FILE_NAME;
  input_file_name = DEFAULT_INPUT_FILE_NAME;
  opterr = 0;
  while(TRUE)
  {
    option = getopt(arguments_number, arguments_values, "hm:sno:p:r:f:");
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
            switch(optarg[1])
            {
              case '1':
                model = MODEL_DISOPRED_1;
                break;
              case '2':
                model = MODEL_DISOPRED_2;
                break;
            }
            break;
          case 'e':
            switch(optarg[1])
            {
              case '1':
                model = MODEL_DISEMBL_1;
                break;
              case '2':
                model = MODEL_DISEMBL_2;
                break;
              case '3':
                model = MODEL_DISEMBL_3;
                break;
            }
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
      case 'n':
        profile.numeric = TRUE;
        break;
      case 'o':
        output_file_prefix = optarg;
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

  if
  (
    model == MODEL_UNKNOWN ||
    (
      profile.numeric == TRUE &&
      model == MODEL_DISOPRED
    ) ||
    (
      profile.numeric != TRUE &&
      (
        model == MODEL_DISOPRED_1 ||
        model == MODEL_DISOPRED_2
      )
    )
  )
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
    profile.output_sql = open_file(output_file_prefix, DEFAULT_OUTPUT_FILE_NAME_SQL_SUFFIX);
  else
    profile.output_sql = NULL;
  profile.output_load = open_file(output_file_prefix, DEFAULT_OUTPUT_FILE_NAME_LOAD_SUFFIX);
  switch(model)
  {
    case MODEL_ANCHOR:
      work_anchor(&profile);
      break;
    case MODEL_DISEMBL_1:
      work_disembl(&profile, 1);
      break;
    case MODEL_DISEMBL_2:
      work_disembl(&profile, 2);
      break;
    case MODEL_DISEMBL_3:
      work_disembl(&profile, 3);
      break;
    case MODEL_DISOPRED:
      work_disopred(&profile, 0);
      break;
    case MODEL_DISOPRED_1:
      work_disopred(&profile, 1);
      break;
    case MODEL_DISOPRED_2:
      work_disopred(&profile, 2);
      break;
    case MODEL_ISUNSTRUCT:
      work_isunstruct(&profile);
      break;
    case MODEL_IUPRED_LONG:
      work_iupred(&profile, TRUE);
      break;
    case MODEL_IUPRED_SHORT:
      work_iupred(&profile, FALSE);
      break;
    case MODEL_OND:
      work_ond(&profile);
      break;
    case MODEL_PREDISORDER:
      work_predisorder(&profile);
      break;
    case MODEL_RONN:
      work_ronn(&profile);
      break;
    case MODEL_VSL2:
      work_vsl2(&profile);
      break;
  }
  fclose(profile.input);
  if(profile.output_sql != NULL)
    fclose(profile.output_sql);
  fclose(profile.output_load);
  return EXIT_SUCCESS;
}
