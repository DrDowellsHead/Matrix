#include "s21_matrix.h"

#include <check.h>
#include <stdlib.h>

#define EPS 1e-6

static void fill_matrix(s21_matrix *A, const double *values) {
    int index = 0;

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            A->matrix[i][j] = values[index];
            index++;
        }
    }
}

static void assert_matrix_eq_array(s21_matrix *A, const double *expected) {
    int index = 0;

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            ck_assert_double_eq_tol(A->matrix[i][j], expected[index], EPS);
            index++;
        }
    }
}

/* create_matrix */

START_TEST(test_create_matrix_valid) {
    s21_matrix A;

    int code = s21_create_matrix(2, 3, &A);

    ck_assert_int_eq(code, 0);
    ck_assert_ptr_nonnull(A.matrix);
    ck_assert_int_eq(A.rows, 2);
    ck_assert_int_eq(A.columns, 3);

    for (int i = 0; i < A.rows; i++) {
        ck_assert_ptr_nonnull(A.matrix[i]);
    }

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_invalid_rows) {
    s21_matrix A;

    int code = s21_create_matrix(0, 3, &A);

    ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_create_matrix_invalid_columns) {
    s21_matrix A;

    int code = s21_create_matrix(3, 0, &A);

    ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_create_matrix_null_result) {
    int code = s21_create_matrix(2, 2, NULL);

    ck_assert_int_eq(code, 1);
}
END_TEST

/* remove_matrix */

START_TEST(test_remove_matrix_valid) {
    s21_matrix A;

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    s21_remove_matrix(&A);

    ck_assert_ptr_null(A.matrix);
    ck_assert_int_eq(A.rows, 0);
    ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_null) { s21_remove_matrix(NULL); }
END_TEST

/* eq_matrix */

START_TEST(test_eq_matrix_equal) {
    s21_matrix A;
    s21_matrix B;

    double values[] = {1.0, 2.0, 3.0, 4.0};

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    ck_assert_int_eq(s21_create_matrix(2, 2, &B), 0);

    fill_matrix(&A, values);
    fill_matrix(&B, values);

    ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_not_equal_values) {
    s21_matrix A;
    s21_matrix B;

    double a_values[] = {1.0, 2.0, 3.0, 4.0};
    double b_values[] = {1.0, 2.0, 3.0, 5.0};

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    ck_assert_int_eq(s21_create_matrix(2, 2, &B), 0);

    fill_matrix(&A, a_values);
    fill_matrix(&B, b_values);

    ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_not_equal_size) {
    s21_matrix A;
    s21_matrix B;

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    ck_assert_int_eq(s21_create_matrix(2, 3, &B), 0);

    ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_precision_success) {
    s21_matrix A;
    s21_matrix B;

    double a_values[] = {1.0000001, 2.0, 3.0, 4.0};
    double b_values[] = {1.0000002, 2.0, 3.0, 4.0};

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    ck_assert_int_eq(s21_create_matrix(2, 2, &B), 0);

    fill_matrix(&A, a_values);
    fill_matrix(&B, b_values);

    ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_null) {
    s21_matrix A;

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);

    ck_assert_int_eq(s21_eq_matrix(&A, NULL), FAILURE);
    ck_assert_int_eq(s21_eq_matrix(NULL, &A), FAILURE);
    ck_assert_int_eq(s21_eq_matrix(NULL, NULL), FAILURE);

    s21_remove_matrix(&A);
}
END_TEST

/* sum_matrix */

