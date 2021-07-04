# Copyright (c) 1998 Cygnus Support
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

DESTDIR =
VPATH = ../../../../newlib-3.3.0/libgloss/libnosys
srcdir = ../../../../newlib-3.3.0/libgloss/libnosys
objdir = .
srcroot = $(srcdir)/../..
objroot = $(objdir)/../..

prefix = /usr
exec_prefix = ${prefix}

host_alias = i386-banana
target_alias = i386-banana
program_transform_name = s&^&i386-banana-&

bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib
tooldir = $(exec_prefix)/$(target_alias)

# Multilib support variables.
# TOP is used instead of MULTI{BUILD,SRC}TOP.
MULTIDIRS = 
MULTISUBDIR = 
MULTIDO = true
MULTICLEAN = true

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = /usr/bin/install -c
INSTALL_DATA = /usr/bin/install -c -m 644

SHELL =	/bin/sh

CC = i386-banana-gcc -B/cygdrive/d/Users/Alex/Desktop/Banana/Libraries/build-newlib/i386-banana/newlib/ -isystem /cygdrive/d/Users/Alex/Desktop/Banana/Libraries/build-newlib/i386-banana/newlib/targ-include -isystem /cygdrive/d/Users/Alex/Desktop/Banana/Libraries/newlib-3.3.0/newlib/libc/include -B/cygdrive/d/Users/Alex/Desktop/Banana/Libraries/build-newlib/i386-banana/libgloss/i386 -L/cygdrive/d/Users/Alex/Desktop/Banana/Libraries/build-newlib/i386-banana/libgloss/libnosys -L/cygdrive/d/Users/Alex/Desktop/Banana/Libraries/newlib-3.3.0/libgloss/i386   

#AS = i386-banana-as
AS = `if [ -f ${objroot}/../gas/as-new ] ; \
	then echo ${objroot}/../gas/as-new ; \
	else echo as ; fi`

AR = i386-banana-ar

#LD = i386-banana-ld
LD = `if [ -f ${objroot}/../ld/ld-new ] ; \
	then echo ${objroot}/../ld/ld-new ; \
	else echo ld ; fi`

RANLIB = i386-banana-ranlib

OBJDUMP = `if [ -f ${objroot}/../binutils/objdump ] ; \
	then echo ${objroot}/../binutils/objdump ; \
	else t='$(program_transform_name)'; echo objdump | sed -e $$t ; fi`
OBJCOPY = `if [ -f ${objroot}/../binutils/objcopy ] ; \
	then echo ${objroot}/../binutils/objcopy ; \
	else t='$(program_transform_name)'; echo objcopy | sed -e $$t ; fi`

# object files needed
OBJS = chown.o close.o environ.o errno.o execve.o fork.o fstat.o \
	getpid.o gettod.o isatty.o kill.o link.o lseek.o open.o \
	read.o readlink.o sbrk.o stat.o symlink.o times.o unlink.o \
	wait.o write.o _exit.o

# Object files specific to particular targets.
EVALOBJS = ${OBJS}

GCC_LDFLAGS = `if [ -d ${objroot}/../gcc ] ; \
	then echo -L${objroot}/../gcc ; fi`

OUTPUTS = libnosys.a
SPECS = ${srcdir}/nosys.specs

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

all: ${OUTPUTS}

#
# here's where we build the library for each target
#

libnosys.a: $(EVALOBJS)
	${AR} ${ARFLAGS} $@ $(EVALOBJS)
	${RANLIB} $@

doc:	

clean mostlyclean:
	rm -f $(OUTPUTS) *.i *~ *.o *-test *.srec *.dis *.map *.x

distclean maintainer-clean realclean: clean
	rm -f Makefile config.status $(OUTPUTS)

.PHONY: install info install-info clean-info
install:
	@for outputs in ${OUTPUTS} ${SPECS}; do\
	 mkdir -p $(DESTDIR)$(tooldir)/lib${MULTISUBDIR}; \
	 $(INSTALL_DATA) $${outputs} $(DESTDIR)$(tooldir)/lib${MULTISUBDIR}; \
	done

info:
install-info:
clean-info:

Makefile: Makefile.in config.status ../../../../newlib-3.3.0/libgloss/libnosys/../config/default.mh
	$(SHELL) config.status

config.status: configure
	$(SHELL) config.status --recheck
