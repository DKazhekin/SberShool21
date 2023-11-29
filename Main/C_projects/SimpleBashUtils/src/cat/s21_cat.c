#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SIZE 1024

typedef struct info {
  int _b;
  int _e;
  int _n;
  int _s;
  int _t;
  int _v;
  int E;
  int T;
  FILE *fd;
} info;

void number_nonblank(char *string, int *num, uint64_t *number_length);
int parse_flags(int argc, char **argv, info *x, int *pos);
void replace_endl(char *string);
void replace_tab(char *string, info *x, uint64_t number_length);
void squeeze(char *string, int *flag);
int is_empty_line(char *string);
void number_all(char *string, int *num, uint64_t *number_length);

int main(int argc, char **argv) {
  info x = {0, 0, 0, 0, 0, 0, 0, 0, NULL};
  int pos = 0, flag = 0, line_number = 0;
  uint64_t number_length = 0;
  if (!parse_flags(argc, argv, &x, &pos)) {
    return 1;
  }
  char string[SIZE];
  memset(string, '\0', SIZE);
  for (int i = pos; i < argc; i++) {
    x.fd = fopen(argv[i], "r");
    if (!x.fd) {
      printf("There is no such file: %s", argv[i]);
      return 1;
    }
    while (x.fd != NULL && fgets(string, sizeof(string), x.fd) != NULL) {
      if (x._b == 1 && x._n == 0) {
        number_nonblank(string, &line_number, &number_length);
      }
      if (x._s == 1 && x._n == 1) {
        number_nonblank(string, &line_number, &number_length);
      }
      if (x._s == 1) {
        squeeze(string, &flag);
      }
      if (x._n == 1 && x._s == 0) {
        number_all(string, &line_number, &number_length);
      }
      if ((x._e == 1) || x.E == 1) {
        replace_endl(string);
      }
      if ((x._t == 1) || x.T == 1) {
        replace_tab(string, &x, number_length);
      }
      printf("%s", string);
      memset(string, '\0', SIZE);
      number_length = 0;
    }
    fclose(x.fd);
    line_number = 0;
    flag = 0;
  }
}

int parse_flags(int argc, char **argv, info *x, int *pos) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-b") == 0 ||
        strcmp(argv[i], "--number-nonblank") == 0) {
      x->_b = 1;
    } else if (strcmp(argv[i], "-e") == 0) {
      x->_e = 1;
    } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
      x->_n = 1;
    } else if (strcmp(argv[i], "-s") == 0 ||
               strcmp(argv[i], "--squeeze-blank") == 0) {
      x->_s = 1;
    } else if (strcmp(argv[i], "-t") == 0) {
      x->_t = 1;
    } else if (strcmp(argv[i], "-T") == 0) {
      x->T = 1;
    } else if (strcmp(argv[i], "-E") == 0) {
      x->E = 1;
    } else if (strcmp(argv[i], "-v") == 0) {
      x->_v = 1;
    } else {
      if (argv[i][0] == '-') {
        for (int j = 1; j < (int)strlen(argv[i]); j++) {
          if (argv[i][j] == 'b') {
            x->_b = 1;
          } else if (argv[i][j] == 'e') {
            x->_e = 1;
          } else if (argv[i][j] == 'n') {
            x->_n = 1;
          } else if (argv[i][j] == 's') {
            x->_s = 1;
          } else if (argv[i][j] == 't') {
            x->_t = 1;
          } else if (argv[i][j] == 'v') {
            x->_v = 1;
          } else if (argv[i][j] == 'E') {
            x->E = 1;
          } else if (argv[i][j] == 'T') {
            x->T = 1;
          } else {
            printf("Error! Wrong argument!");
            return 0;
          }
        }
      } else {
        *pos = i;
        break;
      }
    }
  }
  return 1;
}

void replace_endl(char *string) {
  for (int i = 0; i < (int)strlen(string); i++) {
    if (string[i] == '\n') {
      string[i] = '$';
      string[i + 1] = '\n';
      break;
    }
  }
}

int is_empty_line(char *string) { return strlen(string) == 1; }

void replace_tab(char *string, info *x, uint64_t number_length) {
  char tmp[SIZE];
  memset(tmp, '\0', sizeof(tmp));
  int j = 0;
  for (int i = 0; i < (int)strlen(string); i++) {
    if ((x->_n == 1 || x->_b) && i == 0) {
      memcpy(tmp, string, number_length + 2);
      i = (int)number_length + 2;
    }
    if (string[i] == '\t') {
      tmp[i + j] = '^';
      j++;
      tmp[i + j] = 'I';
    } else {
      tmp[i + j] = string[i];
    }
  }
  strcpy(string, tmp);
  memset(tmp, '\0', sizeof(tmp));
}

void squeeze(char *string, int *flag) {
  if (is_empty_line(string) && (*flag == 0)) {
    *flag = 1;
  } else if (is_empty_line(string) && (*flag == 1)) {
    memset(string, '\0', SIZE);
  } else if (is_empty_line(string) == 0) {
    *flag = 0;
  }
}

void number_nonblank(char *string, int *num, uint64_t *number_length) {
  if (is_empty_line(string) == 0) {
    *num = *num + 1;
    char number[SIZE];
    memset(number, '\0', SIZE);
    sprintf(number, "%6d\t", *num);
    strcat(number, string);
    strcpy(string, number);
    *number_length = strlen(number);
  }
}

void number_all(char *string, int *num, uint64_t *number_length) {
  *num = *num + 1;
  char number[SIZE];
  memset(number, '\0', SIZE);
  sprintf(number, "%6d\t", *num);
  strcat(number, string);
  strcpy(string, number);
  *number_length = strlen(number);
}