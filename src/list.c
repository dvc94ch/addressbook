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

void list_push(list_t* list, void* data) {
  if (list != NULL) {
    listItem_t* item = (listItem_t*)malloc(sizeof(listItem_t));
    item->data = data;
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

void list_free(list_t* list, void (*data_free)(void*)) {
  for (listItem_t* item = list->head; item != NULL; ) {
    listItem_t* next = item->next;
    data_free(item->data);
    free(item);
    item = next;
  }
  free(list);
}
