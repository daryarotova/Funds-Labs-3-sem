CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
INCLUDE = -Iinclude
SOURCES = src/functions.c src/number_e.c src/number_pi.c src/number_ln2.c src/number_sqrt2.c src/number_gamma.c main.c
TARGET = math.out
LIBS = -lm

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCES) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	@echo "Тесты:"
	@FAILED=0; \
	EPS=0.00000001; \
	\
	check() { \
		VAL=$$(./$(TARGET) | grep "$$1" | awk -F',' '{print $$1}' | awk '{print $$3}'); \
		CONST=$$2; \
		DIFF=$$(echo "$$VAL - $$CONST" | bc -l | sed 's/-//'); \
		COMP=$$(echo "$$DIFF < $$EPS" | bc -l); \
		if [ "$$COMP" -eq 1 ]; then \
			echo "$$1: OK"; \
		else \
			echo "$$1: FAILED (получено $$VAL, константа - $$CONST)"; \
			FAILED=1; \
		fi; \
	}; \
	\
	check "Число е" 2.7182818284; \
	check "Число Пи" 3.1415926535; \
	check "Число ln(2)" 0.6931471806; \
	check "Число sqrt(2)" 1.4142135623; \
	check "Число gamma" 0.5772156649; \
	\
	if [ $$FAILED -eq 0 ]; then \
		echo "Все тесты пройдены!"; \
	else \
		echo "Некоторые тесты не пройдены."; \
	fi
