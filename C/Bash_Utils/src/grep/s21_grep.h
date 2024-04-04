#ifndef S21_GREP
#define S21_GREP

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} grep_flags;

grep_flags flags = {0};

void parse_args(int argc, char **argv, grep_flags *flags, char **patterns,
                char **patterns_files, int *patterns_count,
                int *patterns_files_count);
void process_args(int argc, char **argv, grep_flags flags, char **patterns,
                  int *patterns_count, char **search_files,
                  int *search_files_count, char **pattern_files,
                  int pattern_files_count, int *print_all);
void process_flag_e(char **patterns, int *patterns_count);
void process_flag_f(char **patterns_files, int *patterns_files_count);
void count_matched_lines(grep_flags flags, int *matches, int isMatch);
void grep(grep_flags flags, char **patterns, int patterns_count,
          char **search_files, int search_files_count, int print_all);
void print_line(grep_flags flags, int line_counter, const char *line);
void output_line(grep_flags flags, int isMatch, const char *file,
                 int line_counter, int search_files_count, const char *line);
void handle_cl_flags(grep_flags flags, int matches, const char *filename,
                     int search_files_count, int isMatch);
void handle_filename_output(grep_flags flags, int search_files_count,
                            const char *filename);
int pattern_search(char *line, grep_flags flags, char **patterns,
                   int patterns_count, int search_files_count,
                   const char *filename, int line_counter);

#endif