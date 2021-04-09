# Top level makefile for libgloss
#
# Copyright (c) 1995, 1996 Cygnus Support
#
# The authors hereby grant permission to use, copy, modify, distribute,
# and license this software and its documentation for any purpose, provided
# that existing copyright notices are retained in all copies and that this
# notice is included verbatim in any distributions. No written agreement,
# license, or royalty fee is required for any of the authorized uses.
# Modifications to this software may be copyrighted by their authors
# and need not follow the licensing terms described here, provided that
# the new terms are clearly indicated on the first page of each file where
# they apply.
#

DESTDIR =
VPATH = ../../../newlib-3.3.0/libgloss
srcdir = ../../../newlib-3.3.0/libgloss
objdir = .
srcroot = $(srcdir)/../..
objroot = $(objdir)/../..

prefix = /usr
exec_prefix = ${prefix}

host_alias = i386-banana
target_alias = i386-banana

bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib
tooldir = $(exec_prefix)/$(target_alias)

TOP = .
SRCTOP = .

# Multilib support variables.
# TOP is used instead of MULTI{BUILD,SRC}TOP.
MULTISRCTOP =
MULTIBUILDTOP =
MULTIDIRS =
MULTISUBDIR =
MULTIDO = true
MULTICLEAN = true

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = /usr/bin/install -c
INSTALL_DATA = /usr/bin/install -c -m 644

SHELL =	/bin/sh

CC = i386-banana-gcc -B/cygdrive/d/Users/Alex/Desktop/Banana/libraries/build-newlib/i386-banana/newlib/ -isystem /cygdrive/d/Users/Alex/Desktop/Banana/libraries/build-newlib/i386-banana/newlib/targ-include -isystem /cygdrive/d/Users/Alex/Desktop/Banana/libraries/newlib-3.3.0/newlib/libc/include -B/cygdrive/d/Users/Alex/Desktop/Banana/libraries/build-newlib/i386-banana/libgloss/i386 -L/cygdrive/d/Users/Alex/Desktop/Banana/libraries/build-newlib/i386-banana/libgloss/libnosys -L/cygdrive/d/Users/Alex/Desktop/Banana/libraries/newlib-3.3.0/libgloss/i386   

AS = i386-banana-as
AR = i386-banana-ar
LD = i386-banana-ld
RANLIB = i386-banana-ranlib

AR_FLAGS = qv
BISON = bison
MAKEINFO = makeinfo

SUBDIRS =  doc libnosys

.NOEXPORT:
MAKEOVERRIDES=

# Host specific makefile fragment comes in here.
NEWLIB_CFLAGS = `if [ -d ${objroot}/newlib ]; then echo -I${objroot}/newlib/targ-include -I${srcroot}/newlib/libc/include; fi`
NEWLIB_LDFLAGS = `if [ -d ${objroot}/newlib ]; then echo -B${objroot}/newlib/ -L${objroot}/newlib/; fi`

INCLUDES = -I. -I$(srcdir)/..
# Note that when building the library, ${MULTILIB} is not the way multilib
# options are passed; they're passed in $(CFLAGS).
CFLAGS_FOR_TARGET = -O2 -g ${MULTILIB} ${INCLUDES} ${NEWLIB_CFLAGS}
LDFLAGS_FOR_TARGET = ${MULTILIB} ${NEWLIB_LDFLAGS}
AR_FLAGS = rc

.c.o:
	$(CC) $(CFLAGS_FOR_TARGET) -O2 $(INCLUDES) -c $(CFLAGS) $<

.C.o:
	$(CC) $(CFLAGS_FOR_TARGET) -O2 $(INCLUDES) -c $(CFLAGS) $<
.s.o:
	$(AS) $(ASFLAGS_FOR_TARGET) $(INCLUDES) $(ASFLAGS) -o $*.o $<

#
# GCC knows to run the preprocessor on .S files before it assembles them.
#
.S.o:
	$(CC) $(CFLAGS_FOR_TARGET) $(INCLUDES) $(CFLAGS) -c $<

#
# this is a bogus target that'll produce an assembler from the
# C source with the right compiler options. this is so we can
# track down code generation or debug symbol bugs.
#
.c.s:
	$(CC) $(CFLAGS_FOR_TARGET) -S $(INCLUDES) $(CFLAGS) $<

