
ACLOCAL_AMFLAGS = -I build-aux/m4

bin_PROGRAMS =
CLEANFILES =
include_HEADERS =
lib_LTLIBRARIES =

AM_CPPFLAGS = ${local_cppflags}
AM_LDFLAGS = ${local_ldflags} -L./.libs

if DEBUG
AM_CFLAGS = -DDEBUG -O0 -ggdb
else
AM_CFLAGS = -DNDEBUG -O2
endif

lib_LTLIBRARIES += liblogtext.la
liblogtext_la_SOURCES = \
	logtext.c
include_HEADERS += \
	logtext.h

deps_headers = ${include_HEADERS}
deps_sources = \
	${liblogtext_la_SOURCES}

dependencies.mk: ${deps_headers} ${deps_sources}
	${CC} ${CPPFLAGS} ${CFLAGS} -M *.c > dependencies.mk.1
	sed -e 's/^\(.*\)[.]o:/\1.$$(OBJEXT) \1.lo:/' dependencies.mk.1 > dependencies.mk.2
	rm dependencies.mk.1
	mv dependencies.mk.2 dependencies.mk
CLEANFILES += dependencies.mk.1 dependencies.mk.2
