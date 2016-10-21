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

#ifndef MENU_H
#define MENU_H

typedef struct menu_* menuPtr_t;
typedef void (*commandCb_t)(menuPtr_t menu, void* data);

typedef struct command_ {
  char key;
  char* description;
  commandCb_t func;
} command_t;

typedef struct menuItem_ {
  command_t* command;
  struct menuItem_* next;
} menuItem_t;

typedef struct menu_ {
  menuItem_t* head;
  menuItem_t* tail;
} menu_t;

menu_t* menu_new(void);

void registerCommand(menu_t* menu, char key, char* description,
                     commandCb_t func);

void runCommand(menu_t* menu, void* data, char key, commandCb_t fallback);

void menu_free(menu_t* menu);

#endif /* MENU_H */
