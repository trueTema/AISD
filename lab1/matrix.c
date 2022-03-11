#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "matrix.h"
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

matrix* matrix_create(int size, size_t datasize) {
    matrix* mat = malloc(sizeof(matrix));
    mat -> num = size;
    if (datasize == sizeof(int)) {
        mat -> Lines = malloc((int)size * sizeof(int**));
        for (int i = 0; i < size; i++) {
            mat -> Lines[i] = malloc((int)size * sizeof(int*));
        }
        mat -> m_info = InfoInit(datasize, &sum_int, &comp_int, &scal_int, &linear_comb_int, &print_int, &get_det_int);
    } else {
        mat -> Lines = malloc((int)size * sizeof(double**));
        for (int i = 0; i < size; i++) {
            mat -> Lines[i] = malloc((int)size * sizeof(double*));
        }
        mat -> m_info = InfoInit(datasize, &sum_double, &comp_double, &scal_double, &linear_comb_double, &print_double, &get_det_double);
    }
    return mat;
}

struct Info* InfoInit(size_t size, void* (*sum)(void*, void*), void* (*comp)(void*, void*), void* (*scal)(void*, void*), void* (*linear_comb)(void*, void*, void*), void (*print)(void*), void* (*get_det)(void*)) {
    struct Info* m_info = malloc(sizeof(struct Info));
    m_info -> size = size;
    m_info -> sum = sum;
    m_info -> comp = comp;
    m_info -> linear_comb = linear_comb;
    m_info -> scal = scal;
    m_info -> print = print;
    m_info -> get_det = get_det;
    return m_info;
}

void* sum_int(void* mat1, void* mat2) {
    matrix* res = matrix_create(((matrix*)mat1) -> num, ((matrix*)mat1) -> m_info -> size);
    for(int i = 0; i<((matrix*)mat1) -> num; i++) {
        for (int j = 0; j<((matrix*)mat1) -> num; j++) {
            int* cur_item = malloc(sizeof(int));
            *cur_item = (*(int*)(((matrix*)mat1) -> Lines[i][j]) + *(int*)(((matrix*)mat2) -> Lines[i][j]));
            ((matrix*)res) -> Lines[i][j] = cur_item;
        }
    }
    return res;
}
void* comp_int(void* mat1, void* mat2) {
    matrix* res = matrix_create(((matrix*)mat1) -> num, ((matrix*)mat1) -> m_info -> size);
    for(int i = 0; i<((matrix*)mat1) -> num; i++) {
        for (int j = 0; j<((matrix*)mat1) -> num; j++) {
            int* cur_item = malloc(sizeof(int));
            *cur_item = 0;
            for (int k = 0; k < ((matrix*)mat1) -> num; k++) {
                *cur_item += (*(int*)(((matrix*)mat1) -> Lines[i][k])) * (*(int*)(((matrix*)mat2) -> Lines[k][j]));
            }
            ((matrix*)res) -> Lines[i][j] = cur_item;
        }
    }
    return res;
}

void* scal_int(void* scal, void* mat) {
    matrix* res = matrix_create(((matrix*)mat) -> num, ((matrix*)mat) -> m_info -> size);
    for (int i = 0; i < ((matrix*)mat) -> num; i++) {
        for (int j = 0; j < ((matrix*)mat) -> num; j++) {
            int* cur_item = malloc(sizeof(int));
            *cur_item = *(int*)(((matrix*)mat) -> Lines[i][j]) * *(int*)scal;
            ((matrix*)res) -> Lines[i][j] = cur_item;
        }
    }
    return res;
}

void* linear_comb_int(void* num, void* coeffs, void* mat) {
    matrix* res = matrix_create(((matrix*)mat) -> num, ((matrix*)mat) -> m_info -> size);
    for (int i = 0; i < ((matrix*)mat) -> num; i++) {
        for (int j = 0; j < ((matrix*)mat) -> num; j++) {
            (res -> Lines[i][j]) = malloc(sizeof(int));
            *(int*)(res -> Lines[i][j]) = *(int*)(((matrix*)mat) -> Lines[i][j]);
        }
    }
    for (int i = 0; i < ((matrix*)mat) -> num; i++) {
        for (int j = 0; j < ((matrix*)mat) -> num; j++) {
            *(int*)(((matrix*)res) -> Lines[*(int*)num][j]) += *(int*)(((matrix*)mat) -> Lines[i][j]) * ((int*)coeffs)[i];
        }
    }
    return res;
}

