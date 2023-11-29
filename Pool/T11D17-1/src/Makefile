CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -c

# Первое задание
EXECUTABLE = ../build/Quest_1
SOURCE = dmanager_module.c
OBJS = $(SOURCE:.c=.o)

door_struct: $(EXECUTABLE)

$(EXECUTABLE):$(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(FLAGS) $< -o $@


# Второе задание
EXECUTABLE2 = ../build/Quest_2
SOURCE2 = list_test.c list.c
OBJS2 = $(SOURCE2:.c=.o)

list_test: list_test.o list.o
	$(CC) $^ -o $(EXECUTABLE2)

list_test.o:
	$(CC) $(FLAGS) list_test.c -o list_test.o

test.o:
	$(CC) $(FLAGS) test.c -o test.o


# Третье задание
EXECUTABLE3 = ../build/Quest_3
SOURCE3 = stack_test.c stack.c
OBJS3 = $(SOURCE3:.c=.o)

stack_test: stack_test.o stack.o
	$(CC) $^ -o $(EXECUTABLE3)

stack_test.o:
	$(CC) $(FLAGS) stack_test.c -o stack_test.o

stack.o:
	$(CC) $(FLAGS) stack.c -o stack.o

# Очистка
clean:
	rm -rf $(OBJS) $(OBJS2) $(OBJS3)