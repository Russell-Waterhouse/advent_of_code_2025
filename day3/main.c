#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "strings.h"
#include <string.h>

u64 LINE_SIZE = 10 * 1000; /* ten kilobytes */

u64 part1_joltage_per_line(String* line);
u64 part2_joltage_per_line(String* line);

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
    part2_answer += part2_joltage_per_line(line);

    free_str_or_die(line);
  }



  printf("Part 1 answer is %lu\n", part1_answer);
  printf("Part 2 answer is %lu\n", part2_answer);
  free(input);
  exit(0);
}

u64 part1_joltage_per_line(String* line) {
  Result r = strip_in_place(line);
  if (r != SUCCESS) {
    puts("Failed to strip in place");
    exit(-1);
  }
  String number = *line;
  u64 i, max_idx, max_idx_second_digit;
  char max;
  max = '0';
  max_idx = -1;
  for (i = 0; i < number.size - 1; i++) {
    if(number.str[i] > max) {
      max = number.str[i];
      max_idx = i;
    }
  }

  max = '0';
  for (i = max_idx + 1; i < number.size ; i++) {
    if(number.str[i] > max) {
      max = number.str[i];
      max_idx_second_digit = i;
    }
  }

  char cstr[3];
  cstr[0] = number.str[max_idx];
  cstr[1] = number.str[max_idx_second_digit];
  cstr[2] = '\0';
  String* joltage_string = cstr_to_str_or_die(cstr, 2);
  ToU64Result res = str_to_u64(joltage_string);
  free_str_or_die(joltage_string);
  if (res.status == SUCCESS) {
    printf("Returning %lu for %s", res.result, line->str);
    return (u64)res.result;
  }
  puts("shouldn't have gotten here");
  exit(-1);
}

u64 part2_joltage_per_line(String* line) {
  Result r = strip_in_place(line);
  if (r != SUCCESS) {
    puts("Failed to strip in place");
    exit(-1);
  }
  String number = *line;
  char cstr[13];
  u64 i, k;
  char max;
  i32 max_idx = -1;
  for (i = 0; i < 12; i++) {
    max = '0';
    max_idx++;
    for (k = max_idx; k < number.size - (11 - i); k++) {
      if(number.str[k] > max) {
        max = number.str[k];
        max_idx = k;
      }
    }
    cstr[i] = number.str[max_idx];
  }


  cstr[12] = '\0';
  String* joltage_string = cstr_to_str_or_die(cstr, 12);
  ToU64Result res = str_to_u64(joltage_string);
  free_str_or_die(joltage_string);
  if (res.status == SUCCESS) {
    printf("Returning %lu for %s", res.result, line->str);
    return res.result;
  }
  puts("shouldn't have gotten here");
  exit(-1);
}
