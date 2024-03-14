SAN = -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector
W = -Wall -Werror -Wextra
FLAGS = -std=c11
GCC = gcc
LIBS = -lcheck
GCOV = --coverage
SOURCE = arithmetic_operations/*.c other/*.c
HEADERS = *.h arithmetic_operations/*.h other/*.h

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS += -lsubunit
endif

all: clean s21_decimal.a test gcov_report 
	
check: lint-fix lint-errors

clean:
	rm -rf *.o *.a *.out *.gcno *.gcda *.info report/

s21_decimal.o:
	${GCC} ${FLAGS} ${W} -c ${SOURCE}

s21_decimal.a: s21_decimal.o
	ar rcs s21_decimal.a *.o

brew:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

gcov_report:
	${GCC} ${FLAGS} ${W} ${GCOV} ${LIBS} *.c ${SOURCE} -o test.out
	./test.out
	lcov -t "gcov_report" -o test_coverage.info -c -d .
	genhtml -o report test_coverage.info
	open report/index.html
	rm -f *.o *.a *.out *.gcno *.gcda *.info /report

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c ${SOURCE}

lint-fix:
	clang-format -i -style=Google *.c ${SOURCE} ${HEADERS}

lint-errors:
	clang-format -n -style=Google *.c ${SOURCE} ${HEADERS}

test: lint-fix lint-errors cppcheck
# ${GCC} ${FLAGS} ${W} ${SAN} *.c ${SOURCE} -lcheck -o test.out
	${GCC} ${FLAGS} ${W} *.c ${SOURCE} -lcheck -o test.out
	./test.out
	rm -rf *.o *.a *.out