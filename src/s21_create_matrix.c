#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, s21_matrix *result) {
    if (rows <= 0 || columns <= 0 || result == NULL) {
        return 1;
    }

    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));

    if (result->matrix == NULL) {
        result->rows = columns;
        result->columns = 0;
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));

        if (result->matrix[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(result->matrix[k]);
            }

            free(result->matrix);

            result->matrix = NULL;
            result->rows = 0;
            result->columns = 0;

            return 1;
        }
    }

    return 0;
}