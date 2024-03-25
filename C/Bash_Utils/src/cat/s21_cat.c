#include "s21_cat.h"

int main(int argc, char **argv) {
  parse_args(argc, argv, &flags);
  for (int i = optind; i < argc; i++) {
    cat(flags, argv[i]);
  }
  return 0;
}