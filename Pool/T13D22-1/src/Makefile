CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
OBJS = cipher.o logging_cipher.o
BUILD = ../build/

cipher:
	$(CC) $(FLAGS) cipher.c logger.c -o $(BUILD)$@

logging_cipher:
	$(CC) $(FLAGS) cipher.c logger.c -o $(BUILD)$@

clean:
	rm -rf $(OBJS) $(BUILD)cipher