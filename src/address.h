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

#ifndef ADDRESS_H
#define ADDRESS_H

#include <stdio.h>

typedef struct address_ {
  char* name;
  char* street;
  char* zip;
  char* city;
} address_t;

address_t* address_new(char* name, char* street, char* zip, char* city);

void address_print(address_t* addr);

void address_write(FILE* file, address_t* addr);

address_t* address_read(FILE* file);

void address_free(address_t* addr);

#endif /* ADDRESS_H */
