#ifndef S21_CAT
#define S21_CAT

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} cat_flags;

cat_flags flags = {0};

void parse_args(int argc, char **argv, cat_flags *flags);
void cat(cat_flags flags, const char *filePath);

#endif
