SAN = -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector
W = -Wall -Werror -Wextra
FLAGS = -std=c11
GCC = gcc
LIBS = $(shell pkg-config --libs --cflags check)
GCOV = --coverage
SOURCE = s21_matrix.c helpers.c
HEADERS = *.h
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIBS += -lsubunit
endif

all: clean check s21_matrix.a test gcov_report

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

lint-fix:
	clang-format -i -style=Google *.c ${HEADERS}

lint-err:
	clang-format -n -style=Google *.c ${HEADERS}
	
check: cppcheck lint-fix lint-err

clean:
	rm -rf *.o *.a *.out *.gcno *.gcda *.info report/

s21_matrix.o:
	${GCC} ${FLAGS} ${W} -c ${SOURCE}

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a *.o

brew:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

gcov_report:
	${GCC} ${FLAGS} ${W} ${GCOV} s21_matrix.test.c ${SOURCE} ${LIBS} -o test.out
	./test.out
	lcov -t "gcov_report" -o test_coverage.info -c -d .
	genhtml -o report test_coverage.info
	open report/index.html
	rm -f *.o *.a *.out *.gcno *.gcda *.info

leaks_check:
	${GCC} ${FLAGS} ${W} *.c $(LIBS) -o test.out
	leaks -atExit -- ./test.out

sanitize_check: clean
	${GCC} ${FLAGS} ${W} ${SAN} *.c $(LIBS) -o test.out
	./test.out

test: check
	${GCC} ${FLAGS} ${W} *.c $(LIBS) -o test.out
	./test.out

test_static: check s21_matrix.a
	${GCC} ${FLAGS} ${W} s21_matrix.test.c s21_matrix.a $(LIBS) -o test.out
	./test.out