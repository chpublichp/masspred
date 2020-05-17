#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LINE_LEN 1024

int main(void)
{
  unsigned char first_line[LINE_LEN];
  unsigned char line[LINE_LEN];
  int stat[UCHAR_MAX];
  int i;

  if(fgets(first_line, LINE_LEN, stdin) == NULL)
    return 1;
  for(i = 0; first_line[i] != '\n'; i++);
  first_line[i] = '\0';
  for(i = 0; i < UCHAR_MAX; i++)
    stat[i] = 0;
  while(fgets(line, LINE_LEN, stdin) != NULL)
    for(i = 0; line[i] != '\0'; i++)
      stat[line[i]]++;

  printf
  (
    (
      ":name=\"%s\"\n"
      ":position=\"%s\"\n"
      ":db=\"%s\"\n"
      ":id=\"%s\"\n"
      ":reference_db=\"%s\"\n"
      ":reference=\"%s\"\n"
      ":first_line=\"%s\"\n"
      "\n"
      "A: %d\n"
      "B: %d\n"
      "C: %d\n"
      "D: %d\n"
      "E: %d\n"
      "F: %d\n"
      "G: %d\n"
      "H: %d\n"
      "I: %d\n"
      "J: %d\n"
      "K: %d\n"
      "L: %d\n"
      "M: %d\n"
      "N: %d\n"
      "O: %d\n"
      "P: %d\n"
      "Q: %d\n"
      "R: %d\n"
      "S: %d\n"
      "T: %d\n"
      "U: %d\n"
      "V: %d\n"
      "W: %d\n"
      "Y: %d\n"
      "Z: %d\n"
      "X: %d\n"
      "*: %d\n"
      "-: %d\n"
    ),
    getenv("MASSPRED_FILE_NAME"),
    getenv("MASSPRED_INPUT_POSITION"),
    getenv("MASSPRED_FASTA_DB"),
    getenv("MASSPRED_FASTA_ID"),
    getenv("MASSPRED_FASTA_REFERENCE_DB"),
    getenv("MASSPRED_FASTA_REFERENCE"),
    first_line,
    stat['A']+stat['a'],
    stat['B']+stat['b'],
    stat['C']+stat['c'],
    stat['D']+stat['d'],
    stat['E']+stat['e'],
    stat['F']+stat['f'],
    stat['G']+stat['g'],
    stat['H']+stat['h'],
    stat['I']+stat['i'],
    stat['J']+stat['j'],
    stat['K']+stat['k'],
    stat['L']+stat['l'],
    stat['M']+stat['m'],
    stat['N']+stat['n'],
    stat['O']+stat['o'],
    stat['P']+stat['p'],
    stat['Q']+stat['q'],
    stat['R']+stat['r'],
    stat['S']+stat['s'],
    stat['T']+stat['t'],
    stat['U']+stat['u'],
    stat['V']+stat['v'],
    stat['W']+stat['w'],
    stat['Y']+stat['y'],
    stat['Z']+stat['z'],
    stat['X']+stat['x'],
    stat['*'],
    stat['-']
  );
  return 0;
}
