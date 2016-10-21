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
#include "../src/address.h"

START_TEST (test_address_new)
{
  address_t* addr = address_new("David Craven", "Hauptstrasse 32",
                                "6260", "Reiden");
  ck_assert(addr != NULL);
  ck_assert_str_eq(addr->name, "David Craven");
  ck_assert_str_eq(addr->street, "Hauptstrasse 32");
  ck_assert_str_eq(addr->zip, "6260");
  ck_assert_str_eq(addr->city, "Reiden");

  address_free(addr);
}
END_TEST

Suite* addressSuite(void)
{
  Suite *s = suite_create("Address");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_address_new);

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
