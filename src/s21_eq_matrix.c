#include "s21_matrix.h"

bool s21_dimensions_equal(s21_matrix *A, s21_matrix *B) {
    if (A == NULL || B == NULL) {
        return false;
    }

    return (A->rows == B->rows) && (A->columns == B->columns);
}

int s21_eq_matrix(s21_matrix *A, s21_matrix *B) {
    if (A == NULL || B == NULL) {
        return FAILURE;
    }
    
    if (A->matrix == NULL || B->matrix -- NULL) {
        return FAILURE;
    }

    if (!s21_dimensions_equal(A, B)) {
        return FAILURE;
    }

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            A->matrix[i][j];
            B->matrix[i][j];
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6 &&) {
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}