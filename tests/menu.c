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
#include "../src/menu.h"

int callback_called;

void callback(menu_t* menu, void* data)
{
  ck_assert(menu != NULL);
  callback_called++;
}

START_TEST (test_menu_new)
{
  menu_t* menu = menu_new();
  ck_assert(menu != NULL);
  ck_assert(menu->head == NULL);
  ck_assert(menu->tail == NULL);

  menu_free(menu);
}
END_TEST

START_TEST (test_registerCommand)
{
  menu_t* menu = menu_new();
  registerCommand(menu, 'c', "description", &callback);
  ck_assert(menu->head != NULL);
  ck_assert(menu->tail ==  menu->head);

  command_t* cmd = menu->head->command;
  ck_assert(cmd->key == 'c');
  ck_assert_str_eq(cmd->description, "description");
  ck_assert(cmd->func == &callback);

  menu_free(menu);
}
END_TEST


START_TEST (test_runCommand_exists)
{
  menu_t* menu = menu_new();
  registerCommand(menu, 'c', "description", &callback);

  callback_called = 0;
  runCommand(menu, NULL, 'c', NULL);
  ck_assert(callback_called == 1);

  menu_free(menu);
}
END_TEST

START_TEST (test_runCommand_fallback)
{
  menu_t* menu = menu_new();

  callback_called = 0;
  runCommand(menu, NULL, 'c', &callback);
  ck_assert(callback_called == 1);

  menu_free(menu);
}
END_TEST

Suite* menuSuite(void)
{
  Suite *s = suite_create("Menu");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_menu_new);
  tcase_add_test(tc_core, test_registerCommand);
  tcase_add_test(tc_core, test_runCommand_exists);
  tcase_add_test(tc_core, test_runCommand_fallback);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = menuSuite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
