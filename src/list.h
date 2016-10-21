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

#ifndef LIST_H
#define LIST_H

typedef struct listItem_ {
  void* data;
  struct listItem_* next;
} listItem_t;

typedef struct list_ {
  listItem_t* head;
} list_t;

list_t* list_new();
void list_push(list_t* list, void* data);
void* list_pop(list_t* list);
void list_each(list_t* list, void (*callback)(void* data));
void list_free(list_t* list, void (*free_data)(void* data));

#endif /* LIST_H */
