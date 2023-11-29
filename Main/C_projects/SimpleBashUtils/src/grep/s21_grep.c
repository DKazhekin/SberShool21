#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

typedef struct info {
  int _i;
  int _v;
  int _n;
  int _c;
  int _l;
  FILE *fd;
} info;

int parse_flags(int argc, char **argv, info *helper, char **patterns,
                char **files, int *count_files);
void filling_list(char **list);
void freeing(char **list);
int iflag_(char *string, char *pattern);
void nflag_(char *string, int n);

int main(int argc, char **argv) {
  char **patterns = malloc(sizeof(char *) * 5);
  char **files = malloc(sizeof(char *) * 5);
  filling_list(patterns);
  filling_list(files);

  info helper = {0, 0, 0, 0, 0, NULL};

  int count_files = 0;
  if (!parse_flags(argc, argv, &helper, patterns, files, &count_files)) {
    return 1;
  }

  char string[SIZE];
  int file_iterator = 0, pattern_iterator;
  while (strlen(files[file_iterator]) != 0) {
    helper.fd = fopen(files[file_iterator], "r");

    if (helper.fd == NULL) {
      fclose(helper.fd);
      file_iterator++;
      continue;
    }

    int string_number = 0, count_strings = 0, count_strings_inv = 0;
    while (fgets(string, sizeof(string), helper.fd) != NULL) {
      int accept = 0;
      string_number++;
      pattern_iterator = 0;

      // Check if any patterns in the string
      while (strlen(patterns[pattern_iterator]) != 0) {
        if (helper._i == 1) {
          accept |= iflag_(string, patterns[pattern_iterator]);
        } else {
          if (strstr(string, patterns[pattern_iterator]) != NULL) {
            accept = 1;
          }
        }
        pattern_iterator++;
        // Why to wait if we are good
        if (accept == 1) {
          count_strings++;
          break;
        }
      }

      if (accept == 0) {
        count_strings_inv++;
      }
      // Mark if string is accepted and needs to be marked or its need to be
      // marked and there is inverse flag
      if ((helper._n == 1 && accept) ||
          (helper._n == 1 && helper._v == 1 && accept == 0)) {
        nflag_(string, string_number);
      }

      // Print string if flags -c -l are 0 (This is printing part if we need to
      // print the whole string)
      if (helper._c == 0 && helper._l == 0) {
        if ((accept && helper._v == 0) || (accept == 0 && helper._v == 1)) {
          count_files > 1 ? printf("%s:%s", files[file_iterator], string)
                          : printf("%s", string);
          if (string[strlen(string) - 1] != '\n') {
            printf("\n");
          }
        }
      }
    }

    // String count differs if we have -v flag (This is printing part if we need
    // to print only string count)
    if (helper._c == 1 && helper._v == 0) {
      count_files > 1 ? printf("%s:%d\n", files[file_iterator], count_strings)
                      : printf("%d\n", count_strings);
    } else if (helper._c == 1 && helper._v == 1) {
      count_files > 1
          ? printf("%s:%d\n", files[file_iterator], count_strings_inv)
          : printf("%d\n", count_strings_inv);
    }

    // Check conditions to print filename (This is printing part if we need to
    // print only filename)
    if ((helper._l == 1 && helper._v == 0 && count_strings > 0) ||
        (helper._l == 1 && helper._v == 1 && count_strings_inv > 0)) {
      printf("%s\n", files[file_iterator]);
    }

    fclose(helper.fd);
    file_iterator++;
  }
  freeing(patterns);
  freeing(files);
  return 0;
}

int parse_flags(int argc, char **argv, info *helper, char **patterns,
                char **files, int *count_files) {
  int flag = 0;
  int pattern_iterator = 0;
  int files_iterator = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0) {
      helper->_i = 1;
    } else if (strcmp(argv[i], "-v") == 0) {
      helper->_v = 1;
    } else if (strcmp(argv[i], "-n") == 0) {
      helper->_n = 1;
    } else if (strcmp(argv[i], "-c") == 0) {
      helper->_c = 1;
    } else if (strcmp(argv[i], "-l") == 0) {
      helper->_l = 1;
    } else if (strcmp(argv[i], "-e") == 0) {
      flag = 1;
    } else {
      if (argv[i][0] == '-') {
        for (int j = 1; j < (int)strlen(argv[i]); j++) {
          if (argv[i][j] == 'i') {
            helper->_i = 1;
          } else if (argv[i][j] == 'v') {
            helper->_v = 1;
          } else if (argv[i][j] == 'n') {
            helper->_n = 1;
          } else if (argv[i][j] == 'c') {
            helper->_c = 1;
          } else if (argv[i][j] == 'l') {
            helper->_l = 1;
          } else if (argv[i][j] == 'e') {
            continue;
          } else {
            printf("Wrong argument!");
            return 0;
          }
        }
      } else if (flag) {
        strcpy(patterns[pattern_iterator], argv[i]);
        pattern_iterator++;
        flag = 0;
      } else if (strlen(patterns[0]) == 0) {
        strcpy(patterns[0], argv[i]);
      } else {
        strcpy(files[files_iterator], argv[i]);
        files_iterator++;
      }
    }
  }
  *count_files = files_iterator;
  return 1;
}

void filling_list(char **list) {
  for (int i = 0; i < 5; i++) {
    char *pattern = malloc(sizeof(char) * 20);
    memset(pattern, '\0', sizeof(char) * 20);
    list[i] = pattern;
  }
}

void freeing(char **list) {
  for (int i = 0; i < 5; i++) {
    free(list[i]);
  }
  free(list);
}

int iflag_(char *string, char *pattern) {
  regex_t regex;
  int re;
  re = regcomp(&regex, pattern, REG_ICASE);
  if (re) {
    fprintf(stderr, "Could not compile regex\n");
    return 0;
  }
  re = regexec(&regex, string, 0, NULL, 0);
  if (!re) {
    regfree(&regex);
    return 1;
  } else if (re == REG_NOMATCH) {
    regfree(&regex);
    return 0;
  } else {
    printf("Error!");
    return 0;
  }
}

void nflag_(char *string, int n) {
  char tmp[SIZE];
  sprintf(tmp, "%d", n);
  strcat(tmp, ":");
  strcat(tmp, string);
  memcpy(string, tmp, SIZE);
}