#include "s21_matrix.h"

int s21_mult_matrix(s21_matrix *A, s21_matrix *B, s21_matrix *result) {
	if (s21_validate_matrix(A) != 0 || s21_validate_matrix(B) != 0 || result == NULL) {
		return 1;
	}

	if (A->columns != B->rows) {
		return 2;
	}
	
	if (s21_create_matrix(A->rows, B->columns, result) != 0) {
		return 1;
	}

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
			double sum = 0;

			for (int k = 0; k < A->columns; k++) {
				sum += A->matrix[i][k] * B->matrix[k][j];
			}

			result->matrix[i][j] = sum;
        }
    }
	
	return 0;
}