CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

OS := $(shell uname)

ifeq ($(OS), Darwin)
	CHECK_FLAGS = -lcheck
else
	CHECK_FLAGS = -lcheck -lsubunit -lrt -lpthread -lm
endif

SRC = s21_create_matrix.c \
      s21_remove_matrix.c \
      s21_eq_matrix.c \
      s21_sum_matrix.c \
      s21_sub_matrix.c \
      s21_mult_number.c \
      s21_mult_matrix.c \
      s21_transpose.c \
      s21_minor_matrix.c \
      s21_calc_complements.c \
      s21_determinant.c \
      s21_inverse_matrix.c \
      s21_validate_matrix.c

OBJ = $(SRC:.c=.o)

all: s21_matrix.a

s21_matrix.a: $(OBJ)
	ar rcs s21_matrix.a $(OBJ)
	ranlib s21_matrix.a

test: clean s21_matrix.a
	$(CC) $(CFLAGS) -I. tests/s21_matrix_test.c s21_matrix.a -o test $(CHECK_FLAGS)
	./test

gcov_report: clean
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -I. $(SRC) tests/s21_matrix_test.c -o test $(CHECK_FLAGS)
	./test
	lcov -t "s21_matrix" -o s21_matrix.info -c -d .
	genhtml -o report s21_matrix.info

clean:
	rm -rf *.o *.a test *.gcda *.gcno *.info report

rebuild: clean all