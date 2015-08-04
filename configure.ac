AC_INIT([vecamole],
	[0.0.1],
	[https://github.com/zerebubuth/vecamole/issues],
	[vecamole-0.0.1],
	[https://github.com/zerebubuth/vecamole])
AM_INIT_AUTOMAKE([subdir-objects parallel-tests])
LT_INIT
AC_SUBST([LIBTOOL_DEPS])

AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS([include/vecamole/config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_CHECK_PROG([HAVE_PERL],[perl],[yes],[no])
if test "x$HAVE_PERL" = "xno"; then
   AC_MSG_ERROR([cannot find Perl program, but this is required. Please install the perl package])
fi

AC_HEADER_STDC
AC_LANG_CPLUSPLUS
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])
AX_BOOST_BASE([1.54],,[AC_MSG_ERROR([cannot find Boost libraries, but these are required. Please install libboost-dev or similar package >= 1.56])])

REQUIRE_MAPNIK([3.0.2])
REQUIRE_PROTOC

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
