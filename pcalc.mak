#---------------------------------------------------------------------
#
#       pcalc makefile for MSC 'nmake' utility.
#

#---------------------------------------------------------------------
#               definition

PROGRAM         = pcalc.exe
MSC             = cl
CFLAGS          = -c -Ox -W2
INCL            = -I.
CC              = $(MSC) $(CFLAGS) $(INCL)
YACC            = bison -ld
LEX             = flex
HEADERS         = pcalc.h hocdecl.h

OBASE0           = pcalc
OBASE1           = pcalcl
OBASE2           = funct
OBASE3           = math
OBASE4           = symbol
OBASE5           = help
OBASE6           = store
OBASE7           = print
OBASE8           = str
OBASE9           = convert

OBJS0            = $(OBASE0).obj
OBJS1            = $(OBASE1).obj
OBJS2            = $(OBASE2).obj
OBJS3            = $(OBASE3).obj
OBJS4            = $(OBASE4).obj
OBJS5            = $(OBASE5).obj
OBJS6            = $(OBASE6).obj
OBJS7            = $(OBASE7).obj
OBJS8            = $(OBASE8).obj
OBJS9            = $(OBASE9).obj

#---------------------------------------------------------------------
#               construction rules

.c.obj:
                $(CC) $*.c

#---------------------------------------------------------------------
#               dependencies


pcalc.exe:      $(OBJS0) $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) \
                $(OBJS6) $(OBJS7) $(OBJS8) $(OBJS9)
                link $(OBJS0) $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) \
                $(OBJS6) $(OBJS7) $(OBJS8) $(OBJS9),,, /NOI /STACK:0x8000 ;

pcalc.obj:      pcalc.y
                $(YACC) $*.y
                $(CC) $*.c

pcalcl.obj:     pcalcl.l
                $(LEX) $*.l
                $(CC) -Fopcalcl.obj lexyy.c


$(OBASE2).obj:   $(OBASE2).c $(HEADERS)

$(OBASE3).obj:   $(OBASE3).c $(HEADERS)

$(OBASE4).obj:   $(OBASE4).c $(HEADERS)

$(OBASE5).obj:   $(OBASE5).c $(HEADERS)
