#include "vector.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void grow(vector *v){
    v-> alloc_len += v->init_alloc;
    v->elems =  realloc(v->elems, v->elem_size * v->alloc_len);
}

void vector_new(vector *v, int elem_size, int init_alloc){
    assert(elem_size > 0);
	assert(init_alloc > 0);
    assert(v != NULL);

    v->alloc_len = init_alloc;
    v->init_alloc = init_alloc;
    v->log_len = 0;
    v->elem_size = elem_size;
    v->elems = malloc(v->elem_size * v->alloc_len);
}

void vector_dispose(vector * v){
    assert(v != NULL);

    free(v->elems);
}

int vector_length(const vector *v){
    assert(v != NULL);

    return v->log_len;
}

void *vector_nth(const vector *v, int position){
    assert(v != NULL);
    assert(position >= 0);
    assert(position < v->log_len);

    return (char *)v->elems + v->elem_size * position;
}

void vector_insert(vector *v, const void *elem_addr, int position){
    assert(v != NULL);
    assert(position >= 0);
    assert(position <= v->log_len);

    if(v->log_len == v->alloc_len)
        grow(v);

    void * destination = (char *)v->elems + (position + 1) * v->elem_size;
    void * source = (char *)v->elems + position * v->elem_size;
    int move_size = (v->log_len - position) * v->elem_size;

    memmove(destination, source, move_size);
    source = memcpy(source, elem_addr, v->elem_size);
    v->log_len ++;
}

void vector_append(vector *v, const void *elem_addr){
    assert(v != NULL);
    assert(elem_addr != NULL);

    if(v->log_len == v->alloc_len)
        grow(v);

    void * destination = (char *)v->elems + v->elem_size * v->log_len;
    memcpy(destination, elem_addr, v->elem_size);
    v->log_len ++;
}

void vector_replace(vector *v, const void *elem_addr, int position){
    assert(v != NULL);
    assert(elem_addr != NULL);
    assert(position >= 0);
    assert(position < v->log_len);

    void * destination = (char *)v->elems + position * v->elem_size;
    memcpy(destination, elem_addr, v->elem_size);
}


void vector_delete(vector *v, int position){
    assert(v != NULL);
    assert(position >= 0);
    assert(position < v->log_len);

    void * destination = (char *)v->elems + position * v->elem_size;
    void * source = (char *)v->elems + (position + 1) * v->elem_size;
    int move_size = (v->log_len - position + 1) * v->elem_size;
    memmove(destination, source, move_size);
    v->log_len --;
}
