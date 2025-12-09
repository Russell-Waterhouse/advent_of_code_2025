#ifndef MY_STRINGS_H
#define MY_STRINGS_H

#include <stddef.h>
#include "./types.h"

typedef struct String {
  size_t size;
  size_t memsize;
  char* str;
} String;

typedef struct DynStringArr {
  size_t memsize;
  size_t size;
  String* arr;
} DynStringArr;

typedef struct SplitResultOption {
  Result status;
  u32 num_strs;
  DynStringArr* strs;
} SplitResultOption;

typedef struct SplitResult {
  u32 num_strs;
  DynStringArr* strs;
} SplitResult;

typedef struct ToU64Result {
  Result status;
  u64 result;
} ToU64Result;

typedef struct SliceResult {
  Result status;
  String* slice;
} SliceResult;

/* _or_die functions */
String* cstr_to_str_or_die(char* cstr, u32 size);
void free_str_or_die(String* s);
char char_at_or_die(String* s, u32 idx);
String* u64_to_str_or_die(u64 v);
String* concat_or_die(String* s1, String* s2);
SplitResult split_str_or_die(String* s, char split_char);
DynStringArr* insert_back_or_die(DynStringArr* a, String value);
String at_or_die(DynStringArr* a, size_t index);

/* save optional/result type functions */
SliceResult slice(String* s1, u32 start, u32 end);
SplitResultOption split_str(String* s, char split_char);
char* to_cstr(String* s);
u32 str_equal(String* s1, String* s2);
ToU64Result str_to_u64(String* s);
String* trim(String* s);
u32 blank(String* s);

/* not yet implemented functions */
u32 ends_with(String* s1, String* search_str);
u32 starts_with(String* s1, String* search_str);
u32 includes(String* s1, String* search_str);
i32 index_of(String* s1, String* search_str);
u32 replace(String* s1, String* search_str, String* replacement_str);
u32 replace_all(String* s1, String* search_str, String* replacement_str);

/* _in_place functions */
Result strip_in_place(String* s);

#endif /* MY_STRINGS_H */
