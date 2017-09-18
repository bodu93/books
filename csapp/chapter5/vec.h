#include "typedef.h"

typedef struct {
    long len;
    data_t *data;
} vec_rec, *vec_ptr;

vec_ptr new_vec(long);

int get_vec_element(vec_ptr, long, data_t *);

long vec_length(vec_ptr);
