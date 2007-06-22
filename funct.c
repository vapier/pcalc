
/* =====[ xxx.c ]=========================================================

   Description:

   Compiled:        MS-C.

   Compiler opt:    ??

   Revisions:

      REV     DATE     BY           DESCRIPTION
      ----  --------  ----------    --------------------------------------
      0.00  xx.xx.94  Peter Glen    Initial version.

   ======================================================================= */

/* -------- System includes:  -------------------------------------------- */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
//include <dos.h>
#include <time.h>
#include <string.h>

/* -------- Includes:  --------------------------------------------------- */

#include "hocdecl.h"
#include "symbol.h"
#include "str.h"

/* -------- Defines: ----------------------------------------------------- */


/* -------- Macros: ------------------------------------------------------ */


/* -------- Forward references for procedures: --------------------------- */


/* -------- Declarations: ------------------------------------------------ */


/* -------- Definitions: ------------------------------------------------- */


/* -------- Data: -------------------------------------------------------- */


/* -------- Strings: ----------------------------------------------------- */

static char    work_str[2000];

/* -------- Implementation: ---------------------------------------------- */

int     print(double ee)

{
    printf("val\t%-8.8g\t0x%-8lx\n", ee, (long)ee);
    return(0);
}

int     echo(char *str)

{
    if(str)
        {
        str_esc(str, work_str, sizeof(work_str));
        printf("%s\n", work_str);

        //printf("%s\n", str);
        }
    return(0);
}

int     echo_nl(char *str)

{
    if(str)
        {
        str_esc(str, work_str, sizeof(work_str));
        printf("%s", work_str);

        //printf("%s\n", str);
        }
    return(0);
}


/* the date function */

int     ddate(char *str)

{
    struct tm *loc_time;
    time_t lt;
    char string[128];

    lt = time(NULL);

    str_esc(str, work_str, sizeof(work_str));
    loc_time = localtime(&lt);
    strftime(string, sizeof(string), work_str, loc_time);

    printf("%s", string);

    return(0);
}
