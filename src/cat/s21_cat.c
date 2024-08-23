#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/flags.h"

bool set_flag(char symbol_flag, flag *f);
bool check_gnu_flag(const char *s, flag *f);
bool check_flag(int argc, char **argv, flag *f, int *index_myfile);
void cat(const char *myfile, const flag *f, bool optional);
void cat_with_flags(int c, const flag *f, int *prev, bool *line_printed,
                    int *index);

int main(int argc, char **argv) {
  if (argc == 1) {
    printf("INVALID OPTIONS\n");
    exit(1);
  }
  flag f;
  flag_init(&f);
  int index_myfile = 0;
  bool optional = check_flag(argc, argv, &f, &index_myfile);
  if (optional == true && argc == 2) {
    printf("NO FILE\n");
    exit(1);
  }
  for (int i = index_myfile; i < argc; i++) {
    cat(argv[i], &f, optional);
  }
  return 0;
}

bool set_flag(char symbol_flag, flag *f) {
  bool answer = true;
  switch (symbol_flag) {
    case 'b':
      f->b = true;
      f->n = false;
      break;
    case 'e':
      f->e = true;
      f->v = true;
      break;
    case 'n':
      if (f->b == false) {
        f->n = true;
      }
      break;
    case 'E':
      f->e = true;
      break;
    case 's':
      f->s = true;
      break;
    case 't':
      f->t = true;
      f->v = true;
      break;
    case 'T':
      f->t = true;
      break;
    case 'v':
      f->v = true;
      break;
    default:
      answer = false;
      break;
  }
  return answer;
}

bool check_gnu_flag(const char *s, flag *f) {
  bool answer = false;
  if (strcmp(s, "number-nonblank") == 0) {
    f->b = true;
    answer = true;
  } else if (strcmp(s, "number") == 0) {
    f->n = true;
    answer = true;
  } else if (strcmp(s, "squeeze-blank") == 0) {
    f->s = true;
    answer = true;
  }
  return answer;
}

bool check_flag(int argc, char **argv, flag *f, int *index_myfile) {
  bool answer = false;
  bool check_legal = false;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      check_legal = true;
      if (argv[i][1] == '-') {
        answer = check_gnu_flag(&argv[i][2], f);
      } else {
        char *ptr = &argv[i][1];
        while (*ptr != '\0') {
          answer = set_flag(*ptr, f);
          ptr++;
        }
      }
    } else {
      *index_myfile = i;
      break;
    }
  }
  if (check_legal != answer) {
    printf("INVALID FLAG\n");
    exit(1);
  }
  return answer;
}

void cat(const char *myfile, const flag *f, bool optional) {
  FILE *fp;
  fp = fopen(myfile, "rt");
  if (fp == NULL) {
    printf("INVALID FILE:%s\n", myfile);
    exit(1);
  }
  int index = 1;
  int prev = '\n';
  bool line_printed = false;
  int c = fgetc(fp);
  if (optional == false) {
    while (c != EOF) {
      putc(c, stdout);
      c = fgetc(fp);
    }
    fclose(fp);
  } else if (optional == true) {
    while (c != EOF) {
      cat_with_flags(c, f, &prev, &line_printed, &index);
      c = fgetc(fp);
    }
    // fclose(fp);
  }
  fclose(fp);
}

void cat_with_flags(int c, const flag *f, int *prev, bool *line_printed,
                    int *index) {
  if (!((f->s == true) && (c == '\n') && (*prev == '\n') &&
        (*line_printed == true))) {
    if ((*prev == '\n') && (c == '\n'))
      *line_printed = true;
    else
      *line_printed = false;

    if ((f->n) && (*prev == '\n')) {
      printf("%6d\t", *index);
      *index += 1;
    }

    if (f->b == true && (c != '\n') && (*prev == '\n')) {
      printf("%6d\t", *index);
      *index += 1;
    }

    if ((f->t == true) && (c == '\t')) {
      printf("^");
      c = '\t' + 64;
    }

    if ((f->e == true) && (c == '\n')) {
      printf("$");
    }

    if (f->v == true) {
      if ((c >= 126) && (c <= 159)) {
        printf("M-^");
        c = c - 128 + 64;
      }
      if (((c <= 31) && (c >= 0) && (c != '\n') && (c != '\t')) || c == 127) {
        printf("^");
        c = c + 64;
      }
    }

    putc(c, stdout);
  }
  *prev = c;
}