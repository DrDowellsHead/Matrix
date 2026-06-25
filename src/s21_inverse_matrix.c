#include "s21_matrix.h"

int s21_inverse_matrix(s21_matrix *A, s21_matrix *result) {
  if (s21_validate_matrix(A) != 0 || result == NULL) {
    return 1;
  }

  if (A->rows != A->columns) {
    return 2;
  }

  double det = 0;

  /* LCOV_EXCL_START */
  if (s21_determinant(A, &det) != 0) {
    return 1;
  }
  /* LCOV_EXCL_STOP */

  if (fabs(det) < 1e-6) {
    return 2;
  }

  s21_matrix complements;
  s21_matrix transposed;

  /* LCOV_EXCL_START */
  if (s21_calc_complements(A, &complements) != 0) {
    return 1;
  }
  /* LCOV_EXCL_STOP */

  /* LCOV_EXCL_START */
  if (s21_transpose(&complements, &transposed) != 0) {
    s21_remove_matrix(&complements);
    return 1;
  }
  /* LCOV_EXCL_STOP */

  /* LCOV_EXCL_START */
  if (s21_mult_number(&transposed, 1.0 / det, result) != 0) {
    s21_remove_matrix(&complements);
    s21_remove_matrix(&transposed);
    return 1;
  }
  /* LCOV_EXCL_STOP */

  s21_remove_matrix(&complements);
  s21_remove_matrix(&transposed);

  return 0;
}
