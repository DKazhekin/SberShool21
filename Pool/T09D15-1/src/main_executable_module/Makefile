# Выбор компилятора в переменную
CC=gcc

# Все флаги в переменную
FLAGS= -Wall -Wextra -Werror -std=c11 -c

# Файлы - источники кода в переменную
SOURCES= main_executable_module.c ../yet_another_decision_module/decision.c ../data_libs/data_io.c ../data_module/data_process.c ../data_libs/data_stat.c

# Файлы - объектные скомпилированные, просто меняем им расширение в переменную
OBJS=$(SOURCES:.c=.o)

# Исполняемый файл
EXECUTABLE=Quest_3

# Точка входа в make (устанавливаем зависимость от исполняемого файла)
all: $(EXECUTABLE)

# Правила для перевода в исполняемые файлы из объектных
$(EXECUTABLE): $(OBJS)
	$(CC) $^ -o $@

# Цикл для прохода по всем файлам .c и компиляции их в объектные файлы с флагом -c
%.o: %.c
	$(CC) $(FLAGS) $< -o $@


EXECUTABLE2=Quest_5

# Файлы за исключением data_stat.c для задания со статической библиотекой
SOURCES_STATIC_LIB = ../yet_another_decision_module/decision.c ../data_libs/data_io.c ../data_module/data_process.c
# Объектные файлы для задания со статической библиотекой
OBJS_STATIC_LIB=$(SOURCES_STATIC_LIB:.c=.o)

# Создание статической библиотеки (архива)
datastat.a:
	$(CC) $(FLAGS) ../data_libs/data_stat.c -o ../data_libs/libdata_stat.o
	ar rcs ../data_libs/libdata_stat.a ../data_libs/libdata_stat.o

build_with_static: $(EXECUTABLE2)

$(EXECUTABLE2): $(OBJS_STATIC_LIB)
	$(CC) $(FLAGS) main_executable_module.c -o main_executable_module.o
	$(CC) $^ main_executable_module.o -L../data_libs -ldata_stat -o $@

%.o: %.c
	$(CC) $(FLAGS) $< -o $@


EXECUTABLE2=Quest_6

SOURCES_DYNAMIC_LAB=../yet_another_decision_module/decision.c ../data_libs/data_io.c ../data_libs/data_stat.c
OBJS_DYNAMIC_LIB= $(SOURCES_DYNAMIC_LAB:.c=.o)

data_process.so:
	$(CC) -shared -o ../data_module/libdata_process.so ../data_module/data_process.c ../data_libs/data_stat.c

build_with_dynamic: $(EXECUTABLE2)

$(EXECUTABLE2): $(OBJS_DYNAMIC_LIB)
	$(CC) -o $@ main_executable_module.c $^ -L../data_module -ldata_process

%.o: %.c
	$(CC) $(FLAGS) $< -o $@


# Очистка
clean:
	rm -rf $(OBJS) ../data_libs/libdata_stat.a ../data_libs/libdata_stat.o ../data_module/libdata_process.so

rebuild:
	make clean
	rm -rf $(EXECUTABLE)
	make all


# $^ - подстановка всех элементов из правой части правила
# $< - подстановка первого элемента из правой части правила
# $@ - подстановка имени цели из левой части
# %.o: %.c
#	$(CC) $(FLAGS) $< -o $@ - грубо говоря, цикл в котором перебираются все .o и .c файлы, которые найдутся в Makefile (в моем случае они находятся в переменной SOURCES и OBJS)