#define _GNU_SOURCE
#define NMAX 1024
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/flags.h"

bool set_flags(char symbol_flag, flag *f);
bool check_flag(int argc, char **argv, flag *f);
void set_pattern(int argc, char **argv, const flag *f, bool optionals,
                 regex_t *regex, int *index);
void grep(const char *filename, const flag *f, bool index_filename,
          regex_t *regex);
void grep_file(FILE *myfile, const flag *f, regex_t *preg, bool index_filename,
               const char *filename);
void grep_file_flag_c(FILE *myfile, const flag *f, regex_t *preg,
                      bool index_filename, const char *filename);
void grep_file_flag_l(FILE *myfile, regex_t *preg, const char *filename);
void make_new_pattern(char *new_pattern, const char *old_pattern,
                      int *index_new_pattern, bool *flag_make);
void app_pattern(char *new_pattern, int *index_new_pattern,
                 const char *old_pattern);
void patterns_from_file(char *new_pattern, const char *patterns_file,
                        int *index_new_pattern, bool *flag_make);

int main(int argc, char **argv) {
  if (argc <= 2) {
    printf("INVALID OPTIONALS\n");
    exit(1);
  }
  flag f;
  flag_init(&f);
  int index = 0;
  regex_t preg_regex;
  regex_t *regex = &preg_regex;
  bool optional = check_flag(argc, argv, &f);
  set_pattern(argc, argv, &f, optional, regex, &index);
  bool index_filename = false;
  if ((f.h == false) && (argc - index > 2)) {
    index_filename = true;
  }
  for (int i = index + 1; i < argc; i++) {
    grep(argv[i], &f, index_filename, regex);
  }
  regfree(regex);
  return 0;
}

bool set_flags(char symbol_flag, flag *f) {
  bool answer = true;
  switch (symbol_flag) {
    case 'e':
      f->e = true;
      break;
    case 'i':
      f->i = true;
      break;
    case 'v':
      f->v = true;
      break;
    case 'c':
      f->c = true;
      break;
    case 'n':
      f->n = true;
      break;
    case 'l':
      f->l = true;
      break;
    case 'h':
      f->h = true;
      break;
    case 'o':
      f->o = true;
      break;
    case 's':
      f->s = true;
      break;
    case 'f':
      f->f = true;
      break;
    default:
      answer = false;
      break;
  }
  return answer;
}

bool check_flag(int argc, char **argv, flag *f) {
  bool answer = false;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      answer = true;
      char *ptr = &argv[i][1];
      while (*ptr != '\0') {
        set_flags(*ptr, f);
        ptr++;
      }
    }
  }
  return answer;
}

void set_pattern(int argc, char **argv, const flag *f, bool optionals,
                 regex_t *regex, int *index) {
  bool flag_make = false;
  char **pattern;
  char pattern_e_f[NMAX];
  int index_new_pattern = 0;
  if (optionals == true) {
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] == '-') {
        for (int j = 1; argv[i][j] != '\0'; j++) {
          if (argv[i][j] == 'e') {
            char **old_pattern = &argv[i + 1];
            make_new_pattern(pattern_e_f, *old_pattern, &index_new_pattern,
                             &flag_make);
            *index = i + 1;
          }
          if (argv[i][j] == 'f') {
            char **pattern_file = &argv[i + 1];
            patterns_from_file(pattern_e_f, *pattern_file, &index_new_pattern,
                               &flag_make);
            *index = i + 1;
          } else if ((f->f == false) && (f->e == false)) {
            pattern = &argv[i + 1];
            *index = i + 1;
          }
        }
      }
    }
  } else {
    pattern = &argv[1];
    *index = 1;
  }
  if ((f->e == true) || (f->f == true)) {
    regcomp(regex, pattern_e_f, REG_EXTENDED);
  } else if (f->i == true) {
    regcomp(regex, *pattern, REG_ICASE);
  } else {
    regcomp(regex, *pattern, 0);
  }
}

void grep(const char *filename, const flag *f, bool index_filename,
          regex_t *regex) {
  FILE *fp;
  fp = fopen(filename, "rt");
  if (fp == NULL) {
    if (f->s == false) {
      printf("grep: %s: No such file or directory\n", filename);
    }
  } else {
    if (f->c == true) {
      grep_file_flag_c(fp, f, regex, index_filename, filename);
    } else if (f->l == true) {
      grep_file_flag_l(fp, regex, filename);
    } else {
      grep_file(fp, f, regex, index_filename, filename);
    }
    fclose(fp);
  }
}

