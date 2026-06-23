#include "s21_matrix.h"

int s21_minor_matrix(s21_matrix *A, int excluded_row, int excluded_col,
                     s21_matrix *result) {
    if (s21_validate_matrix(A) != 0 || result == NULL) {
        return 1;
    }

    if (A->rows <= 1 || A->columns <= 1) {
        return 2;
    }

    if (s21_create_matrix(A->rows - 1, A->columns - 1, result) != 0) {
        return 1;
    }

    if (excluded_row < 0 || excluded_row >= A->rows || excluded_col < 0 ||
        excluded_col >= A->columns) {
        return 2;
    }

    int minor_i = 0;

    for (int i = 0; i < A->rows; i++) {
        if (i == excluded_row) {
            continue;
        }

        int minor_j = 0;

        for (int j = 0; j < A->columns; j++) {
            if (j == excluded_col) {
                continue;
            }

            result->matrix[minor_i][minor_j] = A->matrix[i][j];
            minor_j++;
        }

        minor_i++;
    }

    return 0;
}