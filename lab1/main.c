#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "matrix.h"
#include <string.h>
//#include <unistd.h>
#include <time.h>

matrix* enter();
matrix* process(matrix*);
void* enter_int(int);
void* enter_double(int);
void matrix_free(matrix* mat);
void flush();
void load_main();
void load_screen();
void sleep(double);
int* get_coeffs_int(int, int *);
double* get_coeffs_double(int, int *);

int main() {
    load_main();
    int* var = NULL;
    matrix* mat = NULL;
    do {
        printf("\n= = = = = = = = = = = = \n\nВыберите команду:\n\n<1> Ввести матрицу\n<2> Вывести матрицу\n<3> Обработать матрицу \n<4> Посчитать определитель \n<5> Дополнительная функция\n<6> Выход\n\n= = = = = = = = = = = = \n\n>> ");
        if (var)
            free(var);
        var = get_int();
        flush();
        if (!var) {
            system("clear");
            printf("\n<!> Введено не число\n");
            continue;
        }
        switch (*var) {
            //ввод
            case 1:
                system("clear");
                matrix_free(mat);
                mat = enter();
                break;
            //вывод
            case 2:
                if (!mat) {
                    system("clear");
                    printf("\n<!> Матрица не существует\n");
                    break;
                }
                system("clear");
                mat -> m_info -> print((void*)mat);

                break;
            case 3:
                if (!mat) {
                    system("clear");
                    printf("\n<!> Матрица не существует\n");
                    break;
                }
                mat = process(mat);
                break;
            case 4:
                if (!mat) {
                    system("clear");
                    printf("\n<!> Матрица не существует\n");
                    break;
                }
                if (mat -> m_info -> size == sizeof(int)) {
                    int* cur = mat -> m_info -> get_det(mat);
                    printf("\n\nОпределитель матрицы -> %d\n\n", *cur);
                    free(cur);
                } else {
                    double* cur = mat -> m_info -> get_det(mat);
                    printf("\n\nОпределитель матрицы -> %lf\n\n", *cur);
                    free(cur);
                }
                break;
            case 5:
                if (!mat) {
                    system("clear");
                    printf("\n<!> Матрица не существует\n");
                    break;
                }
                if (mat_check(mat)) {
                    printf("\n\nМатрица является верхнетреугольной\n\n");
                } else {
                    printf("\n\nМатрица не является верхнетреугольной\n\n");
                }
                break;
            case 6:
                system("clear");
                matrix_free(mat);
                printf(" = = = = = = = = = = = = = = = = = = = = = = =\n\n\t\tДо встречи!\n\n = = = = = = = = = = = = = = = = = = = = = = =\n");
                break;

            default:
                system("clear");
                printf("\n<!> Неверный номер команды\n");
        }
    } while(!var || (var && *var != 6));
    if (var) free(var);
    return 0;
}



matrix* enter() {
    printf("Введите размер квадратной матрицы:\n>> ");
    int* cur = get_int();
    if (!cur) {
        printf("<!> Введено не число\n");
        return NULL;
    }
    if (*cur < 1) {
        free(cur);
        printf("<!> Размер должен быть положительным\n");
        return NULL;
    }
    int size = *cur;
    flush();
    do {
        printf("\n= = = = = = = = = = = = \n\nВыберите тип данных:\n\n<1> Целые числа\n<2> Вещественные\n<3> Назад\n\n= = = = = = = = = = = = \n\n>> ");
        free(cur);
        cur = get_int();
        flush();
        if (!cur) {
            system("clear");
            printf("\n<!> Введено не число\n");
            continue;
        }
        switch (*cur) {
            matrix* mat;
            case 1:
                system("clear");
                mat = (matrix*)enter_int(size);
                if (mat) {
                    printf("\n\n<OK> Успешно считано\n\n");
                }
                free(cur);
                return mat;
                break;
            case 2:
                system("clear");
                mat = (matrix*)enter_double(size);
                if (mat) {
                    printf("\n\n<OK> Успешно считано\n\n");
                }
                free(cur);

                return mat;
                break;
            case 3:
                free(cur);
                return NULL;
                break;
            default:
                system("clear");

                printf("\n<!> Неверный номер команды\n");
        }
        
    } while(!cur || (cur && *cur != 3));
}

