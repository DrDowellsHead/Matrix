#include "s21_matrix.h"

int s21_calc_complements(s21_matrix *A, s21_matrix *result) {
  if (s21_validate_matrix(A) != 0 || result == NULL) {
    return 1;
  }

  if (A->rows != A->columns) {
    return 2;
  }

  /* LCOV_EXCL_START */
  if (s21_create_matrix(A->rows, A->columns, result) != 0) {
    return 1;
  }
  /* LCOV_EXCL_STOP */

  if (A->rows == 1) {
    result->matrix[0][0] = 1;
    return 0;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      s21_matrix minor;
      double det = 0;

      /* LCOV_EXCL_START */
      if (s21_minor_matrix(A, i, j, &minor) != 0) {
        s21_remove_matrix(result);
        return 1;
      }
      /* LCOV_EXCL_STOP */

      /* LCOV_EXCL_START */
      if (s21_determinant(&minor, &det) != 0) {
        s21_remove_matrix(&minor);
        s21_remove_matrix(result);
        return 1;
      }
      /* LCOV_EXCL_STOP */

      if ((i + j) % 2 == 0) {
        result->matrix[i][j] = det;
      } else {
        result->matrix[i][j] = -det;
      }

      s21_remove_matrix(&minor);
    }
  }

  return 0;
}