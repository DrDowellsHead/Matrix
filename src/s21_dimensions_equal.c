#include "s21_matrix.h"

bool s21_dimensions_equal(s21_matrix *A, s21_matrix *B) {
  if (A == NULL || B == NULL) {
    return false;
  }

  return (A->rows == B->rows) && (A->columns == B->columns);
}