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

typedef struct {
  char *filename;
  menu_t *menu;
  list_t *addresses;
} appData_t;


void new(appData_t *app)
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
  list_push(app->addresses, addr);

  return address_print(addr);

 error:
  fprintf(stderr, "Buffer overflow.");
}

void print(appData_t *app)
{
  list_each(app->addresses, &address_print);
}

void load(appData_t *app)
{
  FILE *f = fopen(app->filename, "r");
  if (!f) goto error_open;

  address_t *addr;
  while ((addr = address_read(f))) {
    list_push(app->addresses, addr);
  }

  return;

 error_open:
  fprintf(stderr, "File couldn't be opened: %s", strerror(errno));
}

void save(appData_t *app)
{
  FILE *f = fopen(app->filename, "w+");
  if (!f) goto error_open;

  for (listItem_t *item = (app->addresses)->head; item; item = item->next) {
    address_write(f, (address_t*)item->data);
  }

  int fd = fileno(f);
  // C11 fflush only flushes libc buffer to os
  // POSIX fsync flushes the os buffer too
  if (fsync(fd) != 0) goto error_write;
  if (fclose(f) != 0) goto error_write;
  return;

 error_open:
  fprintf(stderr, "File couldn't be opened: %s", strerror(errno));
  return;

 error_write:
  fprintf(stderr, "Error writing to file: %s", strerror(errno));
}

void sort_by_name(appData_t *app) {
  app->addresses = list_sort(app->addresses, &address_cmp_name);
}

void sort_by_zip(appData_t *app) {
  app->addresses = list_sort(app->addresses, &address_cmp_zip);
}

void help(appData_t *app)
{
  printf("========= Menu =========\n\n");

  for (menuItem_t* item = app->menu->head; item != NULL; item = item->next) {
    command_t* cmd = item->command;
    printf("%c --> %s\n", cmd->key, cmd->description);
  }

  printf("\n========================\n");
}

void unknown_command(appData_t *app)
{
  printf("Unknown command, press h for help.");
}

void quit(appData_t *app)
{
  list_free(app->addresses, &address_free);
  menu_free(app->menu);
  exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
  appData_t app;
  app.filename = "addresses.csv";
  app.menu = menu_new();
  app.addresses = list_new();

  char key;

  registerCommand(app.menu, 'n', "New address", &new);
  registerCommand(app.menu, 'p', "Print addresses", &print);
  registerCommand(app.menu, 'l', "Load addresses", &load);
  registerCommand(app.menu, 's', "Save addresses", &save);
  registerCommand(app.menu, '1', "Sort by name", &sort_by_name);
  registerCommand(app.menu, '2', "Sort by zip", &sort_by_zip);
  registerCommand(app.menu, 'h', "Print help", &help);
  registerCommand(app.menu, 'q', "Quit", &quit);

  // Disable stdout buffering to avoid having to call fflush all the time.
  setbuf(stdout, NULL);
  help(&app);
  printf("Command: ");

  while ((key = getchar())) {
    if (isalnum(key)) {
      runCommand(app.menu, &app, tolower(key), &unknown_command);
      printf("Command: ");
    }
  }
}
