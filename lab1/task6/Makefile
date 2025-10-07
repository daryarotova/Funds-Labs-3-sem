CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
INCLUDE = -Iinclude
SOURCES = src/functions.c src/validate.c main.c
TARGET = main.out

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCES) -o $(TARGET) -lm

clean:
	rm -f $(TARGET) *.tmp

.PHONY: clean test

test: $(TARGET)
	@echo "Тесты:"
	@# Тест 1: корректный epsilon
	@./$(TARGET) 0.0001 > output.tmp 2>&1; \
	if grep -q "Первый интеграл" output.tmp && grep -q "Второй интеграл" output.tmp; then \
		echo "Тест с epsilon=0.0001: OK"; \
	else \
		echo "Тест с epsilon=0.0001: FAILED"; \
	fi

	@# Тест 2: некорректный аргумент
	@./$(TARGET) abc > output.tmp 2>&1; \
	if grep -q "Введите вещественное число" output.tmp; then \
		echo "Тест с epsilon=abc: OK"; \
	else \
		echo "Тест с epsilon=abc: FAILED"; \
	fi

	@# Тест 3: отрицательный epsilon
	@./$(TARGET) -0.1 > output.tmp 2>&1; \
	if grep -q "Эпсилон должен быть положительным числом" output.tmp; then \
		echo "Тест с epsilon=-0.1: OK"; \
	else \
		echo "Тест с epsilon=-0.1: FAILED"; \
	fi

	@# Тест 4: слишком большое epsilon
	@./$(TARGET) 0.9 > output.tmp 2>&1; \
	if grep -q "Первый интеграл" output.tmp; then \
		echo "Тест с epsilon=0.9: OK"; \
	else \
		echo "Тест с epsilon=0.9: FAILED"; \
	fi

	@rm -f output.tmp
