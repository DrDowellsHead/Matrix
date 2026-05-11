#include "s21_matrix.h"

int s21_calc_complements(s21_matrix *A, s21_matrix *result) {
    if (s21_validate_matrix(A) != 0 || result == NULL) {
        return 1;
    }

    if (s21_create_matrix(A->rows - 1, A->columns - 1, result) != 0) {
        return 1;
    }

    
}