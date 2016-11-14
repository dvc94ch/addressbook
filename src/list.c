/******************************************************************************
 * Copyright © 2016 David Craven <david@craven.ch>
 *
 * This file is part of AddressBook.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#include <stdlib.h>
#include "list.h"

list_t* list_new(void) {
  list_t* list = (list_t*)malloc(sizeof(list_t));
  list->head = NULL;
  return list;
}

listItem_t* listItem_new(void* data) {
  listItem_t* item = (listItem_t*)malloc(sizeof(listItem_t));
  item->data = data;
  item->next = NULL;
  return item;
}

void list_push(list_t* list, void* data) {
  if (list != NULL) {
    listItem_t *item = listItem_new(data);
    item->next = list->head;
    list->head = item;
  }
}

void* list_pop(list_t* list) {
  if (list != NULL && list->head != NULL) {
    listItem_t* item = list->head;
    void* data = item->data;
    list->head = item->next;
    free(item);
    return data;
  }
  return NULL;
}

void list_each(list_t* list, void (*callback)(void*)) {
  for (listItem_t* item = list->head; item != NULL; item = item->next) {
    callback(item->data);
  }
}

list_t *list_sort(list_t* list, int (*cmp)(void*, void*)) {
  list_t *sorted_list;
  void *data;

  // list can be NULL or empty
  if (!list || !list->head) {
    return list;
  }
  // list contains at least one element

  sorted_list = list_new();
  list_push(sorted_list, list_pop(list));

  // sorted_list has at least one element
  while ((data = list_pop(list))) {
    listItem_t *next;
    for (listItem_t *item = sorted_list->head; item; item = item->next) {
      int res = cmp(data, item->data);
      // push when smaller than first element
      if (res <= 0 && sorted_list->head == item) {
        list_push(sorted_list, data);
        break;
      }
      // append when no elements left
      if (!item->next) {
        item->next = listItem_new(data);
        break;
      }

      // item->next != NULL
      int res_next = cmp(data, item->next->data);
      if (res >= 0 && res_next <= 0) {
        next = item->next;
        item->next = listItem_new(data);
        item->next->next = next;
        break;
      }
    }
  }

  free(list);

  return sorted_list;
}

void list_free(list_t* list, void (*data_free)(void*)) {
  for (listItem_t* item = list->head; item != NULL; ) {
    listItem_t* next = item->next;
    data_free(item->data);
    free(item);
    item = next;
  }
  free(list);
}
