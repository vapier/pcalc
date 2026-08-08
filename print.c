
/* =====[ print.c ]=========================================================

   Description:  Printer routines for pcalc.

   Revisions:

      REV     DATE     BY           DESCRIPTION
      ----  --------  ----------    --------------------------------------
      0.00  mm/dd/95  Peter Glen    Initial version.
      1.00  22/9/98   Peter Glen    Unix port

   ======================================================================= */

/* -------- System includes:  -------------------------------------------- */

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* -------- Includes:  --------------------------------------------------- */

#include "convert.h"
#include "hocdecl.h"
#include "symbol.h"

/* -------- Implementation: ---------------------------------------------- */

static char work_str[128];

extern bool fOctal;
extern int fPrecisionFpFrac;

void    print_num(long double var)

{
    Symbol *msx  = lookup_sym("DEC");
    unsigned long long ullvar = var < 0 ? (long long)var : (unsigned long long)var;

    // compatibility variable:

    if(!msx)
      msx  = lookup_sym("DECIMAL");
    
    if(msx && msx->u.val == 1)
      {
	printf("%Lg", var);
      }
    else if(msx && msx->u.val == 2)
      {
	printf("%llx" , ullvar);
      }
    else if(msx && msx->u.val == 3)
      {
	long_to_bin_str(ullvar, work_str);
	printf("%s", work_str);
      }
    else if(msx && msx->u.val == 4)
      {
	printf("%llo", ullvar);
      }
    else
      {
	long_to_bin_str(ullvar, work_str);
	printf("\t%-16.*Lg", fPrecisionFpFrac, var);
	if (fOctal)
	  printf("\t0o%-16llo", ullvar);
	printf("\t0x%-16llx", ullvar);
	printf("\t0y%s\n", work_str);
      }
}
