#ifndef _LIST_H_
#define _LIST_H_ 

#include <stddef.h>
#include <stdbool.h>
#include <alloc/alloc.h>


typedef struct list list;


/**
 * @brief
 */
list * list_new(Alloc * alloc, size_t dtype);


/**
 * @brief
 */
bool list_push_front(list * self, void * value);


/**
 * @brief
 */
bool list_push_back(list * self, void * value);


/**
 * @brief
 */
void * list_front(list * self);


/**
 * @brief
 */
void * list_back(list * self);


/**
 * @brief
 */
void * list_get(list * self, size_t index);


/**
 * @brief
 */
void list_remove(list * self, size_t index);


/**
 * @brief
 */
void list_remove_front(list * self);


/**
 * @brief
 */
void list_remove_back(list * self);


#include "iter.h"


/**
 * @brief
 */
typedef struct {
    iterator iter;
    void * head;
}list_iter;


/**
 * @brief
 */
list_iter list_iterator(list * self);


/**
 * @brief
 */
size_t list_size(list * self);


/**
 * @brief
 */
size_t list_dtype(list * self);


/**
 * @brief
 */
bool list_empty(list * self);


/**
 *@brief
 */
void list_finalize(list * self);


#endif


