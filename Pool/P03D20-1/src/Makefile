CFLAGS=-Wall -Werror -Wextra -std=c11

all: graph.o drawing.o expression_parser.o stack_module.o polish_notation_module.o
	gcc graph.o drawing.o expression_parser.o stack_module.o polish_notation_module.o -o ../build/graph

graph.o: graph.c
	gcc $(FLAGS) -c graph.c -o graph.o

drawing.o: drawing.c
	gcc $(FLAGS) -c drawing.c -o drawing.o

expression_parser.o: expression_parser.c
	gcc $(FLAGS) -c expression_parser.c -o expression_parser.o

polish_notation_module.o: polish_notation_module.c
	gcc $(FLAGS) -c  polish_notation_module.c -o polish_notation_module.o

stack_module.o: stack_module.c
	gcc $(FLAGS) -c  stack_module.c -o stack_module.o


clean:
	rm -rf *.o *.out ../build/*

rebuild:
	make clean
	make all