#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "strings.h"
#include <string.h>

u64 LINE_SIZE = 10 * 1000; /* ten kilobytes */

u32 part1_joltage_per_line(String* line);

int main() {
  FILE* input_file;
  String* line;
  u64 part1_answer = 0;
  u64 part2_answer = 0;
  char* input = calloc(LINE_SIZE, sizeof(char));

  if (NULL == input) {
    puts("Failed to alloc memory");
    exit(-1);
  }
  input_file = fopen("sample.txt", "r");

  if (NULL == input_file) {
    puts("Failed to open file");
    exit(-1);
  }
  while(fgets(input, LINE_SIZE - 1, input_file)) {
    line = cstr_to_str_or_die(input, strlen(input));
    if (blank(line)) {
      continue;
    }

    part1_answer += part1_joltage_per_line(line);

    free_str_or_die(line);
  }



  printf("Part 1 answer is %lu\n", part1_answer);
  printf("Part 2 answer is %lu\n", part2_answer);
  free(input);
  exit(0);
}

u32 part1_joltage_per_line(String* line) {
  u32 joltage = 1;

  return joltage;
}
