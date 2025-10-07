SHELL := /bin/bash

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
INCLUDE = -Iinclude
SOURCES = main.c src/solve.c src/output.c
TARGET = main.out

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCES) -o $(TARGET) -lm

clean:
	rm -f $(TARGET) input.tmp output.tmp expected.tmp

.PHONY: clean test

test: $(TARGET)
	@echo "Проверим тесты"
	@FAILED=0; \
	echo "101 1A 0F" > input.tmp; \
	echo -e "101 2 5\n1A 11 21\nF 16 15" > expected.tmp; \
	./$(TARGET) input.tmp output.tmp; \
	if ! diff -q output.tmp expected.tmp > /dev/null; then \
		echo "Тест 1: FAILED"; \
		FAILED=1; \
	else \
		echo "Тест 1: OK"; \
	fi; \
	echo "0 0001 Z" > input.tmp; \
	echo -e "0 2 0\n1 2 1\nZ 36 35" > expected.tmp; \
	./$(TARGET) input.tmp output.tmp; \
	if ! diff -q output.tmp expected.tmp > /dev/null; then \
		echo "Тест 2: FAILED"; \
		FAILED=1; \
	else \
		echo "Тест 2: OK"; \
	fi; \
	echo "abcdef ABCDEF 10" > input.tmp; \
	echo -e "abcdef 16 11259375\nABCDEF 16 11259375\n10 2 2" > expected.tmp; \
	./$(TARGET) input.tmp output.tmp; \
	if ! diff -q output.tmp expected.tmp > /dev/null; then \
		echo "Тест 3: FAILED"; \
		FAILED=1; \
	else \
		echo "Тест 3: OK"; \
	fi; \
	if [ $$FAILED -eq 0 ]; then \
		echo "Все тесты пройдены!"; \
	else \
		echo "Некоторые тесты не прошли."; \
	fi
