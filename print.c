
/* =====[ print.c ]=========================================================

   Description:  Printer routines for pcalc.

   Revisions:

      REV     DATE     BY           DESCRIPTION
      ----  --------  ----------    --------------------------------------
      0.00  mm/dd/95  Peter Glen    Initial version.
      1.00  22/9/98   Peter Glen    Unix port

   ======================================================================= */

/* -------- System includes:  -------------------------------------------- */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* -------- Includes:  --------------------------------------------------- */

#include "hocdecl.h"
#include "symbol.h"

/* -------- Forward references for procedures: --------------------------- */

static void long_to_bin_str(unsigned long num, char *str);

/* -------- Implementation: ---------------------------------------------- */

static char work_str[128];

void    print_num(double var)

{
    Symbol *msx  = lookup_sym("DEC");
    
    // compatibility variable:

    if(!msx)
      msx  = lookup_sym("DECIMAL");
    
    if(msx && msx->u.val == 1)
      {
	printf("%g" , var);
      }
    else if(msx && msx->u.val == 2)
      {
	printf("%lx" , (long)var);
      }
    else if(msx && msx->u.val == 3)
      {
	long_to_bin_str((long)var, work_str);
	printf("%s", work_str);
      }
    else
      {
	long_to_bin_str((long)var, work_str);
	printf("\t%-8.8g\t0x%-8lx\t0y%s\n" , var, (long)var, work_str);
      }
}

/*
 * Convert an unsigned long to a string representation in binary
 *
 */

extern int fNibble;

static void long_to_bin_str(unsigned long num, char *str)
{
    size_t i;
    char tmp_str[sizeof(num) * 8 * 2 + 1];
    char *p = tmp_str + sizeof(tmp_str) - 1;

    if (num == 0)                                          /* dummy result */
        {
        strcpy(str, "0");
        return;
        }

    *p-- = '\0';                                              /* terminate */

    for (i = 0; i < sizeof(num) * 8; ++i)
        {
        unsigned long bit = (unsigned long)1 << i;
        *p-- = (num & bit ? '1' : '0');

        if (fNibble && (i + 1) % 4 == 0)
            *p-- = ' ';
        }
    *p = ' ';

    while (*p == '0' || *p == ' ')                   /* skip leading zeros */
        ++p;

    if (fNibble)                                /* fill out leading nibble */
        {
        for (i = 1; p[i] && p[i] != ' '; ++i)
            continue;
        while (i++ < 4)
            *--p = '0';
        }

    strcpy(str, p);                                       /* output result */
}

/* EOF */
