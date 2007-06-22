
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

void    long_to_bin_str(unsigned long num, char *str);

/* -------- Implementation: ---------------------------------------------- */

static char    work_str[128];

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

#define  BITS_IN_LONG 32

void    long_to_bin_str(unsigned long num, char *str)

{
    int a;
    unsigned long   div;
    char  *ptr, tmp_str[BITS_IN_LONG +1];

    if (num == 0)                                          /* dummy result */
        {
        strcpy(str, "0");
        return;
        }

    for(a = BITS_IN_LONG; a > 0; a--)
        {
        div = (unsigned long)1 << (a-1);
        if(num / div  != 0)
            {
            tmp_str[BITS_IN_LONG - a] = '1';
            num  -=  div;
            }
        else
            tmp_str[BITS_IN_LONG - a] = '0';
        }
    tmp_str[BITS_IN_LONG] = '\0';                             /* terminate */

    ptr = tmp_str;
    while(*ptr == '0')                               /* skip leading zeros */
        ptr++;
    strcpy(str, ptr);                                     /* output result */
}

/* EOF */
