#include "s21_matrix.h"

int s21_sum_matrix(s21_matrix *A, s21_matrix *B, s21_matrix *result) {
    if (A->matrix == NULL || B->matrix == NULL) {
        return 1;
    }

    if (s21_eq_matrix(A, B)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                A->matrix[i][j];
            }
            return 0;
        }

        for (int i = 0; i < B->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
            }
            return 0;
        }

        result = A->matrix[i,j] + B->matrix[i,j];

        if (result == NULL) {
            return 1;
        }

        return result;
    }
    return 0;
}