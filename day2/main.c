#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "strings.c"


int main() {
  FILE* input_file;
  String* line;
  String* numbers;
  u32 part1_answer = 0;
  u32 part2_answer = 0;
  char* input = calloc(256, sizeof(char));
  i32 dial = 50; /* dial starts at 50*/
  i32 p2_dial = 50; /* dial starts at 50*/

  if (NULL == input) {
    puts("Failed to alloc memory");
    exit(-1);
  }
  /*input_file = fopen("test.txt", "r");*/
  input_file = fopen("input.txt", "r");

  if (NULL == input_file) {
    puts("Failed to open file");
    exit(-1);
  }

  while(fgets(input, 255, input_file)) {
    line = cstr_to_str(input, strlen(input));
    if (blank(line)) {
      continue;
    }

  }
  exit(0);
}
