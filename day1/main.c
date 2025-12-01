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
    numbers = slice(line, 1, line->size - 1); /* -1 for \n */
    ToIntResult res = str_to_int(numbers);
    if (res.status == FAIL) {
      printf("Parsing numbers failed for numbers %s", numbers->str);
      exit(-1);
    }
    i64 i = res.result;
    if(line->str[0] == 'R') {
      while (i > 0) {
        p2_dial++;
        i--;
        if (p2_dial == 0) {
          puts("Passed zero here");
          part2_answer++;
        } else if (p2_dial > 99) {
          p2_dial -= 100;
          part2_answer++;
          puts("pased zero here too?");
        } else if (p2_dial < 0) {
          p2_dial += 100;
        }
      }

      dial += res.result;
    } else if (line->str[0] == 'L') {
      while (i > 0) {
        p2_dial--;
        i--;
        if (p2_dial == 0) {
          puts("Passed zero here");
          part2_answer++;
        } else if (p2_dial > 99) {
          part2_answer++;
          puts("pased zero here too?");
          p2_dial -= 100;
        } else if (p2_dial < 0) {
          p2_dial += 100;
        }
      }
      dial -= res.result;
    } else {
      printf("Unknown first letter\n");
    }
    while (dial < 0) {
      dial += 100;
    }

    while (dial > 99) {
      dial -= 100;
    }
    if (dial == 0) {
      part1_answer++;
    }

    if (dial != p2_dial) {
      puts("ERROR: dials out of sync");
    }
    printf("New dial answer at %d\n", dial);
    free_str(line);
    free_str(numbers);
  }
  printf("Part 1 answer: %d\n", part1_answer);
  printf("Part 2 answer: %d\n", part2_answer);

  exit(0);
}
