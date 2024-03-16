#include "s21_matrix.h"

int s21_matrix_check(matrix_t *A) {
  if (A) {
    if (A->rows <= 0 || A->columns <= 0 || !A->matrix)
      return 0;
    else
      return 1;
  } else
    return 0;
}

int s21_inf_nan_check(matrix_t *A) {
  int status = SUCCESS;
  for (int i = 0; i < A->rows && status == SUCCESS; i++) {
    for (int j = 0; j < A->columns && status == SUCCESS; j++) {
      if (isinf(A->matrix[i][j]) || isnan(A->matrix[i][j])) status = FAILURE;
    }
  }
  return status;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || !result) return 1;

  int status = 0;

  result->rows = rows;
  result->columns = columns;
  result->matrix = calloc(rows, sizeof(double *));

  if (result->matrix) {
    for (int i = 0; i < rows && status == 0; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
      if (!result->matrix[i]) status = 1;
    }
  } else {
    status = 1;
  }

  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->rows > 0 && A->columns > 0 && A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) free(A->matrix[i]);
    }

    if (A->matrix) free(A->matrix);
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!s21_matrix_check(A) || !s21_matrix_check(B)) return FAILURE;
  int status = SUCCESS;

  if (A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows && status == SUCCESS; i++) {
      for (int j = 0; j < A->columns && status == SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) status = FAILURE;
      }
    }
  } else
    status = FAILURE;
  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_matrix_check(A) || !s21_matrix_check(B)) return 1;
  if (!s21_inf_nan_check(A) || !s21_inf_nan_check(B)) return 2;
  if (A->columns == B->columns && A->rows == B->rows) {
    if (s21_create_matrix(A->rows, A->columns, result) != 0) {
      return 1;
    }
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else
    return 2;

  return 0;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_matrix_check(A) || !s21_matrix_check(B)) return 1;
  if (!s21_inf_nan_check(A) || !s21_inf_nan_check(B)) return 2;
  if (A->columns == B->columns && A->rows == B->rows) {
    if (s21_create_matrix(A->rows, A->columns, result) != 0) {
      return 1;
    }
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  } else
    return 2;

  return 0;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!s21_matrix_check(A)) return 1;
  if (!s21_inf_nan_check(A)) return 2;
  if (s21_create_matrix(A->rows, A->columns, result) != 0) {
    return 1;
  }
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return 0;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_matrix_check(A) || !s21_matrix_check(B)) return 1;
  if (!s21_inf_nan_check(A) || !s21_inf_nan_check(B)) return 2;
  if (A->columns == B->rows) {
    if (s21_create_matrix(A->rows, B->columns, result) != 0) {
      return 1;
    }
    for (int i = 0; i < result->rows; ++i) {
      for (int j = 0; j < result->columns; ++j) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; ++k) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  } else
    return 2;
  return 0;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!s21_matrix_check(A)) return 1;
  if (!s21_inf_nan_check(A)) return 2;
  if (s21_create_matrix(A->columns, A->rows, result) != 0) {
    return 1;
  }
  for (int i = 0; i < result->rows; ++i) {
    for (int j = 0; j < result->columns; ++j) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }
  return 0;
}

int s21_determinant(matrix_t *A, double *result) {
  if (!s21_matrix_check(A)) return 1;
  if (A->columns != A->rows) return 2;

  if (A->columns == 1) {
    *result = A->matrix[0][0];
  } else if (A->columns == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    *result = s21_determinant_recursion(A);
  }

  return 0;
}

double s21_determinant_recursion(matrix_t *A) {
  if (A->columns == 2) {
    return A->matrix[0][0] * A->matrix[1][1] -
           A->matrix[0][1] * A->matrix[1][0];
  }

  double result = 0.0;
  for (int i = 0; i < A->rows; i++) {
    matrix_t temp = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
    for (int j = 0; j < A->columns; j++) {
      s21_smaller_matrix_completion(&temp, A, i, j);
      result +=
          (pow(-1.0, i)) * A->matrix[i][0] * (s21_determinant_recursion(&temp));
    }
    s21_remove_matrix(&temp);
  }

  return result;
}

void s21_smaller_matrix_completion(matrix_t *temp, matrix_t *A, int i, int j) {
  for (int k = 0; k < A->rows; k++) {
    for (int g = 0; g < A->columns; g++) {
      if (i != k && j != g) {
        if (k < i && g < j) {
          temp->matrix[k][g] = A->matrix[k][g];
        } else if (k < i && g > j) {
          temp->matrix[k][g - 1] = A->matrix[k][g];
        } else if (k > i && g < j) {
          temp->matrix[k - 1][g] = A->matrix[k][g];
        } else {
          temp->matrix[k - 1][g - 1] = A->matrix[k][g];
        }
      }
    }
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!s21_matrix_check(A) || !result) return 1;
  if (A->columns != A->rows) return 2;

  int status = 0;
  if (s21_create_matrix(A->rows, A->columns, result) != 0) {
    status = 1;
  } else {
    if (A->columns == 1) {
      result->matrix[0][0] = 1;
    } else {
      s21_calc_complements_plus(A, result, &status);
    }
  }
  return status;
}

void s21_calc_complements_plus(matrix_t *A, matrix_t *result, int *status) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (A->columns == 2) {
        result->matrix[i][j] =
            pow(-1.0, i + j) * A->matrix[(i + 1 + A->rows) % A->rows]
                                        [(j + 1 + A->columns) % A->columns];
      } else {
        matrix_t temp = {0};
        *status = s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
        if (*status == 0) {
          s21_smaller_matrix_completion(&temp, A, i, j);
          double det = 0.0;
          *status = s21_determinant(&temp, &det);
          result->matrix[i][j] = pow(-1.0, i + j) * det;
          s21_remove_matrix(&temp);
        }
      }
    }
  }
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!s21_matrix_check(A) || !result) return 1;
  if (A->columns != A->rows) return 2;

  int status = 0;
  double check = 0.0;
  status = s21_determinant(A, &check);
  if (check != 0) {
    if (A->columns == 1) {
      if (s21_create_matrix(A->rows, A->columns, result) == 0) {
        if (A->matrix[0][0]) {
          result->matrix[0][0] = 1.0 / A->matrix[0][0];
        } else {
          status = 2;
        }
      } else {
        status = 1;
      }
    } else {
      matrix_t temp = {0};
      status = s21_calc_complements(A, &temp);
      if (!status) {
        matrix_t trans = {0};
        status = s21_transpose(&temp, &trans);
        if (!status) {
          s21_mult_number(&trans, 1.0 / check, result);
        }
        s21_remove_matrix(&trans);
      }
      s21_remove_matrix(&temp);
    }
  } else {
    status = 2;
  }

  return status;
}
