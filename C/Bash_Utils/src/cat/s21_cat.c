#include "s21_cat.h"

int main(int argc, char **argv) {
  parse_args(argc, argv, &flags);
  for (int i = optind; i < argc; i++) {
    cat(flags, argv[i]);
  }
  return 0;
}

void parse_args(int argc, char **argv, cat_flags *flags) {
  static struct option long_options[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };
  int option;
  int option_index;
  while ((option = getopt_long(argc, argv, "+benstvTE", long_options,
                               &option_index)) != -1) {
    switch (option) {
      case 'b':
        flags->b = 1;
        break;
      case 'e':
        flags->e = 1;
        flags->v = 1;
        break;
      case 'E':
        flags->e = 1;
        flags->v = 0;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 't':
        flags->t = 1;
        flags->v = 1;
        break;
      case 'T':
        flags->t = 1;
        flags->v = 0;
        break;
      case 'v':
        flags->v = 1;
        break;
      default:
        fprintf(stderr, "usage: s21_cat [-benstvTE] [file ...]\n");
        exit(1);
        break;
    }
  }
}