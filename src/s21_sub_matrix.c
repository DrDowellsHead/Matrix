#include "s21_matrix.h"

int s21_sub_matrix(s21_matrix *A, s21_matrix *B, s21_matrix *result) {
    if (A == NULL || B == NULL) {
        return 1;
    }

    if (s21_eq_matrix) {
        for (int r1 = 0; r1 < A->rows; r1++) {
            for (int r2 = 0; r2 < B->rows; r2++) {

            }
        }
    }

    return 2;
}