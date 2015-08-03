# ============================================================
# NOTE: from https://raw.githubusercontent.com/MapQuest/avecado/master/m4/mapnik.m4
#
# Copyright (c) 2014, MapQuest Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer. 
#
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#
# ============================================================
# Check for mapnik
#
# Looks for mapnik-config, which should be installed by the
# dev package and checks the version against the requirement.
#
# If it succeeds, it calls:
#   AC_SUBST(MAPNIK_CPPFLAGS) and AC_SUBST(MAPNIK_LIBS)
# and sets HAVE_MAPNIK, MAPNIK_DEFAULT_FONT_DIR and
# MAPNIK_DEFAULT_INPUT_PLUGIN_DIR.

AC_DEFUN([REQUIRE_MAPNIK],
[
AC_ARG_WITH([mapnik-config],
  [AS_HELP_STRING([--with-mapnik-config=PATH],
    [full path to mapnik-config program.])],
  [
  if test -n "$withval" ; then
    ac_mapnik_config_path="$withval"
  fi
  ],
  [ac_mapnik_config_path=""])

mapnik_version_req=ifelse([$1], ,2.3.0,$1)
mapnik_version_req_major=`expr $mapnik_version_req : '\([[0-9]]*\)'`
mapnik_version_req_minor=`expr $mapnik_version_req : '[[0-9]]*\.\([[0-9]]*\)'`
mapnik_version_req_sub_minor=`expr $mapnik_version_req : '[[0-9]]*\.[[0-9]]*\.\([[0-9]]*\)'`
if test "x$mapnik_version_req_sub_minor" = "x" ; then
   mapnik_version_req_sub_minor="0"
fi

dnl First, check for the mapnik-config shell script which should be installed
dnl by whatever development package installs mapnik.

if test "x$ac_mapnik_config_path" = "x" ; then
   AC_PATH_PROG([MAPNIK_CONFIG],[mapnik-config])
else
   MAPNIK_CONFIG="$ac_mapnik_config_path"
fi

AC_MSG_CHECKING(for mapnik-config)
if test -x "$MAPNIK_CONFIG"; then
   AC_MSG_RESULT([yes])
else
   AC_MSG_RESULT([no])
   AC_MSG_ERROR([cannot find mapnik-config in your path, but it is required for building avecado. Please install mapnik-dev.])
fi

dnl Check that the version supplied by mapnik-config satisfies the
dnl minimum version given in the argument.

AC_MSG_CHECKING(for mapnik >= $mapnik_version_req)
succeeded=no

mapnik_version=`$MAPNIK_CONFIG --version`
mapnik_version_major=`expr $mapnik_version : '\([[0-9]]*\)'`
mapnik_version_minor=`expr $mapnik_version : '[[0-9]]*\.\([[0-9]]*\)'`
mapnik_version_sub_minor=`expr $mapnik_version : '[[0-9]]*\.[[0-9]]*\.\([[0-9]]*\)'`
if test "x$mapnik_version_sub_minor" = "x" ; then
   mapnik_version_sub_minor="0"
fi

if test $mapnik_version_major -gt $mapnik_version_req_major ; then
   succeeded=yes

elif test $mapnik_version_major -eq $mapnik_version_req_major ; then
   if test $mapnik_version_minor -gt $mapnik_version_req_minor ; then
     succeeded=yes

   elif test $mapnik_version_minor -eq $mapnik_version_req_minor ; then
      if test $mapnik_version_sub_minor -ge $mapnik_version_req_sub_minor ; then
         succeeded=yes
      fi
   fi
fi

if test "x$succeeded" = "xyes" ; then
   AC_MSG_RESULT([yes])
else
   AC_MSG_RESULT([no])
   AC_MSG_ERROR([found mapnik $mapnik_version, but require >= $mapnik_version_req])
fi

dnl Set up environment variables and autoconf substitutions

MAPNIK_CPPFLAGS=`$MAPNIK_CONFIG --cflags`
MAPNIK_LIBS="`$MAPNIK_CONFIG --dep-libs` `$MAPNIK_CONFIG --libs`"
AC_SUBST(MAPNIK_CPPFLAGS)
AC_SUBST(MAPNIK_LIBS)
AC_DEFINE(HAVE_MAPNIK,,[define if Mapnik is available])
AC_DEFINE_UNQUOTED(MAPNIK_DEFAULT_FONT_DIR,"`$MAPNIK_CONFIG --fonts`",
  [Mapnik default fonts directory.])
AC_DEFINE_UNQUOTED(MAPNIK_DEFAULT_INPUT_PLUGIN_DIR,"`$MAPNIK_CONFIG --input-plugins`",
  [Mapnik default input plugins directory.])

])
