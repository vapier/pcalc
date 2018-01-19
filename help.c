
/* =====[ help.c ]=========================================================

   Description:  Help file for pcalc

   Revisions:

      REV     DATE     BY           DESCRIPTION
      ----  --------  ----------    --------------------------------------
      0.00  mm/dd/95  Peter Glen    Initial version.

   ======================================================================= */

/* -------- System includes:  -------------------------------------------- */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "help.h"

/* -------- Implementation: ---------------------------------------------- */

void    basehelp(void)

{

        printf("\
Functions:\n\
    SIN   COS   ATAN   LOG    LOG10   EXP   SQRT   INT   ABS\n\
    F2C   C2F   IN2MM  MM2IN  PO2KG   KG2PO\n\
\n\
Operators:\n\
    '=' '+' '-' '*' '/' '%%' '^'\n\
    '~' or and xor '<<' '>>'\n\
\n\
Constants: (case sensitive)\n\
    PI      E       GAMMA   DEG     PHI   \n\
\n\
Values:\n\
    0x...   0b...   0y...   0c...   0o...\n\
\n\
");
}

void    funchelp(void)

{
        printf("\
Functions: (case insensitive)\n\
\n\
    SIN         math sinus              COS        math cos   \n\
    ATAN        math atan               LOG        math log   \n\
    LOG10       math log10              EXP        math exp   \n\
    SQRT        math sqrt               INT        math int   \n\
    ABS         math abs                                      \n\
\n\
    F2C         converting temperature -> fahrenheit to celsius \n\
    C2F         converting temperature -> celsius to fahrenheit \n\
    IN2MM       converting length      -> inches to millimeter \n\
    MM2IN       converting length      -> millimeter to inches\n\
    PO2KG       converting mass        -> pounds to kilogram\n\
    KG2PO       converting mass        -> kilogram to pounds\n\
\n\
");
}

void    ophelp(void)

{
        printf("\
Operator priorities:\n\
\n\
    right  association:     '='         ASSIGNMENT\n\
    right  association:     '~'         BINARY NEGATION\n\
    left   association:     or          BINARY OR\n\
    left   association:     and         BINARY AND\n\
    left   association:     xor         BINARY XOR\n\
    left   association:     '<<' '>>'   BINARY LEFT/RIGHT SHIFT\n\
    left   association:     '+' '-'     ADDITION/SUBTRACTION\n\
    left   association:     '*' '/' '%%' MULTIPLY/DIVIDE\n\
    left   association:     '-'         UNARY MINUS\n\
    right  association:     '^'         EXPONENTATION\n\
\n\
");
}

void    conshelp(void)

{
        printf("\
Constants:\n\
\n\
    PI      3.14159265358979323846\n\
    E       2.71828182845904523536\n\
    GAMMA   0.57721566490153286060\n\
    DEG     57.29577951308322087680\n\
    PHI     1.61803389974989484820\n\
\n\
Values:\n\
    0x...   Hex number\n\
    0b...   Binary number\n\
    0y...   Binary number\n\
    0c...   Octal number\n\
    0o...   Octal number\n\
    ...     Decimal number\n\
\n\
");
}


void    cbhelp(void)

{
        printf("\
Controls:\n\
\n\
    date    -echo string, expanding date (strftime compatible)\n\
    echo    -echo string.\n\
    _echo   -echo string without training new line.\n\
    store   -store variable to file.\n\
    restore -restore variable from file.\n\
\n\
Built in variables:\n\
\n\
    DEBUG           for debug\n\
    DECIMAL         controlling number display\n\
                    0 = normal, 1 = DEC 2 = HEX, 3 = BIN, 4 = OCT\n\
\n\
");
}


void    help_help(void)

{

        printf("\
For everything type pcalc e\n\
For functions  type pcalc f\n\
For controls   type pcalc l\n\
For operators  type pcalc o\n\
For constants  type pcalc c\n\
");

}


/* EOF */