void grep_file(FILE *myfile, const flag *f, regex_t *preg, bool index_filename,
               const char *filename) {
  char *line = NULL;
  size_t size = 0;
  regmatch_t match;
  int count_lines = 0;
  bool last_symbol = true;
  while (getline(&line, &size, myfile) > 0) {
    count_lines++;
    if (f->v == true) {
      if (regexec(preg, line, 1, &match, 0)) {
        if (index_filename == true) {
          printf("%s:", filename);
        }
        if (f->n == true) {
          printf("%d:", count_lines);
        }
        printf("%s", line);
        int len = strlen(line);
        if (line[len - 1] != '\n') {
          last_symbol = false;
        }
        if ((f->o == true) && (last_symbol == false)) {
          printf("\n");
        }
      }
    } else {
      if (!regexec(preg, line, 1, &match, 0)) {
        if (index_filename == true) {
          printf("%s:", filename);
        }
        if (f->n == true) {
          printf("%d:", count_lines);
        }
        if (f->o == true) {
          for (int i = match.rm_so; i < match.rm_eo; i++) {
            printf("%c", line[i]);
          }
          printf("\n");
        } else {
          printf("%s", line);
          int len = strlen(line);
          if (line[len - 1] != '\n') {
            last_symbol = false;
          }
        }
      }
    }
  }
  if ((f->o == false) && (last_symbol == false)) {
    printf("\n");
  }

  free(line);
}

void grep_file_flag_c(FILE *myfile, const flag *f, regex_t *preg,
                      bool index_filename, const char *filename) {
  char *line = 0;
  size_t size = 0;
  int index_lines = 0;
  regmatch_t match;
  while (getline(&line, &size, myfile) > 0) {
    if (f->v == true) {
      if (regexec(preg, line, 1, &match, 0)) {
        index_lines++;
        if (f->l == true) {
          break;
        }
      }
    } else {
      if (!regexec(preg, line, 1, &match, 0)) {
        index_lines++;
        if (f->l == true) {
          break;
        }
      }
    }
  }
  if (index_filename == true) {
    printf("%s:%d", filename, index_lines);
  } else {
    printf("%d", index_lines);
  }
  printf("\n");
  if (f->l == true) {
    printf("%s\n", filename);
  }
  free(line);
}

void grep_file_flag_l(FILE *myfile, regex_t *preg, const char *filename) {
  char *line = 0;
  size_t size = 0;
  bool flag_l_filename = false;
  regmatch_t match;
  while (getline(&line, &size, myfile) > 0) {
    if (!regexec(preg, line, 1, &match, 0)) {
      flag_l_filename = true;
    }
  }
  if (flag_l_filename == true) {
    printf("%s", filename);
  }

  printf("\n");
  free(line);
}

void make_new_pattern(char *new_pattern, const char *old_pattern,
                      int *index_new_pattern, bool *flag_make) {
  if (*flag_make == false) {
    new_pattern[0] = '(';
    ++*index_new_pattern;
    *flag_make = true;
  }
  app_pattern(new_pattern, index_new_pattern, old_pattern);
  new_pattern[*index_new_pattern] = ')';
}

void app_pattern(char *new_pattern, int *index_new_pattern,
                 const char *old_pattern) {
  if (new_pattern[*index_new_pattern] == ')') {
    new_pattern[*index_new_pattern] = '|';
    ++*index_new_pattern;
  }
  int len_old = strlen(old_pattern);
  for (int i = 0; i < len_old; i++) {
    new_pattern[*index_new_pattern] = old_pattern[i];
    ++*index_new_pattern;
  }
}

void patterns_from_file(char *new_pattern, const char *patterns_file,
                        int *index_new_pattern, bool *flag_make) {
  FILE *fp;
  fp = fopen(patterns_file, "rt");
  if (fp == NULL) {
    printf("INVALID OPTIONALS\n");
    exit(1);
  }
  char *line = NULL;
  size_t size = 0;
  while (getline(&line, &size, fp) > 0) {
    int len_line = strlen(line);
    if (line[len_line - 1] == '\n') {
      line[len_line - 1] = '\0';
    }
    make_new_pattern(new_pattern, line, index_new_pattern, flag_make);
  }
  free(line);
  fclose(fp);
}