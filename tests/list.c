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

#include <check.h>
#include <stdlib.h>
#include "../src/list.h"

int callback_called;

void callback(void* data)
{
  callback_called++;
}

START_TEST (test_list)
{
  int numbers[3] = {1, 2, 3};
  list_t* list = list_new();

  ck_assert(list_pop(list) == NULL);

  list_push(list, &numbers[0]);
  list_push(list, &numbers[1]);
  list_push(list, &numbers[2]);

  callback_called = 0;
  list_each(list, &callback);
  ck_assert_int_eq(callback_called, 3);

  ck_assert(list_pop(list) == &numbers[2]);
  ck_assert(list_pop(list) == &numbers[1]);
  ck_assert(list_pop(list) == &numbers[0]);

  ck_assert(list_pop(list) == NULL);

  list_free(list, &callback);
}
END_TEST

Suite* addressSuite(void)
{
  Suite *s = suite_create("List");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_list);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = addressSuite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
