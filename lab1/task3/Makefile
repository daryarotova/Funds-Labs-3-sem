CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Iinclude
TARGET = test_lab3

SOURCES = main_third_task.c src/solving.c src/outputing.c src/checking.c
OBJECTS = main_third_task.o src/solving.o src/outputing.o src/checking.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

src/main_third_task.o: main_third_task.c
	$(CC) $(CFLAGS) -c $< -o $@

src/solving.o: src/solving.c
	$(CC) $(CFLAGS) -c $< -o $@

src/outputing.o: src/outputing.c
	$(CC) $(CFLAGS) -c $< -o $@

src/checking.o: src/checking.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) src/*.o

# тесты
test_missing_args_q:
	@echo "Тест: недостаточно аргументов для -q "
	@./$(TARGET) -q 0.001 1 2 || true

test_missing_args_m:
	@echo "Тест: недостаточно аргументов для -m"
	@./$(TARGET) -m 10 || true

test_missing_args_t:
	@echo "Тест: недостаточно аргументов для -t"
	@./$(TARGET) -t 0.001 3 4 || true

test_invalid_arg_q:
	@echo "Тест: некорректный аргумент для -q"
	@./$(TARGET) -q 0.001 1 asd 2 || true

test_invalid_arg_m:
	@echo "Тест: некорректный аргумент для -m"
	@./$(TARGET) -m 12 asd || true

test_invalid_arg_t:
	@echo "Тест: некорректный аргумент для -t"
	@./$(TARGET) -t 0.001 3 4 xyz || true

test_valid_q:
	@echo "Тест: корректный ввод для -q"
	@./$(TARGET) -q 0.001 1 -3 2 || true

test_valid_m:
	@echo "Тест: корректный ввод для -m"
	@./$(TARGET) -m 10 5 || true

test_valid_t:
	@echo "Тест: корректный ввод для -t"
	@./$(TARGET) -t 0.001 3 4 5 || true

test_wrong_triangle:
	@echo "Тест: треугольник не прямоугольный"
	@./$(TARGET) -t 0.001 2 3 4 || true

test: all test_missing_args_q test_missing_args_m test_missing_args_t \
      test_invalid_arg_q test_invalid_arg_m test_invalid_arg_t \
      test_valid_q test_valid_m test_valid_t test_wrong_triangl

.PHONY: all clean test \
        test_missing_args_q test_missing_args_m test_missing_args_t \
        test_invalid_arg_q test_invalid_arg_m test_invalid_arg_t \
        test_valid_q test_valid_m test_valid_t test_wrong_triangle