void print_int(void* mat) {
    printf("= = = = = = = = = = = = \n\nМатрица:\n\n");
    for (int i = 0; i < ((matrix*)mat) -> num; i++) {
        for (int j = 0; j<((matrix*)mat) -> num; j++) {
            int cur = *(int*)(((matrix*)mat) -> Lines[i][j]);
            printf("%d\t", cur);
        }
        printf("\n");
    }
    printf("\n\n= = = = = = = = = = = = ");
}
void* enter_int(int num) {
    matrix* mat = matrix_create(num, sizeof(int));
    printf("\nВводите матрицу (%dx%d) построчно:\n\n", num, num);
    for (int i = 0; i < num; i++) {
        printf("Введите элементы %d-й строки:\n>> ", i+1);
        for (int j = 0; j< num; j++) {
            int* cur = get_int();
            if (cur) {
                mat -> Lines[i][j] = cur;
            } else {
                printf("\n<!> Некорректный параметр\n");
                return NULL;
            }
        }
    }
    return mat;
}
void* sum_double(void* mat1, void* mat2) {
    matrix* res = matrix_create(((matrix*)mat1) -> num, ((matrix*)mat1) -> m_info -> size);
    for(int i = 0; i<((matrix*)mat1) -> num; i++) {
        for (int j = 0; j<((matrix*)mat1) -> num; j++) {
            double* cur_item = malloc(sizeof(double));
            *cur_item = (*(double*)(((matrix*)mat1) -> Lines[i][j]) + *(double*)(((matrix*)mat2) -> Lines[i][j]));
            ((matrix*)res) -> Lines[i][j] = cur_item;
        }
    }
    return res;
}
void* comp_double(void* mat1, void* mat2) {
    matrix* res = matrix_create(((matrix*)mat1) -> num, ((matrix*)mat1) -> m_info -> size);
    for(int i = 0; i<((matrix*)mat1) -> num; i++) {
        for (int j = 0; j<((matrix*)mat1) -> num; j++) {
            double* cur_item = malloc(sizeof(double));
            *cur_item = 0;
            for (int k = 0; k < ((matrix*)mat1) -> num; k++) {
                *cur_item += (*(double*)(((matrix*)mat1) -> Lines[i][k])) * (*(double*)(((matrix*)mat2) -> Lines[k][j]));
            }
            ((matrix*)res) -> Lines[i][j] = cur_item;
        }
    }
    return res;
}
void* scal_double(void* scal, void* mat) {
    matrix* res = matrix_create(((matrix*)mat) -> num, ((matrix*)mat) -> m_info -> size);
    for (int i = 0; i < ((matrix*)mat) -> num; i++) {
        for (int j = 0; j < ((matrix*)mat) -> num; j++) {
            double* cur_item = malloc(sizeof(double));
            *cur_item = *(double*)(((matrix*)mat) -> Lines[i][j]) * *(double*)scal;
            ((matrix*)res) -> Lines[i][j] = cur_item;
        }
    }
    return res;
}

void* linear_comb_double(void* num, void* coeffs, void* mat) {
    matrix* res = matrix_create(((matrix*)mat) -> num, ((matrix*)mat) -> m_info -> size);
    for (int i = 0; i < ((matrix*)mat) -> num; i++) {
        for (int j = 0; j < ((matrix*)mat) -> num; j++) {
            (res -> Lines[i][j]) = malloc(sizeof(double));
            *(double*)(res -> Lines[i][j]) = *(double*)(((matrix*)mat) -> Lines[i][j]);
        }
    }
    for (int i = 0; i < ((matrix*)mat) -> num; i++) {
        for (int j = 0; j < ((matrix*)mat) -> num; j++) {
            *(double*)(((matrix*)res) -> Lines[*(int*)num][j]) += *(double*)(((matrix*)mat) -> Lines[i][j]) * ((double*)coeffs)[i];
        }
    }
    return res;
}

