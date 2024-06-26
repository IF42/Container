/** 
 * @file dynarr.h
 *
 */

#ifndef _DYNARR_H_
#define _DYNARR_H_

#include <stdbool.h>
#include <stddef.h>
#include <alloc/alloc.h>

typedef struct dynarr dynarr;


/**
 * @brief
 */
dynarr * dynarr_new(Alloc * alloc, size_t dtype);


/** 
 * @brief
 */
dynarr * dynarr_new_empty(Alloc * alloc, size_t dtype, size_t size);


/*
 * @brief
 */
dynarr * dynarr_new_from_array(Alloc * alloc, size_t dtype, size_t size, void * array);


#include "iter.h"


typedef struct {
    iterator iter;
    size_t dtype;
    size_t size;
    size_t index;
    void * head;
}dynarr_iter;


/**
 * @brief
 */
dynarr_iter dynarr_iterator(dynarr * self);



/**
 * @brief
 */
void * dynarr_at(dynarr * self, size_t index);


/**
 * @brief
 */
bool dynarr_set(dynarr * self, size_t index, void * value);


/**
 * @brief
 */
void dynarr_push(dynarr * self, void * value);


/**
 * @brief
 */
bool dynarr_insert(dynarr * self, size_t index, void * value);


/**
 * @brief
 */
void dynarr_round(dynarr * self);


/**
 * @brief
 */
size_t dynarr_size(dynarr * self);


/**
 *  @brief
 */
void dynarr_clear(dynarr * self);


/**
 * @brief
 */
const void * dynarr_array(dynarr * self);


/**
 * @brief
 */
void * dynarr_to_array(dynarr * self);


/**
 * @brief
 */
size_t dynarr_dtype(dynarr * self);


/**
 * @brief
 */
void dynarr_finalize(dynarr * self);


#endif
