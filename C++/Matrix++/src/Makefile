GCC= gcc -g -std=c++17
CFLAGS = -Wall -Werror -Wextra
GCOV = --coverage
LIBS = -lgtest -lstdc++
UNAME_S := $(shell uname -s)
SOURCE = s21_matrix_oop.cc

ifeq ($(UNAME_S),Linux)
	LIBS += -lsubunit
endif

all: check s21_matrix_oop.a test

clean:
	rm -rf test test* report/ *.o *.a *.out *.gcno *.gcda *.info

s21_matrix_oop.o:
	${GCC} ${CFLAGS} -c ${SOURCE}

s21_matrix_oop.a: s21_matrix_oop.o
	ar rcs s21_matrix_oop.a *.o

test: check s21_matrix_oop.a
	$(GCC) ${CFLAGS} s21_matrix_oop.test.cc s21_matrix_oop.a ${LIBS} -o test
	./test

gcov_report: check
	$(GCC) ${CFLAGS} s21_matrix_oop.test.cc ${GCOV} ${SOURCE} ${LIBS} -o test
	./test
	lcov --no-external --exclude s21_matrix_oop.test.cc --exclude s21_matrix_oop.test.h -t "gcov_report" -o test_coverage.info -c -d .
	genhtml -o report test_coverage.info
	open report/index.html
	rm -f *.o *.a *.out *.gcno *.gcda *.info

leak_test: test
	leaks -atExit -- ./test

check: style-lint lint-errors cppcheck

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.cc

lint-errors:
	clang-format -n --style=Google *.h *.cc

style-lint:
	clang-format -i --style=Google *.h *.cc