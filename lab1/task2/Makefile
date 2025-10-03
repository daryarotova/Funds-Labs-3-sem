CC=gcc
CFLAGS= -Wall -Werror -Wextra
CLIBS= -lm

.PHONY: all test clean

# сборка

all: test_2.out

test_2.out: main_second_task.c src/primes.c
	$(CC) $(CFLAGS) main_second_task.c src/primes.c $(CLIBS) -o test_2.out

clean:
	rm -f test_2.out *.o

# тесты

test: test_2.out
	@echo "0" | ./test_2.out > /dev/null 2>&1; \
	if [ $$? -ne 0 ]; then echo "TEST 1 PASSED: Некорректное количество введенных чисел"; else echo "TEST 1 FAILED"; fi

	@echo "2\n12\nabc" | ./test_2.out > /dev/null 2>&1; \
	if [ $$? -ne 0 ]; then echo "TEST 2 PASSED: Некорректный ввод аргумента"; else echo "TEST 2 FAILED"; fi

	@output=$$(echo "3\n1\n5\n10" | ./test_2.out); \
	if echo "$$output" | grep -q "Простое число под номером 1 это: 2" && \
	   echo "$$output" | grep -q "Простое число под номером 5 это: 11" && \
	   echo "$$output" | grep -q "Простое число под номером 10 это: 29"; then \
	    echo "TEST 3 PASSED: Корректный вывод программы при правильных аргументах"; \
	else \
	    echo "TEST 3 FAILED"; \
	fi

	@echo "2\n-1\n5" | ./test_2.out > /dev/null 2>&1; \
	if [ $$? -ne 0 ]; then echo "TEST 4 PASSED: Корректный вывод программы при отрицательных аргументах"; else echo "TEST 4 FAILED"; fi

	@echo "1\n1000001" | ./test_2.out > /dev/null 2>&1; \
	if [ $$? -ne 0 ]; then echo "TEST 5 PASSED: Корректный вывод программы при слишком больших аргументах"; else echo "TEST 5 FAILED"; fi
