#---------------------------------------------------------------------
# pcalc 
#
# Makefile for Linux. Please let me know if you port pcalc.
#

VERSION = 5

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
pcalc: LDFLAGS += $(CFLAGS)

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
	git archive --prefix=pcalc-$(VERSION)/ HEAD | tar xf -
	git log --stat > pcalc-$(VERSION)/ChangeLog
	$(MAKE) -C pcalc-$(VERSION) pcalc.c pcalcl.c
	$(MAKE) -C pcalc-$(VERSION)/ptest testsuite
	tar cf - pcalc-$(VERSION) | xz > pcalc-$(VERSION).tar.xz
	rm -rf pcalc-$(VERSION)

distcheck: dist
	xzcat pcalc-$(VERSION).tar.xz | tar xf -
	set -e; \
	for t in clean all check; do $(MAKE) -C pcalc-$(VERSION) $$t; done; \
	for t in clean all check; do env CFLAGS=-O2 $(MAKE) -C pcalc-$(VERSION) $$t; done
	rm -rf pcalc-$(VERSION)

.PHONY: all check clean dist distcheck distclean install pack test
