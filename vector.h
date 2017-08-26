#ifndef _vector_
#define _vector_
typedef struct{
    void * elems;
    int elem_size;
    int log_len;
    int alloc_len;
    int init_alloc;
}vector;

void vector_new(vector *v, int elem_size, int init_alloc);

void vector_dispose(vector * v);

int vector_length(const vector *v);

void *vector_nth(const vector *v, int position);

void vector_insert(vector *v, const void *elem_addr, int position);

void vector_append(vector *v, const void *elem_addr);

void vector_replace(vector *v, const void *elem_addr, int position);

void vector_delete(vector *v, int position);
#endif
