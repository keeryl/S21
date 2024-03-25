CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: s21_cat cppcheck lint lint-errors

s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

test: cppcheck lint lint-errors
	$(CC) $(CFLAGS) s21_cat.test.c -o test
	./test
	rm test

rebuild: clean all

clean:
	rm s21_cat

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