#!/bin/bash
set -e
rm -f ./a

gcc \
  --std=c89 \
  -Werror \
  -Wall \
  ./main.c \
  ./strings.c \
  -I. \
  -o \
  a

./a