matrix* process(matrix* mat) {
    int *cur = NULL;
    do {
        printf("\n= = = = = = = = = = = = \n\nВыберите тип обработки:\n\n<1> Матричное сложение\n<2> Матричное умножение\n<3> Умножение на скаляр\n<4> Линейная комбинация строк\n<5> Назад\n\n= = = = = = = = = = = = \n\n>> ");
        if (cur)
            free(cur);
        cur = get_int();
        flush();
        if (!cur) {
            system("clear");
            printf("\n<!> Введено не число\n");
            continue;
        }
        switch (*cur) {
            matrix* mat2;
            matrix* mat_res;
            case 1:
                system("clear");
                printf("\n= = = = = = = = = = = = \n\n Матричное сложение \n\n= = = = = = = = = = = = \n");
                mat -> m_info -> print(mat);
                if (mat -> m_info -> size == sizeof(int)) {
                    mat2 = enter_int(mat -> num);
                } else {
                    mat2 = enter_double(mat -> num);
                }
                if (!mat2) {
                    return mat;
                }
                mat_res =  mat -> m_info -> sum(mat, mat2);
                if (mat_res) {
                    printf("\n\n<OK> Успешно обработано\n\n");
                } else {
                    return mat;
                }
                matrix_free(mat);
                matrix_free(mat2);
                free(cur);
                return mat_res;
                break;
            case 2:
                system("clear");
                printf("\n= = = = = = = = = = = = \n\n Матричное умножение \n\n= = = = = = = = = = = = \n");
                mat -> m_info -> print(mat);
                if (mat -> m_info -> size == sizeof(int)) {
                    mat2 = enter_int(mat -> num);
                } else {
                    mat2 = enter_double(mat -> num);
                }
                if (!mat2) {
                    return mat;
                }
                mat_res =  mat -> m_info -> comp(mat, mat2);
                if (mat_res) {
                    printf("\n\n<OK> Успешно обработано\n\n");
                } else {
                    return mat;
                }
                matrix_free(mat);
                matrix_free(mat2);
                free(cur);
                return mat_res;
                break;
            case 3:
                system("clear");
                printf("\n= = = = = = = = = = = = \n\n Умножение на скаляр \n\n= = = = = = = = = = = = \n");
                mat -> m_info -> print(mat);
                void* num = NULL;
                if (mat -> m_info -> size == sizeof(int)) {
                    printf("\nВведите целочисленный скаляр\n>> ");
                    num = get_int();
                    flush();
                } else {
                    printf("\nВведите вещественный скаляр\n>> ");
                    num = get_double();
                    flush();
                }
                if (!num) {
                    system("clear");
                    printf("\n\n<!> Введено не число\n\n");
                    return mat;
                }
                mat_res = mat -> m_info -> scal(num, mat);
                free(num);
                if (mat_res) {
                    printf("\n\n<OK> Успешно обработано\n\n");
                } else {
                    return mat;
                }
                matrix_free(mat);
                free(cur);
                return mat_res;
                break;
            case 4:
                system("clear");
                printf("\n= = = = = = = = = = = = = = = = = = = = =\n\n\tЛинейная комбинация строк \n\n= = = = = = = = = = = = = = = = = = = = =\n");
                mat -> m_info -> print(mat);
                int* str;
                printf("\n\nВведите номер строки, к которой прибавляется\nлинейная комбинация\n>> ");
                str = get_int();
                if (!str) {
                    system("clear");
                    printf("\n\n<!> Введено не число\n\n");
                    free(cur);
                    return mat;
                }
                if (*str < 1 || *str > mat -> num) {
                    system("clear");
                    printf("\n\n<!> Строки с таким номером не существует\n\n");
                    free(str);
                    free(cur);
                    return mat;
                }
                *str = *str - 1;
                printf("\n\nВводите коэффициенты перед каждой строкой линейной комбинации\n\n");
                void* coeffs;
                if (mat -> m_info -> size == sizeof(int)) {
                    coeffs = get_coeffs_int(mat -> num, str);
                } else {
                    coeffs = get_coeffs_double(mat -> num, str);
                }
                if (!coeffs) {
                    system("clear");
                    free(str);
                    free(cur);
                    printf("\n\n<!> Введено не число\n\n");
                    return mat;
                }
                mat_res = mat -> m_info -> linear_comb(str, coeffs, mat);
                free(str);
                free(coeffs);
                if (mat_res) {
                    printf("\n\n<OK> Успешно обработано\n\n");
                } else {
                    return mat;
                }
                matrix_free(mat);
                free(cur);
                return mat_res;
                break;
            case 5:
                free(cur);
                return mat;
                break;
            default:
                system("clear");
                printf("\n<!> Неверный номер команды\n");

        }
       
    } while(!cur || (cur && *cur != 5));
}

void flush() {
    while(getchar() != '\n');
}

void load_main() {
    load_screen("Загрузка файлов", 20);
    load_screen("Загрузка библиотек", 28);
    load_screen("Подключение математического модуля", 16);
    load_screen("Сборка программы", 22);
    load_screen("Запуск main.c", 19);
    printf("\n\nЗагрузка завершена.\n");
    sleep(2);
    system("clear");
}

void load_screen(const char* x, int delta) {
    int d = 0;
    srand(time(0));
    system("clear");
    int f = 2;
    while(d <= 100 && f) {
        sleep(0.25);
        system("clear");
        printf("\n%s\t", x);
        fflush(stdout);
        printf("[ %d% ]\n\n< ", d);
        for (int i = 0; i< d / 4; i++) {
            printf("%c ", 128);
        }
        printf(" >");
        fflush(stdout);
        d += rand()%8 - 4 + delta;
        if (d > 100) d = 100, f -= 1;
    }
    sleep(0.5);
}

int* get_coeffs_int(int num, int *str) {
    int* res = malloc(num*sizeof(int));
    for (int i = 0; i < num; i++) {
        if (i == *str) {
            res[i] = 0;
            continue;
        }
        printf("Введите целочисленный коэффициент для %d-й строки\n>> ", i+1);
        int* cur = get_int();
        if (!cur) {
            free(res);
            free(cur);
            return NULL;
        }
        res[i] = *cur;
        free(cur);
    }
    return res;
}

double* get_coeffs_double(int num, int *str) {
    double* res = malloc(num*sizeof(double));
    for (int i = 0; i < num; i++) {
        if (i == *str) {
            res[i] = 0;
            continue;
        }
        printf("Введите вещественный коэффициент для %d-й строки\n>> ", i+1);
        double* cur = get_double();
        if (!cur) {
            free(res);
            free(cur);
            return NULL;
        }
        res[i] = *cur;
        free(cur);
    }
    return res;
}

void sleep(double sec) {
    clock_t t1 = clock();
    clock_t t2 = clock();
    while((double)(t2 - t1)/(double)CLOCKS_PER_SEC < sec) {
        t2 = clock();
    }
}