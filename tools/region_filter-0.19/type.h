#ifndef __TYPE__H__
#define __TYPE__H__

typedef enum boolean_t
{
  FALSE = 0,
  TRUE  = 1
} boolean_t;

typedef enum model_t
{
  MODEL_ANCHOR,
  MODEL_DISEMBL_1,
  MODEL_DISEMBL_2,
  MODEL_DISEMBL_3,
  MODEL_DISOPRED,
  MODEL_DISOPRED_1,
  MODEL_DISOPRED_2,
  MODEL_ISUNSTRUCT,
  MODEL_IUPRED_LONG,
  MODEL_IUPRED_SHORT,
  MODEL_OND,
  MODEL_PREDISORDER,
  MODEL_RONN,
  MODEL_VSL2,
  MODEL_UNKNOWN
} model_t;

typedef enum region_t
{
  REGION_O,
  REGION_D,
  REGION_UNKNOWN
} region_t;

typedef struct profile_t
{
  boolean_t numeric;
  FILE*     input;
  FILE*     output_sql;
  FILE*     output_load;
  char*     protein_id;
  char*     protein_reference;
  char*     protein_file_name;
} profile_t;

#define MAX_ROW_SIZE 8192
typedef char row_t[MAX_ROW_SIZE+1];

#endif
