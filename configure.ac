AC_PREREQ([2.59])
AC_INIT([liblogtext], [0.1], [kmx.io], [liblogtext], [http://kmx.io/])
CFLAGS="$CFLAGS -W -Wall -Werror"
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])
AC_CONFIG_SRCDIR([logtext.c])
AC_CONFIG_HEADERS([config.h:config.h.in])

AM_INIT_AUTOMAKE
AM_PROG_AR

AC_PROG_CC

LT_INIT()

PKG_PROG_PKG_CONFIG([0.25])

if test -d /usr/local/include; then
  CPPFLAGS="$CPPFLAGS -I/usr/local/include"
fi
if test -d /usr/local/lib; then
  LDFLAGS="$LDFLAGS -L/usr/local/lib"
fi

if test -d /usr/include; then
  CPPFLAGS="$CPPFLAGS -I/usr/include"
fi
if test -d /usr/lib; then
  LDFLAGS="$LDFLAGS -L/usr/lib"
fi

AC_SEARCH_LIBS([libdata_init], [data],
               [],
               [AC_MSG_ERROR([missing libdata for liblogtext"])])

LIBS=

AC_ARG_ENABLE(debug,
  AS_HELP_STRING([--enable-debug],
                 [enable debugging, default: yes]),
  [case "${enableval}" in
     yes) debug=true ;;
      no) debug=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]);;
   esac],
  [debug=true])
AM_CONDITIONAL([DEBUG], [test x"$debug" = x"true"])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

cat dependencies.mk >> Makefile
