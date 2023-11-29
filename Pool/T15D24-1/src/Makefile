CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11

EXECUTABLE = ../build/Quest_1

build_db:
	$(CC) $(FLAGS) master_levels.c master_modules.c master_status_events.c modules_db.c shared.c -o $(EXECUTABLE)

clean:
	rm -rf $(EXECTUTABLE)