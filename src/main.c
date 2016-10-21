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

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "address.h"
#include "list.h"
#include "menu.h"

void new(menu_t* menu, void* addresses)
{
  char c;
  // Flush input buffer.
  while ((c = getchar()) != '\n' && c != EOF);

  char name[100];
  printf("Name: ");
  if (fgets(name, sizeof(name), stdin) == NULL) goto error;
  name[strcspn(name, "\n")] = 0;

  char street[100];
  printf("Street: ");
  if (fgets(street, sizeof(street), stdin) == NULL) goto error;
  street[strcspn(street, "\n")] = 0;

  char zip[10];
  printf("Zip: ");
  if (fgets(zip, sizeof(zip), stdin) == NULL) goto error;
  zip[strcspn(zip, "\n")] = 0;

  char city[30];
  printf("City: ");
  if (fgets(city, sizeof(city), stdin) == NULL) goto error;
  city[strcspn(city, "\n")] = 0;

  address_t* addr = address_new(name, street, zip, city);
  list_push(addresses, addr);

  return address_print(addr);

 error:
  fprintf(stderr, "Buffer overflow.");
}

void print(menu_t* menu, void* addresses)
{
  list_each(addresses, &address_print);
}

void help(menu_t* menu, void* addresses)
{
  printf("========= Menu =========\n\n");

  for (menuItem_t* item = menu->head; item != NULL; item = item->next) {
    command_t* cmd = item->command;
    printf("%c --> %s\n", cmd->key, cmd->description);
  }

  printf("\n========================\n");
}

void unknown_command(menu_t* menu, void* addresses)
{
  printf("Unknown command, press h for help.");
}

void quit(menu_t* menu, void* addresses)
{
  list_free(addresses, &address_free);
  menu_free(menu);
  exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
  menu_t* menu = menu_new();
  list_t* addresses = list_new();
  char key;

  registerCommand(menu, 'n', "New address", &new);
  registerCommand(menu, 'p', "Print addresses", &print);
  registerCommand(menu, 'h', "Print help", &help);
  registerCommand(menu, 'q', "Quit", &quit);

  // Disable stdout buffering to avoid having to call fflush all the time.
  setbuf(stdout, NULL);
  help(menu, addresses);
  printf("Command: ");

  while ((key = getchar())) {
    if (isalnum(key)) {
      runCommand(menu, addresses, tolower(key), &unknown_command);
      printf("Command: ");
    }
  }
}