START_TEST(test_sum_matrix_valid) {
    s21_matrix A;
    s21_matrix B;
    s21_matrix result;

    double a_values[] = {1.0, 2.0, 3.0, 4.0};
    double b_values[] = {10.0, 20.0, 30.0, 40.0};
    double expected[] = {11.0, 22.0, 33.0, 44.0};

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    ck_assert_int_eq(s21_create_matrix(2, 2, &B), 0);

    fill_matrix(&A, a_values);
    fill_matrix(&B, b_values);

    ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 0);
    ck_assert_int_eq(result.rows, 2);
    ck_assert_int_eq(result.columns, 2);
    assert_matrix_eq_array(&result, expected);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_size_error) {
    s21_matrix A;
    s21_matrix B;
    s21_matrix result;

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    ck_assert_int_eq(s21_create_matrix(3, 2, &B), 0);

    ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 2);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_null_result) {
    s21_matrix A;
    s21_matrix B;

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    ck_assert_int_eq(s21_create_matrix(2, 2, &B), 0);

    ck_assert_int_eq(s21_sum_matrix(&A, &B, NULL), 1);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

/* sub_matrix */

START_TEST(test_sub_matrix_valid) {
    s21_matrix A;
    s21_matrix B;
    s21_matrix result;

    double a_values[] = {10.0, 20.0, 30.0, 40.0};
    double b_values[] = {1.0, 2.0, 3.0, 4.0};
    double expected[] = {9.0, 18.0, 27.0, 36.0};

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    ck_assert_int_eq(s21_create_matrix(2, 2, &B), 0);

    fill_matrix(&A, a_values);
    fill_matrix(&B, b_values);

    ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 0);
    assert_matrix_eq_array(&result, expected);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_size_error) {
    s21_matrix A;
    s21_matrix B;
    s21_matrix result;

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    ck_assert_int_eq(s21_create_matrix(2, 3, &B), 0);

    ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 2);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

/* mult_number */

START_TEST(test_mult_number_valid) {
    s21_matrix A;
    s21_matrix result;

    double a_values[] = {1.0, -2.0, 3.5, 4.0};
    double expected[] = {2.0, -4.0, 7.0, 8.0};

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    fill_matrix(&A, a_values);

    ck_assert_int_eq(s21_mult_number(&A, 2.0, &result), 0);
    assert_matrix_eq_array(&result, expected);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_by_zero) {
    s21_matrix A;
    s21_matrix result;

    double a_values[] = {1.0, -2.0, 3.5, 4.0};
    double expected[] = {0.0, 0.0, 0.0, 0.0};

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    fill_matrix(&A, a_values);

    ck_assert_int_eq(s21_mult_number(&A, 0.0, &result), 0);
    assert_matrix_eq_array(&result, expected);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_null_result) {
    s21_matrix A;

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);

    ck_assert_int_eq(s21_mult_number(&A, 2.0, NULL), 1);

    s21_remove_matrix(&A);
}
END_TEST

/* mult_matrix */

START_TEST(test_mult_matrix_valid) {
    s21_matrix A;
    s21_matrix B;
    s21_matrix result;

    double a_values[] = {1.0, 4.0, 2.0, 5.0, 3.0, 6.0};

    double b_values[] = {1.0, -1.0, 1.0, 2.0, 3.0, 4.0};

    double expected[] = {9.0, 11.0, 17.0, 12.0, 13.0, 22.0, 15.0, 15.0, 27.0};

    ck_assert_int_eq(s21_create_matrix(3, 2, &A), 0);
    ck_assert_int_eq(s21_create_matrix(2, 3, &B), 0);

    fill_matrix(&A, a_values);
    fill_matrix(&B, b_values);

    ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), 0);
    ck_assert_int_eq(result.rows, 3);
    ck_assert_int_eq(result.columns, 3);
    assert_matrix_eq_array(&result, expected);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_matrix_size_error) {
    s21_matrix A;
    s21_matrix B;
    s21_matrix result;

    ck_assert_int_eq(s21_create_matrix(2, 3, &A), 0);
    ck_assert_int_eq(s21_create_matrix(2, 3, &B), 0);

    ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), 2);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

/* transpose */

