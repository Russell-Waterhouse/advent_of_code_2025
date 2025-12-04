#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "strings.c"

u64 LINE_SIZE = 10 * 1000; /* ten kilobytes */

u64 num_invalid_inputs_per_range(String* range);
u64 str_is_invalid(String* s);

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
  input_file = fopen("input.txt", "r");

  if (NULL == input_file) {
    puts("Failed to open file");
    exit(-1);
  }
  fgets(input, LINE_SIZE - 1, input_file);
  line = cstr_to_str_or_die(input, strlen(input));
  if (blank(line)) {
    puts("Input line is blank");
    exit(-1);
  }


  SplitResult split_result = split_str_or_die(line, ',');
  if (split_result.num_strs < 1) {
    puts("Failed to split strings somehow");
    exit(-1);
  }

  u64 i;
  for (i = 0; i < split_result.num_strs; i++) {
    String s = split_result.strs->arr[i];
    part1_answer += num_invalid_inputs_per_range(&s);
  }


  printf("Part 1 answer is %lu\n", part1_answer);
  printf("Part 2 answer is %lu\n", part2_answer);
  free_str_or_die(line);
  free(input);
  exit(0);
}


u64 num_invalid_inputs_per_range(String* range) {
  u64 invalid_nums_count = 0;
  SplitResult range_strs = split_str_or_die(range, '-');
  u64 i;
  if (range_strs.num_strs != 2) {
    puts("didn't get 2 strings in num_strs in num_invalid_inputs_per_range");
    exit(-1);
  }

  strip_in_place(&range_strs.strs->arr[0]);
  strip_in_place(&range_strs.strs->arr[1]);
  ToU64Result start = str_to_u64(&range_strs.strs->arr[0]);
  ToU64Result end = str_to_u64(&range_strs.strs->arr[1]);
  for (i = start.result; i <= end.result; i++) {
    String* s = u64_to_str_or_die(i);
    if (str_is_invalid(s)) {
      invalid_nums_count += i;
    }
    free_str_or_die(s);
  }

  return invalid_nums_count;
}


u64 str_is_invalid(String* s){
  if (!s) {
    puts("Null passed to str_is_palindrome");
    exit(-1);
  }
  if ((s->size % 2) != 0) {
    /* Only strings with an even number of chars can be invalid */
    return 0;
  }

  u64 i;
  for (i = 0; i < (s->size / 2); i++) {
    /*printf("\tComparing %c to %c\n", s->str[i], s->str[i*2]);*/
    if (s->str[i] != s->str[i + (s->size / 2)]) {
      printf("\tValid string: %c != %c in %s\n", s->str[i], s->str[i + (s->size / 2)], s->str);
      return 0;
    }
  }

  printf("Invalid String: %s\n", s->str);
  return 1;
}
