CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
INCLUDE = -Iinclude
SOURCES = src/commands.c src/flags.c src/conversion.c src/output.c main.c
TARGET = test.out

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) *.tmp

.PHONY: clean test

test: $(TARGET)
	@echo "Тесты:"
	@FAILED=0; \
	\
	# Тестовые данные \
	echo "abc 123 !" > input.tmp; \
	\
	# -d и /d \
	./$(TARGET) -d input.tmp; \
	if grep -q "ERROR" output.tmp; then FAILED=1; echo "-d: FAILED"; else echo "-d: OK"; fi; \
	./$(TARGET) /d input.tmp; \
	if grep -q "ERROR" output.tmp; then FAILED=1; echo "/d: FAILED"; else echo "/d: OK"; fi; \
	\
	# -i и /i \
	./$(TARGET) -i input.tmp; \
	if grep -q "ERROR" output.tmp; then FAILED=1; echo "-i: FAILED"; else echo "-i: OK"; fi; \
	./$(TARGET) /i input.tmp; \
	if grep -q "ERROR" output.tmp; then FAILED=1; echo "/i: FAILED"; else echo "/i: OK"; fi; \
	\
	# -a и /a \
	./$(TARGET) -a input.tmp; \
	if [ $$? -eq 0 ]; then echo "-a: OK"; else FAILED=1; echo "-a: FAILED"; fi; \
	./$(TARGET) /a input.tmp; \
	if [ $$? -eq 0 ]; then echo "/a: OK"; else FAILED=1; echo "/a: FAILED"; fi; \
	\
	# Итог \
	if [ $$FAILED -eq 0 ]; then \
		echo "Все тесты пройдены!"; \
	else \
		echo "Некоторые тесты не прошли."; \
	fi