START_TEST(test_transpose_square) {
    s21_matrix A;
    s21_matrix result;

    double a_values[] = {1.0, 2.0, 3.0, 4.0};

    double expected[] = {1.0, 3.0, 2.0, 4.0};

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    fill_matrix(&A, a_values);

    ck_assert_int_eq(s21_transpose(&A, &result), 0);
    ck_assert_int_eq(result.rows, 2);
    ck_assert_int_eq(result.columns, 2);
    assert_matrix_eq_array(&result, expected);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_rectangular) {
    s21_matrix A;
    s21_matrix result;

    double a_values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    double expected[] = {1.0, 4.0, 2.0, 5.0, 3.0, 6.0};

    ck_assert_int_eq(s21_create_matrix(2, 3, &A), 0);
    fill_matrix(&A, a_values);

    ck_assert_int_eq(s21_transpose(&A, &result), 0);
    ck_assert_int_eq(result.rows, 3);
    ck_assert_int_eq(result.columns, 2);
    assert_matrix_eq_array(&result, expected);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

/* determinant */

START_TEST(test_determinant_1x1) {
    s21_matrix A;
    double det = 0.0;

    double values[] = {5.0};

    ck_assert_int_eq(s21_create_matrix(1, 1, &A), 0);
    fill_matrix(&A, values);

    ck_assert_int_eq(s21_determinant(&A, &det), 0);
    ck_assert_double_eq_tol(det, 5.0, EPS);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2x2) {
    s21_matrix A;
    double det = 0.0;

    double values[] = {1.0, 2.0, 3.0, 4.0};

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);
    fill_matrix(&A, values);

    ck_assert_int_eq(s21_determinant(&A, &det), 0);
    ck_assert_double_eq_tol(det, -2.0, EPS);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3_zero) {
    s21_matrix A;
    double det = 0.0;

    double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

    ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);
    fill_matrix(&A, values);

    ck_assert_int_eq(s21_determinant(&A, &det), 0);
    ck_assert_double_eq_tol(det, 0.0, EPS);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3_nonzero) {
    s21_matrix A;
    double det = 0.0;

    double values[] = {2.0, 5.0, 7.0, 6.0, 3.0, 4.0, 5.0, -2.0, -3.0};

    ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);
    fill_matrix(&A, values);

    ck_assert_int_eq(s21_determinant(&A, &det), 0);
    ck_assert_double_eq_tol(det, -1.0, EPS);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_not_square) {
    s21_matrix A;
    double det = 0.0;

    ck_assert_int_eq(s21_create_matrix(2, 3, &A), 0);

    ck_assert_int_eq(s21_determinant(&A, &det), 2);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_null_result) {
    s21_matrix A;

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);

    ck_assert_int_eq(s21_determinant(&A, NULL), 1);

    s21_remove_matrix(&A);
}
END_TEST

/* calc_complements */

START_TEST(test_calc_complements_1x1) {
    s21_matrix A;
    s21_matrix result;

    double values[] = {5.0};
    double expected[] = {1.0};

    ck_assert_int_eq(s21_create_matrix(1, 1, &A), 0);
    fill_matrix(&A, values);

    ck_assert_int_eq(s21_calc_complements(&A, &result), 0);
    assert_matrix_eq_array(&result, expected);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_3x3) {
    s21_matrix A;
    s21_matrix result;

    double values[] = {1.0, 2.0, 3.0, 0.0, 4.0, 2.0, 5.0, 2.0, 1.0};

    double expected[] = {0.0, 10.0, -20.0, 4.0, -14.0, 8.0, -8.0, -2.0, 4.0};

    ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);
    fill_matrix(&A, values);

    ck_assert_int_eq(s21_calc_complements(&A, &result), 0);
    assert_matrix_eq_array(&result, expected);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_not_square) {
    s21_matrix A;
    s21_matrix result;

    ck_assert_int_eq(s21_create_matrix(2, 3, &A), 0);

    ck_assert_int_eq(s21_calc_complements(&A, &result), 2);

    s21_remove_matrix(&A);
}
END_TEST

/* inverse_matrix */

START_TEST(test_inverse_matrix_1x1) {
    s21_matrix A;
    s21_matrix result;

    double values[] = {4.0};
    double expected[] = {0.25};

    ck_assert_int_eq(s21_create_matrix(1, 1, &A), 0);
    fill_matrix(&A, values);

    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 0);
    assert_matrix_eq_array(&result, expected);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_3x3) {
    s21_matrix A;
    s21_matrix result;

    double values[] = {2.0, 5.0, 7.0, 6.0, 3.0, 4.0, 5.0, -2.0, -3.0};

    double expected[] = {1.0, -1.0, 1.0, -38.0, 41.0, -34.0, 27.0, -29.0, 24.0};

    ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);
    fill_matrix(&A, values);

    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 0);
    assert_matrix_eq_array(&result, expected);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_zero_determinant) {
    s21_matrix A;
    s21_matrix result;

    double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

    ck_assert_int_eq(s21_create_matrix(3, 3, &A), 0);
    fill_matrix(&A, values);

    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 2);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_not_square) {
    s21_matrix A;
    s21_matrix result;

    ck_assert_int_eq(s21_create_matrix(2, 3, &A), 0);

    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 2);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_null_result) {
    s21_matrix A;

    ck_assert_int_eq(s21_create_matrix(2, 2, &A), 0);

    ck_assert_int_eq(s21_inverse_matrix(&A, NULL), 1);

    s21_remove_matrix(&A);
}
END_TEST

