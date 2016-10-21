TESTS = check_address check_list check_menu
check_PROGRAMS = check_address check_list check_menu

check_address_SOURCES = address.c
check_address_CFLAGS = @CHECK_CFLAGS@
check_address_LDADD = $(top_builddir)/src/libaddressbook.la @CHECK_LIBS@

check_list_SOURCES = list.c
check_list_CFLAGS = @CHECK_CFLAGS@
check_list_LDADD = $(top_builddir)/src/libaddressbook.la @CHECK_LIBS@

check_menu_SOURCES = menu.c
check_menu_CFLAGS = @CHECK_CFLAGS@
check_menu_LDADD = $(top_builddir)/src/libaddressbook.la @CHECK_LIBS@

@VALGRIND_CHECK_RULES@
