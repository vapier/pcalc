#---------------------------------------------------------------------
# pcalc 
#
# Makefile for Linux. Please let me know if you port pcalc.
#

VERSION = 2

CC   ?= cc
YACC  = bison -ld
LEX   = flex

CFLAGS   ?= -ggdb
CFLAGS   += -Wall
CPPFLAGS += -DVERSION='"$(VERSION)"'
LDLIBS   += -lm -lfl

SRCS = pcalc pcalcl funct math symbol help store print str convert
OBJS = $(patsubst %,%.o,$(SRCS))

all: pcalc

pcalc: $(OBJS)

pcalc.c: pcalc.y
	$(YACC) -o $@ $<

pcalcl.c: pcalcl.l
	$(LEX) -o $@ $<

clean:
	rm -f *.o *~ *.var ptest/*~ core y.output pcalc

distclean: clean
	rm -f pcalc.tab.c lexyy.c pcalcl.c pcalc.c pcalc.h

check test: pcalc
	$(MAKE) -C ptest check

INSTALL = install
BINDIR  = /usr/bin
DESTDIR = 
install:
	$(INSTALL) -m 755 -D pcalc $(DESTDIR)$(BINDIR)/pcalc

dist pack: distclean
	rm -rf pcalc-$(VERSION)
	svn export . pcalc-$(VERSION)
	svn log -v -r 1:HEAD > pcalc-$(VERSION)/ChangeLog
	$(MAKE) -C pcalc-$(VERSION) pcalc.c pcalcl.c
	$(MAKE) -C pcalc-$(VERSION)/ptest testsuite
	tar cf - pcalc-$(VERSION) | lzma > pcalc-$(VERSION).tar.lzma
	rm -rf pcalc-$(VERSION)

distcheck: dist
	lzcat pcalc-$(VERSION).tar.lzma | tar xf -
	$(MAKE) -C pcalc-$(VERSION) clean all check
	env CFLAGS=-O2 $(MAKE) -C pcalc-$(VERSION) clean all check
	rm -rf pcalc-$(VERSION)

.PHONY: all check clean dist distcheck distclean install pack test