/* Suites */

Suite *s21_create_remove_suite(void) {
    Suite *suite = suite_create("s21_create_remove");
    TCase *tc = tcase_create("create_remove");

    tcase_add_test(tc, test_create_matrix_valid);
    tcase_add_test(tc, test_create_matrix_invalid_rows);
    tcase_add_test(tc, test_create_matrix_invalid_columns);
    tcase_add_test(tc, test_create_matrix_null_result);
    tcase_add_test(tc, test_remove_matrix_valid);
    tcase_add_test(tc, test_remove_matrix_null);

    suite_add_tcase(suite, tc);
    return suite;
}

Suite *s21_eq_suite(void) {
    Suite *suite = suite_create("s21_eq_matrix");
    TCase *tc = tcase_create("eq");

    tcase_add_test(tc, test_eq_matrix_equal);
    tcase_add_test(tc, test_eq_matrix_not_equal_values);
    tcase_add_test(tc, test_eq_matrix_not_equal_size);
    tcase_add_test(tc, test_eq_matrix_precision_success);
    tcase_add_test(tc, test_eq_matrix_null);

    suite_add_tcase(suite, tc);
    return suite;
}

Suite *s21_arithmetic_suite(void) {
    Suite *suite = suite_create("s21_arithmetic");
    TCase *tc = tcase_create("arithmetic");

    tcase_add_test(tc, test_sum_matrix_valid);
    tcase_add_test(tc, test_sum_matrix_size_error);
    tcase_add_test(tc, test_sum_matrix_null_result);
    tcase_add_test(tc, test_sub_matrix_valid);
    tcase_add_test(tc, test_sub_matrix_size_error);
    tcase_add_test(tc, test_mult_number_valid);
    tcase_add_test(tc, test_mult_number_by_zero);
    tcase_add_test(tc, test_mult_number_null_result);
    tcase_add_test(tc, test_mult_matrix_valid);
    tcase_add_test(tc, test_mult_matrix_size_error);

    suite_add_tcase(suite, tc);
    return suite;
}

Suite *s21_transform_suite(void) {
    Suite *suite = suite_create("s21_transform");
    TCase *tc = tcase_create("transform");

    tcase_add_test(tc, test_transpose_square);
    tcase_add_test(tc, test_transpose_rectangular);

    suite_add_tcase(suite, tc);
    return suite;
}

Suite *s21_advanced_suite(void) {
    Suite *suite = suite_create("s21_advanced");
    TCase *tc = tcase_create("advanced");

    tcase_add_test(tc, test_determinant_1x1);
    tcase_add_test(tc, test_determinant_2x2);
    tcase_add_test(tc, test_determinant_3x3_zero);
    tcase_add_test(tc, test_determinant_3x3_nonzero);
    tcase_add_test(tc, test_determinant_not_square);
    tcase_add_test(tc, test_determinant_null_result);
    tcase_add_test(tc, test_calc_complements_1x1);
    tcase_add_test(tc, test_calc_complements_3x3);
    tcase_add_test(tc, test_calc_complements_not_square);
    tcase_add_test(tc, test_inverse_matrix_1x1);
    tcase_add_test(tc, test_inverse_matrix_3x3);
    tcase_add_test(tc, test_inverse_matrix_zero_determinant);
    tcase_add_test(tc, test_inverse_matrix_not_square);
    tcase_add_test(tc, test_inverse_matrix_null_result);

    suite_add_tcase(suite, tc);
    return suite;
}

int main(void) {
    int failed_count = 0;

    Suite *suites[] = {s21_create_remove_suite(), s21_eq_suite(),
                       s21_arithmetic_suite(),    s21_transform_suite(),
                       s21_advanced_suite(),      NULL};

    for (int i = 0; suites[i] != NULL; i++) {
        SRunner *runner = srunner_create(suites[i]);

        srunner_run_all(runner, CK_NORMAL);
        failed_count += srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    return failed_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}