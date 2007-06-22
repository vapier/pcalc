#---------------------------------------------------------------------
# pcalc 
#
# Makefile for Linux. Please let me know if you port pcalc.
#

#CFLAGS      	= -ggdb
#CC             = $(MSC) $(CFLAGS) $(INCL)
CC              = cc 
YACC            = bison -ld
LEX             = flex

OS0        	= pcalc
OS1           	= pcalcl
OS2           	= funct
OS3           	= math
OS4           	= symbol
OS5           	= help
OS6           	= store
OS7           	= print
OS8           	= str
OS9           	= convert

OB0            	= $(OS0).o
OB1            	= $(OS1).o
OB2            	= $(OS2).o
OB3            	= $(OS3).o
OB4            	= $(OS4).o
OB5            	= $(OS5).o
OB6            	= $(OS6).o
OB7            	= $(OS7).o
OB8            	= $(OS8).o
OB9            	= $(OS9).o

# Our target:

pcalc:  $(OB0) $(OB1) $(OB2) $(OB3) $(OB4) $(OB5) $(OB6) $(OB7) $(OB8) $(OB9)
	$(CC) $(CFLAGS) $(OB0) $(OB1) $(OB2) $(OB3) $(OB4) $(OB5) $(OB6) $(OB7) $(OB8) $(OB9) -o pcalc -lm -lfl

pcalc.c: pcalc.y
	$(YACC) pcalc.y -o pcalc.c

pcalcl.o: pcalcl.l
	$(LEX) -opcalcl.c pcalcl.l 
	$(CC) $(CFLAGS) -c pcalcl.c -o pcalcl.o

# Just a standard clean

clean:
	rm -f *.o
	rm -f *~
	rm -f *.var
	rm -f ptest/*~
	rm -f core
	rm -f y.output

# Force LEX and YACC rebuild

yacclean: clean
	rm -f pcalc.tab.c
	rm -f lexyy.c

# Rudimentary test, for good measure

test: 
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

install:
	install pcalc /usr/bin

# Pack up for distribution:

pack:	clean
	./pack

