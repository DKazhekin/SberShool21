LIBS_LINUX=
ADD_LIB=
LIBNAME=

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)

	ADD_LIB= -l:s21_matrix.a
	LIBNAME= s21_matrix.a

	Linux_type := $(shell cat /etc/issue | sed -n '1p' | awk '{print $$1}')

	ifeq ($(Linux_type), Arch)
		LIBS_LINUX = -lm
	endif

	ifeq ($(Linux_type), Ubuntu)
		LIBS_LINUX = -lsubunit -lm -pthread -lrt
	endif

	ifeq ($(Linux_type), Debian)
		LIBS_LINUX = -lsubunit -lm -pthread -lrt
	endif

endif

ifeq ($(UNAME_S), Darwin)
    ADD_LIB= -ls21_matrix
	LIBNAME= libs21_matrix.a
endif

CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -g

OBJS=s21*.o
SRCS_OBJ=s21*.c
TESTS_OBJ=*.c

TARGET=s21_matrix
TEST_TARG=test_s21_matrix

SRCS_DIR=./
TESTS_DIR=tests

SRCS_H =s21*.h

LIBS = -lcheck $(LIBS_LINUX)


ALL_SRC_OBJ = $(shell find $(SRCS_DIR) -type f -name "$(SRCS_OBJ)")
ALL_TESTS_OBJ = $(shell find $(TESTS_DIR) -type f -name "$(TESTS_OBJ)")

ALL_SRC_H = $(shell find -type f -name "$(SRCS_H)")
ALL_TESTS_H = $(shell find $(TESTS_DIR) -type f -name "*.h")


all: s21_matrix.a test gcov_report

s21_matrix.a:
	$(CC) $(CFLAGS) $(ALL_SRC_OBJ) -c
	ar rsc $(LIBNAME) $(OBJS)
	ranlib $(LIBNAME)
	rm -f $(OBJS)

test: s21_matrix.a
	$(CC) $(CFLAGS) $(ALL_TESTS_OBJ) $(LIBS) -L. $(ADD_LIB) -o $(TEST_TARG)
	./$(TEST_TARG)

test_val: s21_matrix.a test
	valgrind --tool=memcheck --leak-check=yes -s ./$(TEST_TARG)

gcov_report: 
	$(CC) --coverage $(CFLAGS) $(ALL_SRC_OBJ) $(ALL_TESTS_OBJ) $(LIBS) -o $(TEST_TARG)
	./$(TEST_TARG)
	lcov -t "$(TEST_TARG)" -o $(TEST_TARG).info -c -d .
	genhtml -o report $(TEST_TARG).info
	rm -f *.gcda *.gcno *.info $(TEST_TARG)

clean:
	rm -f *.[oa]
	rm -f *.gcno *.gcda *.info *.gcov $(TEST_TARG)
	rm -f $(TEST_TARG)
	rm -rf report *.dSYM

rebuild: clean all
