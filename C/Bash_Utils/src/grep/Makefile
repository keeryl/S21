CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: s21_grep cppcheck lint lint-errors

s21_grep:
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

test: cppcheck lint lint-errors
	$(CC) $(CFLAGS) s21_grep.test.c -o test
	./test
	rm test

rebuild: clean all

clean:
	rm s21_grep

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

lint:
	clang-format -i -style=Google *.c
	clang-format -i -style=Google *.h
	clang-format -i -style=Google ../common/*.h

lint-errors:
	clang-format -n -style=Google *.c
	clang-format -n -style=Google *.h
	clang-format -n -style=Google ../common/*.h