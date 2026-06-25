#include "s21_matrix.h"

int s21_mult_number(s21_matrix *A, double number, s21_matrix *result) {
  if (s21_validate_matrix(A) != 0 || result == NULL) {
    return 1;
  }

  if (s21_create_matrix(A->rows, A->columns, result) != 0) {
    return 1;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }

  return 0;
}