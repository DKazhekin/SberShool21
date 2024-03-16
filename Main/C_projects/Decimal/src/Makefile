WWW = -std=c11 -Wall -Werror -Wextra
OS := $(shell uname)

ifeq ($(OS),Linux)
	CHFLAGS = -lcheck -lm -lpthread -lrt -lsubunit
else
	CHFLAGS = -lcheck -lm -lpthread
endif

all: clean s21_decimal.a

s21_decimal.a: s21_decimal.o s21_decimal_long.o
	ar -crs s21_decimal.a s21_decimal.o s21_decimal_long.o

s21_decimal.o: s21_decimal.c s21_decimal.h
	gcc $(WWW) -c s21_decimal.c

s21_decimal_long.o: s21_decimal_long.c s21_decimal_long.h
	gcc $(WWW) -c s21_decimal_long.c

unit-test.o: unit-test.c
	gcc $(WWW) -c unit-test.c

test: clean s21_decimal.a
	gcc $(WWW) unit-test.c s21_decimal.a $(CHFLAGS) -o unit-test
	./unit-test

gcov_report:
	gcc --coverage -lcheck -lm unit-test.c s21_decimal.c s21_decimal_long.c -o ./gcov
	./gcov
	lcov -t "./gcov" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html
	rm -rf *.gcno *gcda *.gcov


clean:
	rm -rf *.o *.a unit-test
	rm -rf *.gcno *gcda *.gcov gcov program
	rm -rf report report.info

