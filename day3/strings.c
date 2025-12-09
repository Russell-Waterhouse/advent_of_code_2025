#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "./types.h"
#include "./strings.h"

#define START_SIZE 255

String* cstr_to_str_or_die(char* cstr, u32 size) {
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

void free_str_or_die(String* s) {
  if (NULL == s || NULL == s->str) {
    printf("Double free attempt\n");
    exit(-1);
  }
  free(s->str);
  free(s);
}

char* to_cstr(String* s);
u32 str_equal(String* s1, String* s2) {
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

char char_at_or_die(String* s, u32 idx) {
  if (s->size < idx) {
    printf("accessing char_at with invalid index %d", idx);
    exit(-1);
  }

  return s->str[idx];
}

String* concat_or_die(String* s1, String* s2) {
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


SliceResult slice(String* s1, u32 start, u32 end) {
  SliceResult res;
  u32 i;
  String* s;
  u32 size;

  if (NULL == s1 || start > end) {
    res.status = FAIL;
    return res;
  }
  size = end - start;

  s = calloc(1, sizeof *s);
  if (!s) {
    res.status = FAIL;
    return res;
  }
  s->str = (char*)calloc(size, sizeof(char));
  if (!s->str) {
    res.status = FAIL;
    return res;
  }

  for(i = 0; i < end - start; i++) {
    s->str[i] = s1->str[i+start];
  }
  s->size = size;
  s->memsize = size;
  res.status = SUCCESS;
  res.slice = s;
  return res;
}

SplitResultOption split_str(String* s, char split_char) {
  SplitResultOption res;
  DynStringArr* strs = NULL;
  u32 i;
  u32 start;
  res.num_strs = 0;

  if (NULL == s) {
    res.status = FAIL;
    return res;
  }

  start = 0;
  for (i = 0; i < s->size; i++) {
    if (s->str[i] == split_char) {
      SliceResult slice_result = slice(s, start, i);
      /* TODO: if sliceresult.status == success, do the rest*/
      strs = insert_back_or_die(strs, *slice_result.slice);
      start = i + 1;
      res.num_strs++;
    }
  }
  if (start != i) {
      SliceResult slice_result = slice(s, start, i);
      /* TODO: if sliceresult.status == success, do the rest*/
      strs = insert_back_or_die(strs, *slice_result.slice);
      start = i + 1;
      res.num_strs++;
  }
  res.status = SUCCESS;
  res.strs = strs;
  return res;
}

SplitResult split_str_or_die(String* s, char split_char) {
  SplitResult res;
  DynStringArr* strs = NULL;
  u32 i;
  u32 start;
  res.num_strs = 0;

  if (NULL == s) {
    printf("Null string in split_str_or_die");
    exit(-1);
  }

  start = 0;
  for (i = 0; i < s->size; i++) {
    if (s->str[i] == split_char) {
      SliceResult slice_result = slice(s, start, i);
      /* TODO: if sliceresult.status == success, do the rest*/
      strs = insert_back_or_die(strs, *slice_result.slice);
      start = i + 1;
      res.num_strs++;
    }
  }
  if (start != i) {
      SliceResult slice_result = slice(s, start, i);
      /* TODO: if sliceresult.status == success, do the rest*/
      strs = insert_back_or_die(strs, *slice_result.slice);
      start = i + 1;
      res.num_strs++;
  }
  res.strs = strs;
  return res;
}

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

ToU64Result str_to_u64(String* s) {
  ToU64Result res;
  u64 result = 0;
  if (NULL == s || NULL == s->str) {
    res.status = FAIL;
    return res;
  }

  u64 i;
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


String* u64_to_str_or_die(u64 v) {
  /* u32 has a max of 20 digits */
  char str[32];
  sprintf(str, "%lu", v);
  String* s = cstr_to_str_or_die(str, strlen(str));

  return s;
}


Result strip_in_place(String* s) {
  /* TODO: Finish the rest of this */
  if (s->str[s->size - 1] == '\n') {
    s->size--;
  }

  return SUCCESS;
}

DynStringArr* insert_back_or_die(DynStringArr* a, String value) {
  if (a == NULL) {
    a = calloc(1, sizeof *a);
    if (a == NULL) {
      printf("Failed to allocate memory for array holder\n");
      exit(-1);
    }

    a->arr = calloc(START_SIZE, sizeof(String));
    if (!a->arr) {
      printf("Failed to allocate memory for array\n");
      exit(-1);
    }

    a->memsize = START_SIZE;
    a->arr[a->size] = value;
    a->size++;
    return a;
  }

  if (a->size >= a->memsize) {
    size_t new_memsize = a->memsize * 2;
    a = realloc(a, new_memsize);
    if (a == NULL) {
      printf("Failed to allocate memory for array");
      exit(-1);
    }
    a->memsize = new_memsize;
  }
  a->arr[a->size] = value;
  a->size++;
  return a;
}

String at_or_die(DynStringArr* a, size_t index) {
  if (a == NULL) {
    printf("Passed a null dynamic array to the 'at' function. Exiting the program.");
    exit(-1);
  }
  if (index >= a->size) {
    printf("Attempted to index an array outsize of its size. Exiting the program.");
    exit(-1);
  }

  return a->arr[index];
}
