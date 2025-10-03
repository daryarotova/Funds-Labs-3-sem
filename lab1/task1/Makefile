CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -fsanitize=address
CLIBS = -lm

# исходники
SRCS = main_first_task.c functions.c
TARGET = task_1.a

# файлы теста
TEST_SRC = test_1.c
TEST_TARGET = test_task_1.a

.PHONY: all run demo test clean

# цель
all: $(TARGET) $(TEST_TARGET)

# сборка основной программы
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(CLIBS)

# сборка тестов
$(TEST_TARGET): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(CLIBS)

# запуск программы с примером
run: $(TARGET)
	./$(TARGET) 10 -h

# выполнение программы
demo: $(TARGET)
	@echo "Выполнение программы"
	@./$(TARGET) 25 -h
	@./$(TARGET) 17 -p
	@./$(TARGET) 255 -s
	@./$(TARGET) 3 -e
	@./$(TARGET) 50 -a
	@./$(TARGET) 7 -f

# запуск тестов
test: $(TEST_TARGET) $(TARGET)
	@./$(TEST_TARGET)

# очистка
clean:
	rm -f $(TARGET) $(TEST_TARGET)
