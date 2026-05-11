#include "s21_matrix.h"

int s21_transpose(s21_matrix *A, s21_matrix *result) {
    if (s21_validate_matrix(A) != 0 || result == NULL) {
        return 1;
    }

    if (s21_create_matrix(A->columns, A->rows, result) != 0) {
        return 1;
    }

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[j][i] = A->matrix[i][j];
        }
    }

    return 0;
}