CC = gcc
FLAGS = -Werror -Wextra -Wall -std=c11 -c
OBJS = state_sort.o ../build/Quest_1 ../build/Quest_2 state_search.o clear_state.o ../build/Quest_3
BUILD = ../build/

all: state_sort state_search clear_state

state_sort: state_sort.o
	$(CC) $< -o $(BUILD)Quest_1

state_search: state_search.o
	$(CC) $< -o $(BUILD)Quest_2

clear_state: clear_state.o
	$(CC) $< -o $(BUILD)Quest_3

clear_state.o:
	$(CC) $(FLAGS) clear_state.c -o $@

state_search.o:
	$(CC) $(FLAGS) state_search.c -o $@

state_sort.o:
	$(CC) $(FLAGS) state_sort.c -o $@

clean:
	rm -rf $(OBJS)