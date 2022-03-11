void* sum_int(void*, void*);
void* comp_int(void*, void*);
void* scal_int(void*, void*);
void* linear_comb_int(void*, void*, void*);
void print_int(void*);
int* get_int();
double* get_double();
void* sum_double(void*, void*);
void* comp_double(void*, void*);
void* scal_double(void*, void*);
void* linear_comb_double(void*, void*, void*);
void print_double(void*);
void* enter_double(int);
void* get_det_int(void*);
void* get_det_double(void*);
int mat_check(void*);
struct Info* InfoInit(size_t size, void* (*sum)(void*, void*), void* (*comp)(void*, void*), 
    void* (*scal)(void*, void*), void* (*linear_comb)(void*, void*, void*), void (*print)(void*), void* (*get_det)(void*));

struct Info {
    size_t size;
    void* (*sum)(void*, void*);
    void* (*comp)(void*, void*);
    void* (*scal)(void*, void*);
    void* (*linear_comb)(void*, void*, void*);
    void (*print)(void*);
    void* (*get_det)(void*);
};

typedef struct matrix{
    void*** Lines;
    int num;
    struct Info* m_info;
} matrix;

void matrix_free(matrix*);
