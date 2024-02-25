SAN = -fsanitize=address
W = -Wall -Werror -Wextra
FLAGS = -std=c11
GCC = gcc
LIBS = -lcheck
GCOV = --coverage

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS += -lsubunit
endif

all: clean s21_decimal.a test gcov_report 
	
check: lint-fix lint-errors

clean:
	rm -rf *.o *.a *.out *.gcno *.gcda *.info report/

s21_decimal.o:
	${GCC} ${FLAGS} ${W} -c s21_decimal.c -o s21_decimal.o

s21_decimal.a: s21_decimal.o
	ar rcs s21_decimal.a s21_decimal.o

brew:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

gcov_report:
	${GCC} ${FLAGS} ${W} ${GCOV} ${LIBS} *.c arithmetic_operations/*.c -o test.out
	./test.out
	lcov -t "gcov_report" -o test_coverage.info -c -d .
	genhtml -o report test_coverage.info
	open report/index.html
	rm -f *.o *.a *.out *.gcno *.gcda *.info

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c arithmetic_operations/*.c

lint-fix:
	clang-format -i -style=Google *.c *.h arithmetic_operations/*.c

lint-errors:
	clang-format -n -style=Google *.c *.h arithmetic_operations/*.c

test: lint-fix lint-errors cppcheck
	${GCC} ${FLAGS} ${W} *.c arithmetic_operations/*.c -lcheck -o test.out
	./test.out
	rm -rf *.o *.a *.out