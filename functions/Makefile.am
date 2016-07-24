AM_CFLAGS =					\
	$(GROONGA_CFLAGS)

AM_LDFLAGS =					\
	-avoid-version				\
	-module					\
	-no-undefined

LIBS =						\
	$(GROONGA_LIBS)

functions_plugins_LTLIBRARIES =
functions_plugins_LTLIBRARIES += score_boost.la

functions_plugins_SOURCE =			\
	score_boost.c
