AC_PREREQ([2.69])
AC_INIT([AddressBook], [0.1], [david@craven.ch])

AC_CONFIG_MACRO_DIR([m4])

AM_PROG_AR
AM_INIT_AUTOMAKE([foreign subdir-objects dist-xz -Wall -Werror])

LT_INIT

AX_CHECK_COMPILE_FLAG([-std=gnu11],
  [AX_APPEND_FLAG([-std=gnu11])],
  [AC_MSG_WARN([-std=gnu11 not supported, you may have to set CFLAGS to enable C11 support.])
])

AX_CHECK_COMPILE_FLAG([-Wall], [AX_APPEND_FLAG([-Wall])])
# AX_CHECK_COMPILE_FLAG([-Werror], [AX_APPEND_FLAG([-Werror])])


AX_VALGRIND_DFLT([sgcheck], [off])
AX_VALGRIND_CHECK

# Check for programs.
AC_PROG_CC


# Check for libraries.
AC_SUBST(CHECK_LIBS)
AC_SUBST(CHECK_CFLAGS)
if pkg-config --atleast-version=0.10.0 check; then
   CHECK_CFLAGS=`pkg-config --cflags check`
   CHECK_LIBS=`pkg-config --libs check`
else
  AC_MSG_ERROR(Run 'guix environment --pure -l guix.scm' or install check)
fi


AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_OUTPUT
