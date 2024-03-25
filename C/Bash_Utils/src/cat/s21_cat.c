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

void cat(cat_flags flags, const char *filePath) {
  FILE *file = fopen(filePath, "r");
  if (file) {
    char current, next, prev = -1;
    int string_counter = 0;
    while ((current = getc(file)) != EOF) {
      if (flags.s) {
        next = getc(file);
        if ((prev == '\n' || prev == -1) && current == '\n' && next == '\n') {
          ungetc(next, file);
          continue;
        }
        ungetc(next, file);
      }
      if (flags.b) {
        if ((prev == '\n' || prev == -1) && current != '\n')
          printf("%6d\t", ++string_counter);
      } else if (flags.n) {
        if (prev == '\n' || prev == -1) printf("%6d\t", ++string_counter);
      }
      if (flags.v) {
        if ((current >= 0 && current < 32 && current != 9 && current != 10) ||
            current == 127) {
          if (current == 127) {
            printf("^?");
            continue;
          } else {
            printf("^%c", (current + 64));
            continue;
          }
        }
      }
      if (flags.e) {
        // Блок кода для другой версии cat на машине

        // if ((prev == '\n' || prev == -1) && current == '\n' && flags.b)
        //   printf("\t$");
        // else if (current == '\n') printf("$");

        if (current == '\n') printf("$");
      }
      if (flags.t) {
        if (current == '\t') {
          printf("^I");
          continue;
        }
      }
      printf("%c", current);
      prev = current;
    }
  } else {
    fprintf(stderr, "s21_cat: %s: No such file or directory\n", filePath);
  }
}