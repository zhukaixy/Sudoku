dnl $Id$
dnl config.m4 for extension phpsudoku

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(phpsudoku, for phpsudoku support,
dnl Make sure that the comment is aligned:
dnl [  --with-phpsudoku             Include phpsudoku support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(phpsudoku, whether to enable phpsudoku support,
dnl Make sure that the comment is aligned:
[  --enable-phpsudoku           Enable phpsudoku support])

if test "$PHP_PHPSUDOKU" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-phpsudoku -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/phpsudoku.h"  # you most likely want to change this
  dnl if test -r $PHP_PHPSUDOKU/$SEARCH_FOR; then # path given as parameter
  dnl   PHPSUDOKU_DIR=$PHP_PHPSUDOKU
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for phpsudoku files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PHPSUDOKU_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PHPSUDOKU_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the phpsudoku distribution])
  dnl fi

  dnl # --with-phpsudoku -> add include path
  dnl PHP_ADD_INCLUDE($PHPSUDOKU_DIR/include)

  dnl # --with-phpsudoku -> check for lib and symbol presence
  dnl LIBNAME=phpsudoku # you may want to change this
  dnl LIBSYMBOL=phpsudoku # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PHPSUDOKU_DIR/$PHP_LIBDIR, PHPSUDOKU_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PHPSUDOKULIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong phpsudoku lib version or lib not found])
  dnl ],[
  dnl   -L$PHPSUDOKU_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PHPSUDOKU_SHARED_LIBADD)

  PHP_NEW_EXTENSION(phpsudoku, phpsudoku.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
