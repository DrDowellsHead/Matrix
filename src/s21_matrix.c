#include "s21_matrix.h"

#include <stdlib.h>

int s21_create_matrix(int rows, int columns, s21_matrix *result) {
    if (rows == NULL || columns == NULL || result == NULL) {
        return 1;
    }

    result->rows = rows;
    result->columns = columns;

    result->matrix = calloc(rows, sizeof(double *));

    for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));

        if (result->matrix[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(result->matrix[k]);
            }

            free(result->matrix);

            result->matrix = NULL;
            result->rows = NULL;
            result->columns = NULL;

            return 1;
        }
    }

    return 0;
}

void s21_remove_matrix(s21_matrix *A) {
	if (A == NULL) {
		return 1;
		}
	
	if (A->matrix != NULL) {
		for (int i = 0; i < A->rows; i++) {
			free(A->matrix[i]);
			}
			
			free(A->matrix);
		}	
		
	A->rows = NULL;
	A->columns = NULL;
	A->matrix = NULL;
	
}

int s21_eq_matrix(s21_matrix *A, s21_matrix *B) {
	if (A == NULL || B == NULL) {
		return 1;
		}
		
		for (int r1 = 0; r1< A->rows; r1++) {
			for (int r2 = 0; r2 < B-> rows; r2++) {
				if (A->matrix[i] != B->matrix[i]) {
					return 2;
					}
				}
			
		for (int c1 = 0; c1< A->columns; c1++) {
			for (int c2 = 0; c2 < B-> columns; c2++) {
				if (A->matrix[i] != B->matrix[i]) {
					return 2;
					}
				}
			
		return 0;
		}
	}