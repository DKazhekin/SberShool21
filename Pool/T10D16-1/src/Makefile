CC = gcc
FLAGS = -Werror -Wextra -Wall -std=c11 -c

EXECUTABLE = ../build/Quest_1
EXECUTABLE2 = ../build/Quest_2
EXECUTABLE3 = ../build/Quest_3
EXECUTABLE4 = ../build/Quest_4
EXECUTABLE5 = ../build/Quest_5
EXECUTABLE6 = ../build/Quest_6
EXECUTABLE7 = ../build/Quest_7

SOURCES = s21_string.c s21_string_test.c
OBJS = $(SOURCES:.c=.o)

strlen_test: $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(FLAGS) $< -o $@



strcmp_tests: $(EXECUTABLE2) clean

$(EXECUTABLE2): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(FLAGS) $< -o $@



strcpy_tests: $(EXECUTABLE3) clean

$(EXECUTABLE3): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(FLAGS) $< -o $@


strcat_tests: $(EXECUTABLE4) clean

$(EXECUTABLE4): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(FLAGS) $< -o $@

strchr_tests: $(EXECUTABLE5) clean

$(EXECUTABLE5): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(FLAGS) $< -o $@

strstr_tests: $(EXECUTABLE6) clean

$(EXECUTABLE6): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(FLAGS) $< -o $@


strtok_tests: $(EXECUTABLE7) clean

$(EXECUTABLE7): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(FLAGS) $< -o $@

clean:
	rm -rf $(OBJS)