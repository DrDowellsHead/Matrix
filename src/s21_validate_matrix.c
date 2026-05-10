#include "s21_matrix.h"

int s21_validate_matrix(s21_matrix *A) {
    if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
        return 1;
    }

    return 0;
}