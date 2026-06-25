CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

TEST_DIR = tests
GCOV_DIR = $(TEST_DIR)/gcov
TEST_BIN = $(TEST_DIR)/test
GCOV_INFO_RAW = $(TEST_DIR)/s21_matrix_raw.info
GCOV_INFO = $(TEST_DIR)/s21_matrix.info
REPORT_DIR = $(TEST_DIR)/report

GCOV_OBJ = $(addprefix $(GCOV_DIR)/, $(SRC:.c=.o))
TEST_OBJ = $(GCOV_DIR)/s21_matrix_test.o

$(GCOV_DIR):
	mkdir -p $(GCOV_DIR)

$(GCOV_DIR)/%.o: %.c | $(GCOV_DIR)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -I. -c $< -o $@

$(TEST_OBJ): $(TEST_DIR)/s21_matrix_test.c | $(GCOV_DIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

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
      s21_validate_matrix.c \
      s21_dimensions_equal.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean test gcov_report rebuild

all: s21_matrix.a

s21_matrix.a: $(OBJ)
	ar rcs s21_matrix.a $(OBJ)
	ranlib s21_matrix.a

test: clean s21_matrix.a
	$(CC) $(CFLAGS) -I. $(TEST_DIR)/s21_matrix_test.c s21_matrix.a -o $(TEST_BIN) $(CHECK_FLAGS)
	./$(TEST_BIN)

gcov_report: clean $(GCOV_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(GCOV_OBJ) $(TEST_OBJ) -o $(TEST_BIN) $(CHECK_FLAGS)
	./$(TEST_BIN)
	lcov -t "s21_matrix" -o $(GCOV_INFO) -c -d $(GCOV_DIR)
	genhtml -o $(REPORT_DIR) $(GCOV_INFO)

clean:
	rm -rf *.o *.a *.gcda *.gcno *.info report
	rm -rf $(TEST_BIN) $(GCOV_INFO_RAW) $(GCOV_INFO) $(REPORT_DIR) $(GCOV_DIR)

rebuild: clean all