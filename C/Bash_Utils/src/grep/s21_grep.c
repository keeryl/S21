#include "s21_grep.h"

int main(int argc, char **argv) {
  char *patterns[1024] = {NULL};
  char *patterns_files[1024];
  char *search_files[1024];
  int search_files_count = 0;
  int patterns_count = 0;
  int patterns_files_count = 0;
  int print_all = 0;

  parse_args(argc, argv, &flags, patterns, patterns_files, &patterns_count,
             &patterns_files_count);
  process_args(argc, argv, flags, patterns, &patterns_count, search_files,
               &search_files_count, patterns_files, patterns_files_count,
               &print_all);
  grep(flags, patterns, patterns_count, search_files, search_files_count,
       print_all);
  for (int i = 0; i < patterns_count; i++) free(patterns[i]);
  return 0;
}