void print_double(void* mat) {
    printf("= = = = = = = = = = = = \n\nМатрица:\n\n");
    for (int i = 0; i<((matrix*)mat) -> num; i++) {
        for (int j = 0; j<((matrix*)mat) -> num; j++) {
            double cur = *(double*)(((matrix*)mat) -> Lines[i][j]);
            printf("%lf\t", cur);
        }
        printf("\n");
    }
    printf("\n\n= = = = = = = = = = = = ");
}

void* enter_double(int num) {
    matrix* mat = matrix_create(num, sizeof(double));
    printf("\nВводите матрицу (%dx%d) построчно:\n\n", num, num);
    for (int i = 0; i < num; i++) {
        printf("Введите элементы %d-й строки:\n>> ", i+1);
        for (int j = 0; j< num; j++) {
            double* cur = get_double();
            if (cur) {
                mat -> Lines[i][j] = cur;
            } else {
                printf("\n<!> Некорректный параметр\n");
                return NULL;
            }
        }
    }
    return mat;
}

double* get_double() {
    double* var = NULL;
    double num = 0;
    int f = scanf("%lf", &num);
    if (f > 0) {
        var = malloc(sizeof(double));
        *var = num;
    }
    return var;
}

void matrix_free(matrix* mat) {
    if (!mat) return;
    for (int i = 0; i < mat -> num; i++) {
        for (int j = 0; j < mat -> num; j++) {
            free(mat -> Lines[i][j]);
        }
        free(mat -> Lines[i]);
    }
    free(mat -> Lines);
    free(mat -> m_info);
    free(mat);
}

int* get_int() {
    int* var = NULL;
    int num = 0;
    int f = scanf("%d", &num);
    if (f > 0) {
        var = malloc(sizeof(int));
        *var = num;
    }
    return var;
}

void* get_det_int(void *mat) {
    int* ans = malloc(sizeof(int));
    double *cur = (double*)(get_det_double(mat));
    *ans = (int)*cur;
    free(cur);
    return ans;
}

void* get_det_double(void *mat) {
    double det = 1;
    matrix* res = matrix_create(((matrix*)mat) -> num, sizeof(double));
    for (int i = 0; i < res -> num; i++) {
        for (int j = 0; j < res -> num; j++) {
            res -> Lines[i][j] = malloc(sizeof(double));
            *(double*)(res -> Lines[i][j]) = (double) *(int*)(((matrix*)mat) -> Lines[i][j]);
        }
    }
    for (int i = 0; i < res -> num; i++) {
        for (int k = i; k < res -> num; k++) {
            if (*(double*)(res -> Lines[k][i]) != 0) {
                det *= *(double*)res -> Lines[k][i];
                double cur = (double)*(double*)res -> Lines[k][i];
                for (int j = 0; j < res -> num; j++) {
                    
                    *(double*)res -> Lines[k][j] /= cur;
                }
            }
        }        
        for (int k = i + 1; k < res -> num; k++) {
            if (*(double*)(res -> Lines[k][i]) != 0) {
                for (int j = 0; j < res -> num; j++) {
                    *(double*)res -> Lines[k][j] -= (double)*(double*)res -> Lines[i][j];
                }
            }
        }
        
    }
    for (int i = 0; i < res -> num; i++) {
        det *= *(double*)(res -> Lines[i][i]);
    }
    matrix_free(res);
    double* ans = malloc(sizeof(double));
    *ans = det;
    return ans;
}

int mat_check(void* mat) {
    for (int i = 0; i < ((matrix*)mat) -> num; i++) {
        for (int j = 0; j < ((matrix*)mat) -> num; j++) {
            if (i > j) {
                if (*(double*)(((matrix*)mat) -> Lines[i][j]) != 0) return 0;
            }
        }
    }
    return 1;
}