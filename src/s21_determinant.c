#include "s21_matrix.h"

int s21_determinant(s21_matrix *A, double *result) {
  if (s21_validate_matrix(A) != 0 || result == NULL) {
    return 1;
  }

  if (A->rows != A->columns) {
    return 2;
  }

  if (A->rows == 1) {
    *result = A->matrix[0][0];
    return 0;
  }

  if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    return 0;
  }

  double det = 0;

  for (int j = 0; j < A->columns; j++) {
    s21_matrix minor;
    double minor_det = 0;

    if (s21_minor_matrix(A, 0, j, &minor) != 0) {
      return 1;
    }

    if (s21_determinant(&minor, &minor_det) != 0) {
      s21_remove_matrix(&minor);
      return 1;
    }

    if (j % 2 == 0) {
      det += A->matrix[0][j] * minor_det;

    } else {
      det -= A->matrix[0][j] * minor_det;
    }

    s21_remove_matrix(&minor);
  }

  *result = det;
  return 0;
}
