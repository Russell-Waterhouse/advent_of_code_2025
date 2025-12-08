#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "strings.c"

u64 LINE_SIZE = 10 * 1000; /* ten kilobytes */

typedef struct results {
  u64 p1;
  u64 p2;
} results;

results num_invalid_inputs_per_range(String* range);
u64 str_is_invalid(String* s);
u64 str_is_invalid_part2(String* s);

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
    part1_answer += num_invalid_inputs_per_range(&s).p1;
    part2_answer += num_invalid_inputs_per_range(&s).p2;
  }


  printf("Part 1 answer is %lu\n", part1_answer);
  printf("Part 2 answer is %lu\n", part2_answer);
  free_str_or_die(line);
  free(input);
  exit(0);
}


results num_invalid_inputs_per_range(String* range) {
  results res;
  u64 invalid_nums_count_p1 = 0;
  u64 invalid_nums_count_p2 = 0;
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
      invalid_nums_count_p1 += i;
    }
    if (str_is_invalid_part2(s)) {
      invalid_nums_count_p2 += i;
    }
    free_str_or_die(s);
  }
  res.p1 = invalid_nums_count_p1;
  res.p2 = invalid_nums_count_p2;

  return res;
}


u64 str_is_invalid(String* s) {
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
      return 0;
    }
  }

  return 1;
}


u64 str_is_invalid_part2(String* s){
  if (!s) {
    puts("Null passed to str_is_invalid_part2");
    exit(-1);
  }

  u64 i, j, k;
  /*
   * i is the size of the segment we're dividing the string into;
   *   i.e. in 999, we would divide the string into segments of size 1;
   * j is the segment we're comparing
   *   i.e. in 999, j would first be 1, then 2.
   *   i.e. in 123123, j would only be 1.
   * k is the index of the segment we're comparing in j.
   *   i.e. in 123123, j would be 0, 1, 2.
   *
   */
  for (i = 1; i < (s->size / 2); i++) {
    i32 continue_outer = 0;
    if (s -> size % i != 0) {
      continue;
    }

    for (j = 1; j < (s->size / i); j++) {
      for (k = 0; k < i; k++) {
        u64 cmp_idx = k + (j * i);
        if (cmp_idx > s-> size) {
          printf("Err string: %s; i: %lu; j: %lu; k: %lu\n", s->str, i, j, k);
          exit(-1);
        }

        printf("\tComparing %c at index %lu to %c at index %lu; i: %lu; j: %lu; k: %lu\n", s->str[k], k, s->str[cmp_idx], cmp_idx, i, j, k);
        if (s->str[k] != s->str[cmp_idx]) {
          continue_outer = 1;
        }
      }
    }
    if (continue_outer) {
      printf("ignoring: %s\n", s->str);
      continue;
    }
    printf("SUCCESSFUL_FIND: %s\n", s->str);
    return 1;
  }


  return 0;
}
