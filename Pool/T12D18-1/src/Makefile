CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -c
BUILD = ../build/

EXECUTABLE1 = Quest_1
EXECUTABLE2 = Quest_2
EXECUTABLE3 = Quest_3
EXECUTABLE4 = Quest_4
EXECUTABLE5 = Quest_5
SOURCES = print_module.c main_module_entry_point.c documentation_module.c bst.c bst_create_test.c bst_insert_test.o bst_traverse_test.o
OBJS = $(SOURCES:.c=.o)

print_module: print_module.o main_module_entry_point.o documentation_module.o
	$(CC) $^ -o $(BUILD)$(EXECUTABLE1)

print_module.o:
	$(CC) $(FLAGS) print_module.c -o $@

main_module_entry_point.o:
	$(CC) $(FLAGS) main_module_entry_point.c -o $@

documentation_module: print_module.o main_module_entry_point.o documentation_module.o
	$(CC) $^ -o $(BUILD)$(EXECUTABLE2)

documentation_module.o:
	$(CC) $(FLAGS) documentation_module.c -o $@

EXECUTABLE3 = Quest_3
SOURCES2 = bst.c bst_create_test.c
OBJECTS2 = $(SOURCES2=:.c=.o)

bst_insert_test: bst.o bst_insert_test.o
	$(CC) $^ -o $(BUILD)$(EXECUTABLE4)

bst_create_test: bst.o bst_create_test.o
	$(CC) $^ -o $(BUILD)$(EXECUTABLE3)

bst_create_test.o:
	$(CC) $(FLAGS) bst_create_test.c -o $@

bst_insert_test.o:
	$(CC) $(FLAGS) bst_insert_test.c -o $@

bst.o:
	$(CC) $(FLAGS) bst.c -o $@

bst_traverse_test: bst.o bst_traverse_test.o
	$(CC) $^ -o $(BUILD)$(EXECUTABLE5)

bst_traverse_test.o:
	$(CC) $(FLAGS) bst_traverse_test.c -o $@


clean:
	rm -rf $(OBJS)

