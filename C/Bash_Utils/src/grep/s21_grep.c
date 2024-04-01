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

void process_args(int argc, char **argv, grep_flags flags, char **patterns,
                  int *patterns_count, char **search_files,
                  int *search_files_count, char **pattern_files,
                  int pattern_files_count, int *print_all) {
  if (!flags.e && !flags.f) {
    char *pattern = malloc(strlen(argv[optind]) + 1);
    strcpy(pattern, argv[optind]);
    patterns[*patterns_count] = pattern;
    *patterns_count += 1;
    optind += 1;
  }
  for (int i = optind; i < argc; i++) {
    search_files[*search_files_count] = argv[i];
    *search_files_count += 1;
  }

  if (flags.f) {
    for (int i = 0; i < pattern_files_count; i++) {
      if (*print_all == 1) break;
      FILE *file = fopen(pattern_files[i], "r");
      if (!file) {
        fprintf(stderr, "grep: %s: No such file or directory\n",
                pattern_files[i]);
        exit(1);
      } else {
        size_t size = 2048;
        while (!feof(file)) {
          char *line = NULL;
          getline(&line, &size, file);
          if (line[0] == 0 || line[0] == EOF) {
            free(line);
            break;
          }
          if (line[0] == '\n') {
            *print_all = 1;
            free(line);
            break;
          }
          if (line[strlen(line) - 1] == EOF) line[strlen(line) - 1] = '\0';
          if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
          patterns[*patterns_count] = line;
          *patterns_count += 1;
        }
        fclose(file);
      }
    }
  }
}

void process_flag_e(char **patterns, int *patterns_count) {
  char *pattern = malloc(strlen(optarg) + 1);
  strcpy(pattern, optarg);
  patterns[*patterns_count] = pattern;
  *patterns_count += 1;
}

void process_flag_f(char **patterns_files, int *patterns_files_count) {
  patterns_files[*patterns_files_count] = optarg;
  *patterns_files_count += 1;
}

void count_matched_lines(grep_flags flags, int *matches, int isMatch) {
  if (flags.v) {
    if (isMatch == 0) *matches += 1;
  } else {
    if (isMatch == 1) *matches += 1;
  }
}

int pattern_search(char *line, grep_flags flags, char **patterns,
                   int patterns_count, int search_files_count,
                   const char *filename, int line_counter) {
  int isMatch = 0;
  for (int i = 0; i < patterns_count; i++) {
    int search_res = -1;
    regex_t regexp = {0};
    regmatch_t pmatch = {0};
    int reg_comp_error = 0;
    if (flags.i) {
      reg_comp_error = regcomp(&regexp, patterns[i], REG_EXTENDED | REG_ICASE);
    } else {
      reg_comp_error = regcomp(&regexp, patterns[i], REG_EXTENDED);
    }
    if (reg_comp_error) {
      fprintf(stderr, "grep: Failed to compile regexp %s\n", patterns[i]);
      exit(1);
    }
    search_res = regexec(&regexp, line, 1, &pmatch, 0);
    if (flags.o && !flags.v) {
      if (search_res == 0) {
        char matches_string[1024] = {'\0'};
        strncat(matches_string, line + pmatch.rm_so,
                pmatch.rm_eo - pmatch.rm_so);
        output_line(flags, isMatch, filename, line_counter, search_files_count,
                    matches_string);
        line = line + pmatch.rm_eo;
        isMatch = 1;
        while (regexec(&regexp, line, 1, &pmatch, 0) == 0) {
          line = line + pmatch.rm_eo;
          output_line(flags, isMatch, filename, line_counter,
                      search_files_count, matches_string);
        }
      }
    } else {
      if (search_res == 0) {
        isMatch = 1;
        output_line(flags, isMatch, filename, line_counter, search_files_count,
                    line);
        regfree(&regexp);
        break;
      }
    }
    regfree(&regexp);
  }
  if (flags.v) {
    output_line(flags, isMatch, filename, line_counter, search_files_count,
                line);
  }

  return isMatch;
}

void print_line(grep_flags flags, int line_counter, const char *line) {
  int line_len = strlen(line);
  if (flags.n) printf("%d:", line_counter);
  printf("%s", line);
  if (line_len > 0 && line[line_len - 1] != '\n') printf("%c", '\n');
  if (line_len == 0 && line[line_len] != '\n') printf("%c", '\n');
}

void output_line(grep_flags flags, int isMatch, const char *file,
                 int line_counter, int search_files_count, const char *line) {
  if (!flags.c && !flags.l) {
    if (flags.v) {
      if (isMatch == 0) {
        handle_filename_output(flags, search_files_count, file);
        print_line(flags, line_counter, line);
      }
    } else if (flags.o) {
      if (isMatch == 0) {
        handle_filename_output(flags, search_files_count, file);
        if (flags.n) printf("%d:", line_counter);
      }
      printf("%s\n", line);
    } else {
      if (isMatch == 1) {
        handle_filename_output(flags, search_files_count, file);
        print_line(flags, line_counter, line);
      }
    }
  }
}

void handle_cl_flags(grep_flags flags, int matches, const char *filename,
                     int search_files_count, int isMatch) {
  if (flags.c || flags.l) {
    if (flags.c) {
      handle_filename_output(flags, search_files_count, filename);
      printf("%d\n", matches);
    }
    if (flags.l) {
      if (isMatch == 1) {
        printf("%s\n", filename);
      }
    }
  }
}