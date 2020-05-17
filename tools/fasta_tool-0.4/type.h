#ifndef __TYPE__H__
#define __TYPE__H__

typedef enum model_t
{
  MODEL_SPLIT,
  MODEL_ID,
  MODEL_CHECKSUM,
  MODEL_LENGTH,
  MODEL_GET,
  MODEL_UNKNOWN
} model_t;

typedef enum boolean_t
{
  FALSE = 0,
  TRUE  = 1
} boolean_t;

#define MAX_ROW_SIZE 1024
typedef char row_t[MAX_ROW_SIZE+1];

#endif
