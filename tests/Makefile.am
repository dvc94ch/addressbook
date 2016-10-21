TESTS = check_list check_menu
check_PROGRAMS = check_list check_menu

check_list_SOURCES = list.c
check_list_CFLAGS = @CHECK_CFLAGS@
check_list_LDADD = $(top_builddir)/src/libaddressbook.la @CHECK_LIBS@

check_menu_SOURCES = menu.c
check_menu_CFLAGS = @CHECK_CFLAGS@
check_menu_LDADD = $(top_builddir)/src/libaddressbook.la @CHECK_LIBS@

@VALGRIND_CHECK_RULES@
