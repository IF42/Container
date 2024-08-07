#include "container/list.h"

#include <string.h>
#include <stdlib.h>


typedef struct node {
    struct node * next;
    struct node * prev;
}node;


struct list {
    vector vector;

    size_t size;
    node * front;
    node * back;

    struct {
        node * front;
    }iterator;
};


vector * list_new(Alloc * alloc, size_t dtype) {
    list * self = new(alloc, sizeof(list));

    *self = (list) {
        .alloc = alloc
        , .dtype = dtype
    };

    return self;
}


bool list_push_front(list * self, void * value) {
    node * list_node = new(self->alloc, sizeof(node) + self->dtype);

    if(list_node != NULL) {
        memcpy((list_node + 1), value, self->dtype);

        list_node->next = self->front;
        list_node->prev = NULL;

        if(self->front != NULL) {
            self->front->prev = list_node;
        }

        self->front = list_node;

        if(self->back == NULL) {
            self->back = list_node;
        }   

        self->size++;

        return true;
    } else {
        return false;
    }
}


bool list_push_back(list * self, void * value) {
    node * list_node = new(self->alloc, sizeof(node) + self->dtype);

    if(list_node != NULL) {
        memcpy((list_node + 1), value, self->dtype);

        list_node->next = NULL;
        list_node->prev = self->back;

        if(self->back != NULL) {
            self->back->next= list_node;
        }

        self->back = list_node;

        if(self->front == NULL) {
            self->front = list_node;
        }

        self->size++;

        return true;
    } else {
        return false;
    }
}


void * list_front(list * self) {
    return self->front + 1;
}


void * list_back(list * self) {
    return self->back + 1;
}


/*
 * TODO: improve searching of node on given index by starting at the nearest edge (index > size/2 ? back : front )
 */
static node * list_find_node(list * self, size_t index) {
    if(index < self->size) {
        node * list_node = self->front;

        for(size_t i = 0; i < index; i++) {
            if(list_node != NULL) {
                list_node = list_node->next;
            } else {
                return NULL;
            }
        }

        return list_node;
    } else {
        return NULL;
    }
}


void * list_get(list * self, size_t index) {
    node * list_node = list_find_node(self, index);

    if(list_node != NULL) {
        return list_node + 1;
    } else {
        return NULL;
    }
}


static void * list_iterator_next(list_iter * iterator) {
    if(iterator->head != NULL) {
        void * data = (void*) (((node*) iterator->head) + 1); 
        iterator->head = ((node*) iterator->head)->next;
        return data;
    } else {
        return NULL;
    }
}


list_iter list_iterator(list * self) {
    return (list_iter) {
        .iter.next = (void*(*)(iterator *)) list_iterator_next 
        , .head = self->front
    };
}


void list_remove(list * self, size_t index) {
    node * list_node = list_find_node(self, index);

    if(list_node != NULL) {
        if(list_node->prev != NULL) {
            list_node->prev->next = list_node->next;
        }

        if(list_node->next != NULL) {
            list_node->next->prev = list_node->prev;
        }

        /*
         * update front and back reference
         */
        if(list_node == self->front) {
            self->front = list_node->next;
        }
        
        if(list_node == self->back) {
            self->back = list_node->prev;
        }

        /*
         * delete memory
         */
        delete(self->alloc, list_node);

        self->size --;
    } 
}


void list_remove_front(list * self) {
    if(self->front != NULL) {
        if(self->front == self->back) {
            delete(self->alloc, self->front);
            self->front = NULL;
            self->back = NULL;
        } else {
            node * list_node = self->front;
            self->front = list_node->next;
            self->front->prev = NULL;
            delete(self->alloc, list_node);
        }

        self->size --;
    }
}


void list_remove_back(list * self) {
    if(self->back != NULL) {
        if(self->back == self->front) {
            delete(self->alloc, self->front);
            self->front = NULL;
            self->back = NULL;
        } else {
            node * list_node = self->back;
            self->back = list_node->prev;
            self->back->next = NULL;
            delete(self->alloc, list_node);
        }

        self->size --;
    }
}


bool list_empty(list * self) {
    if(self->size == 0) {
        return true;
    } else {
        return false;
    } 
}


size_t list_size(list * self) {
    return self->size;
}


size_t list_dtype(list * self) {
    return self->dtype;
}


void list_finalize(list * self) {
    if(self != NULL) {
        finalize(self->alloc);
    }
}

