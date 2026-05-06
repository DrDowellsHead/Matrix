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