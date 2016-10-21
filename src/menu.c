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
#include <string.h>
#include "menu.h"

/*
 * Creates a new menu. A menu is a linked list of menuItem's.
 */
menu_t* menu_new(void)
{
  menu_t* menu = (menu_t*)malloc(sizeof(menu_t));
  menu->head = NULL;
  menu->tail = NULL;
  return menu;
}

/*
 * Add a command to MENU.
 */
void registerCommand(menu_t* menu, char key, char* description,
                     commandCb_t func)
{
  if (menu == NULL) return;

  command_t* cmd = (command_t*)malloc(sizeof(command_t));
  cmd->key = key;
  cmd->description = strdup(description);
  cmd->func = func;

  menuItem_t* item = (menuItem_t*)malloc(sizeof(menuItem_t));
  item->command = cmd;
  item->next = NULL;

  if (menu->head == NULL) {
    menu->head = menu->tail = item;
  } else {
    menu->tail->next = item;
    menu->tail = menu->tail->next;
  }
}

/*
 * Takes a MENU and runs the first command with key KEY.  If no
 * command is found, then FALLBACK is run.
 */
void runCommand(menu_t* menu, void* data, char key, commandCb_t fallback)
{
  for (menuItem_t* item = menu->head; item != NULL; item = item->next) {
    command_t* cmd = item->command;
    if (cmd->key == key) {
      return (*cmd->func)(menu, data);
    }
  }

  (*fallback)(menu, data);
}

/*
 * Takes a MENU and releases all resources recursively.
 */
void menu_free(menu_t* menu)
{
  for (menuItem_t* item = menu->head; item != NULL; ) {
    free(item->command->description);
    free(item->command);

    menuItem_t* oldItem = item;
    item = item->next;
    free(oldItem);
  }

  free(menu);
}