# These are roughly topologically sorted in order to make porting more
# streamlined.
FLAGS_TO_PASS = \
	"CC=$(CC)" \
	"CFLAGS=$(CFLAGS)" \
	"CFLAGS_FOR_TARGET=$(CFLAGS_FOR_TARGET)" \
	"CCASFLAGS=$(CCASFLAGS)" \
	"AR=$(AR)" \
	"RANLIB=$(RANLIB)" \
	"AR_FLAGS=$(AR_FLAGS)" \
	"MAKEINFO=$(MAKEINFO)" \
	"AS=$(AS)" \
	"LD=$(LD)" \
	"CROSS_CFLAGS=$(CROSS_CFLAGS)" \
	"TARGET_CFLAGS=$(TARGET_CFLAGS)" \
	"exec_prefix=$(exec_prefix)" \
	"prefix=$(prefix)" \
	"tooldir=$(tooldir)" \
	"infodir=$(infodir)" \
	"libdir=$(libdir)" \
	"top_toollibdir=$(toollibdir)" \
	"INSTALL=$(INSTALL)" \
	"INSTALL_PROGRAM=$(INSTALL_PROGRAM)" \
	"INSTALL_DATA=$(INSTALL_DATA)" \
	"DESTDIR=$(DESTDIR)"

all: stmp-bsp force
	+@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MULTIDO) $(FLAGS_TO_PASS) multi-do DO=all

stmp-bsp: force
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	for dir in .. ${SUBDIRS}; do \
	  if [ x$$dir != x.. ]; then \
	    if [ -d $$dir ]; then \
	      (cd $$dir; $(MAKE) $(FLAGS_TO_PASS)) || exit $$?; \
	    else true; fi; \
	  else true; fi; \
	done

install: force
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	for dir in .. ${SUBDIRS}; do \
	  if [ x$$dir != x.. ]; then \
	    if [ -d $$dir ]; then \
	      (cd $$dir; $(MAKE) $(FLAGS_TO_PASS) install) || exit $$?; \
	    else true; fi; \
	  else true; fi; \
	done
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MULTIDO) $(FLAGS_TO_PASS) multi-do DO=install

test: force
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	for dir in .. ${SUBDIRS}; do \
	  if [ x$$dir != x.. ]; then \
	    if [ -d $$dir ]; then \
	      (cd $$dir; $(MAKE) $(FLAGS_TO_PASS) test); \
	    else true; fi; \
	  else true; fi; \
	done
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MULTIDO) $(FLAGS_TO_PASS) multi-do DO=test

clean-here:
	-rm -f *~ core *.o a.out xgdb *.x

clean mostlyclean: clean-here
	rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) DO=$@ DODIRS="$(SUBDIRS)" $(FLAGS_TO_PASS) subdir_do; \
	$(MULTICLEAN) multi-clean DO=$@

distclean maintainer-clean realclean: clean-here
	-rm -f Makefile config.cache config.log config.status 
	-rm -f *-init.exp site.*
	-rm -fr *.log summary detail *.sum
	rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) DO=$@ DODIRS="$(SUBDIRS)" $(FLAGS_TO_PASS) subdir_do; \
	$(MULTICLEAN) multi-clean DO=$@

.PHONY: info install-info clean-info html pdf
subdir_do:
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	for i in .. $(DODIRS); do \
	  if [ x$$i != x.. ]; then \
	    if [ -f ./$$i/Makefile ]; then \
	      if (cd ./$$i; $(MAKE) $(FLAGS_TO_PASS) $(DO)); then \
		true; \
	      else \
		exit 1; \
	      fi; \
	    else true; fi; \
	  else true; fi; \
	done

info dvi html pdf docs:
	rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) DO=$@ DODIRS=doc $(FLAGS_TO_PASS) subdir_do

install-info:
	rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) DO=$@ DODIRS=doc $(FLAGS_TO_PASS) subdir_do

install-html:
	rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) DO=$@ DODIRS=doc $(FLAGS_TO_PASS) subdir_do

install-pdf:
	rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) DO=$@ DODIRS=doc $(FLAGS_TO_PASS) subdir_do

clean-info:

force:

Makefile: Makefile.in config.status ../../../newlib-3.3.0/libgloss/config/default.mh
	$(SHELL) config.status

config.status: configure
	$(SHELL) config.status --recheck
