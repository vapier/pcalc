#---------------------------------------------------------------------
# pcalc 
#
# Makefile for Linux. Please let me know if you port pcalc.
#

VERSION = 1.1

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
	rm -f *.o *~ *.var ptest/*~ core y.output

distclean: clean
	rm -f pcalc.tab.c lexyy.c

check test: pcalc
	mv -f pcalc.var pcalc.old; rm -f *.var 
	./pcalc @ptest/pcalc.001 > testdata
	./pcalc @ptest/pcalc.002 >>testdata
	./pcalc @ptest/pcalc.003 >>testdata
	./pcalc @ptest/pcalc.004 >>testdata
	./pcalc @ptest/pcalc.005 >>testdata
	./pcalc @ptest/pcalc.006 >>testdata
	./pcalc @ptest/pcalc.007 >>testdata
	./pcalc @ptest/pcalc.008 >>testdata
	./pcalc @ptest/pcalc.009 >>testdata
	@diff testdata testorig

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
	tar jcf pcalc-$(VERSION).tar.bz2 pcalc-$(VERSION)
	rm -rf pcalc-$(VERSION)

distcheck: dist
	tar jxf pcalc-$(VERSION).tar.bz2
	$(MAKE) -C pcalc-$(VERSION) all check
	rm -rf pcalc-$(VERSION)

.PHONY: all check clean dist distcheck distclean install pack test
