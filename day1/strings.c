#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./types.h"

typedef struct String {
  size_t size;
  size_t memsize;
  char* str;
} String;

String* cstr_to_str(char* cstr, u32 size) {
  u32 i;
  String* s;
  s = calloc(1, sizeof(*s));
  if (!s) {
    printf("failed to allocate memory for cstr");
    exit(-1);
  }

  s->str = (char*)calloc(size, sizeof(char));
  if (!s->str) {
    printf("failed to allocate memory for cstr arr\n");
    exit(-1);
  }

  for(i = 0; i < size; i++) {
    s->str[i] = cstr[i];
  }

  s->size = size;
  s->memsize = size;

  return s;
}

void free_str(String* s) {
  if (NULL == s || NULL == s->str) {
    printf("Double free attempt\n");
    exit(-1);
  }
  free(s->str);
  free(s);
}

char* to_cstr(String* s);
u32 equal(String* s1, String* s2) {
  u32 i;
  if (NULL == s1 || NULL == s2) {
    return 0;
  }
  if (s1->size != s2->size) {
    return 0;
  }
  for(i = 0; i < s1->size; i++) {
    if (s1->str[i] != s2->str[i]) {
      return 0;
    }
  }
  return 1;
}

char char_at(String* s, u32 idx) {
  if (s->size < idx) {
    printf("accessing char_at with invalid index %d", idx);
    exit(-1);
  }

  return s->str[idx];
}

String* concat(String* s1, String* s2) {
  u32 i, j;
  String* s;
  u32 size;
  s = calloc(1, sizeof *s);
  if (!s1 || !s2 || !s1->str || !s2->str) {
    printf("Called concat with null string(s)\n");
    exit(-1);
  }
  size = s1->size + s2->size;

  if (!s) {
    printf("failed to allocate memory for cstr");
    exit(-1);
  }

  s->str = calloc(size, sizeof(char));
  if (!s->str) {
    printf("failed to allocate memory for cstr arr\n");
    exit(-1);
  }

  for(i = 0; i < s1->size; i++) {
    s->str[i] = s1->str[i];
  }
  for(j = 0; j < s2->size; j++, i++) {
    s->str[i] = s2->str[j];
  }

  return s;
}

u32 ends_with(String* s1, String* search_str);
u32 starts_with(String* s1, String* search_str);
u32 includes(String* s1, String* search_str);
i32 index_of(String* s1, String* search_str);
u32 replace(String* s1, String* search_str, String* replacement_str);
u32 replace_all(String* s1, String* search_str, String* replacement_str);
String* slice(String* s1, u32 start, u32 end) {
  /* TODO input validation */
  u32 i;
  String* s;
  u32 size;

  if (NULL == s1 || start > end) {
    printf("Invalid params passed to string slice: %d > %d or s is null\n", start, end);
    exit(-1);
  }
  size = end - start;

  s = calloc(1, sizeof *s);
  if (!s) {
    printf("failed to allocate memory for cstr");
    exit(-1);
  }
  s->str = (char*)calloc(size, sizeof(char));
  if (!s->str) {
    printf("failed to allocate memory for cstr arr\n");
    exit(-1);
  }

  for(i = 0; i < end - start; i++) {
    s->str[i] = s1->str[i+start];
  }
  s->size = size;
  s->memsize = size;
  return s;
}

typedef struct SplitResult {
  u32 num_strs;
  String* strs[];
} SplitResult;

SplitResult* Split(String* s, char split_char);
String* trim(String* s);
u32 blank(String* s) {
  u32 i;
  if (NULL == s || NULL == s->str) {
    return 1;
  }
  for (i = 0; i < s->size; i++) {
    if (s->str[i] != ' ' && s->str[i] != '\t' && s->str[i] != '\0' && s->str[i] != '\n') {
      return 0;
    }
  }
  return 1;
}

typedef struct ToIntResult {
  Result status;
  i64 result;
} ToIntResult;

ToIntResult str_to_int(String* s) {
  ToIntResult res;
  i64 result = 0;
  if (NULL == s || NULL == s->str) {
    res.status = FAIL;
    return res;
  }

  u32 i;
  for (i = 0; i < s->size; i++) {
    char c = s->str[i];
    if (c < '0' || c > '9') {
      printf("Failed to parse ascii code %d\n", c);
      res.status = FAIL;
      return res;
    }
    result *= 10;
    result += (c - '0');
  }


  res.status = SUCCESS;
  res.result = result;

  return res;
}



