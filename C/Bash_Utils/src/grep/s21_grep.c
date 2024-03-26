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

void parse_args(int argc, char **argv, grep_flags *flags, char **patterns,
                char **patterns_files, int *patterns_count,
                int *patterns_files_count) {
  static struct option long_options[] = {
      {0, 0, 0, 0},
  };
  int option, option_index;
  while ((option = getopt_long(argc, argv, "e:ivclnhsf:o", long_options,
                               &option_index)) != -1) {
    switch (option) {
      case 'e':
        flags->e = 1;
        process_flag_e(patterns, patterns_count);
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'f':
        flags->f = 1;
        process_flag_f(patterns_files, patterns_files_count);
        break;
      case 'o':
        flags->o = 1;
        break;
      default:
        fprintf(stderr, "usage: s21_grep [-eivclnhsfo] [file ...]\n");
        exit(1);
        break;
    }
  }
}