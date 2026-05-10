#include "s21_string.h"

int s21_mult_number(s21_matrix *A, double number, s21_matrix *result) {
	if (s21_validate_matrix(A) != 0 || s21_validate_matrix(B) != 0 || result == NULL) {
		return 1;
	}
	
	if (!s21_dimensions_equal(A, B)) {
		return 2;
	}
	
	if (s21_create_matrix(A->rows, A->columns, result) != 0) {
		return 1;
	}

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] * B->matrix[i][j];
        }
    }
	
	return 0;
}