#include "linkedlist.h"

#include <stdbool.h>
#include <stdlib.h>


linkedlist new_llist(allocator allocator) {
  return (linkedlist) {
    .allocator = allocator,
    .head = NULL,
    .tail = NULL
  };
}

void delete_llist(
  linkedlist* const list,
  void (*delete)(allocator, void*),
  allocator allocator
) {
  listnode* next;
  
  for (listnode* node = list->head; node != NULL; node = next) {
    next = node->next;
    
    if (delete != NULL)
      delete(allocator, node->data);
    
    al_dealloc(list->allocator, node);
  }
  
  *list = (linkedlist) {
    .allocator = null_allocator(),
    .head = NULL,
    .tail = NULL
  };
}


bool llist_empty(linkedlist list) {
  return list.head == NULL;
}


void llist_push_head(linkedlist* list, const void* obj) {  // Insert at the head.
  if (obj == NULL)
    return;

  listnode* node = al_alloc(list->allocator, 1, sizeof(*node));
  *node = (listnode) {
    .next = list->head,
    .data = (void*) obj
  };
  
  if (llist_empty(*list))
    list->tail = node;
  
  list->head = node;
}

void llist_push_tail(linkedlist* list, const void* obj) {  // Insert at the tail.
  if (obj == NULL)
    return;
  
  listnode* node = al_alloc(list->allocator, 1, sizeof(*node));
  *node = (listnode) {
    .next = NULL,
    .data = (void*) obj
  };
  
  if (llist_empty(*list))
    list->head = list->tail = node;
  else
    list->tail = list->tail->next = node;
}


void* llist_pop_head(linkedlist* list) {  // Pop from the head.
  if (llist_empty(*list))
    return NULL;
  
  listnode* node = list->head;
  void* obj = node->data;
  
  list->head = list->head->next;
  if (list->tail == node)
    list->tail = NULL;
  
  al_dealloc(list->allocator, node);
  
  return obj;
}
