
/* =====[ xxx.c ]=========================================================

   Description:

   Compiled:        MS-VC.

   Compiler opt:    See makefile.

   Revisions:

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
#include <ctype.h>

/* -------- Includes:  --------------------------------------------------- */

#include "convert.h"

/* -------- Defines: ----------------------------------------------------- */


/* -------- Macros: ------------------------------------------------------ */


/* -------- Forward references for procedures: --------------------------- */


/* -------- Declarations: ------------------------------------------------ */


/* -------- Definitions: ------------------------------------------------- */


/* -------- Data: -------------------------------------------------------- */


/* -------- Strings: ----------------------------------------------------- */


/* -------- Implementation: ---------------------------------------------- */

/*
 * Convert hex string to long.
 *
 */

ulong   hextol(char *str)

{
    ulong sum = 0L;
    char chh, val;

    while (isxdigit(*str))
        {
        chh = *str;
        sum *= 0x10;

        if (isdigit(chh))
            val = chh - '0';
        else
            {
            chh = tolower(chh);
            val = chh - 'a' + 10;
            }
        sum += val;
        str++;
        }
    return(sum);
}

/*
 * Convert hex string to long.
 *
 */

ulong   bintol(char *str)

{
    ulong sum = 0L;
    char    chh;

    while ((chh = *str) == '1' || chh == '0')
        {
        sum *= 2;                                   /* make the one higher */

        if(chh == '1')
            sum++;

        str++;
        }
    return(sum);
}

/*
 * Convert octal string to long.
 *
 */

ulong   otol(char *str)

{
    ulong   sum = 0L;
    char    chh;

    while ((chh = *str) >= '0' && chh <= '7')
        {
        sum *= 8;                                   /* make the one higher */
        sum += chh - '0';
        str++;
        }
    return(sum);
}

uint    hextoi(char *str, int lim)

{
    unsigned int sum = 0;
    char chh, val;

    while (1)
        {
        chh = *str;

        if(!isxdigit(chh))
           break;

        if(!lim)
           break;

        sum *= 0x10;

        if (isdigit(chh))
            val = chh - '0';
        else
            {
            chh = tolower(chh);
            val = chh - 'a' + 10;
            }
        sum += val;
        str++;  lim--;
        }
    #ifdef PG_DEBUG
    printf("SUM: %x\n", sum);
    #endif
    return(sum);
}


uint    dectoi(char *str, int lim)

{
    unsigned int sum = 0;
    char chh, val;

    while (1)
        {
        chh = *str;

        if(!isdigit(chh))
           break;

        if(!lim)
           break;

        sum *= 10;

        val = chh - '0';

        sum += val;
        str++;  lim--;
        }
    #ifdef PG_DEBUG
    printf("DEC SUM: %x\n", sum);
    #endif
    return(sum);
}


uint    hexlen(char *str)

{
    unsigned int sum = 0;

    while (1)
        {
        char chh = *str;

        if(!isxdigit(chh))
           break;

        str++; sum++;
        }
    #ifdef PG_DEBUG
    printf("LEN: %x\n", sum);
    #endif
    return(sum);
}


uint    declen(char *str)

{
    unsigned int sum = 0;

    while (1)
        {
        char chh = *str;

        if(!isdigit(chh))
           break;

        str++; sum++;
        }
    #ifdef PG_DEBUG
    printf("LEN: %x\n", sum);
    #endif
    return(sum);
}

#if 0


/*
 * Convert an ulong to a string representation in binary
 */

#define  BITS_IN_LONG 32

void    long_to_bin_str(ulong num, char *str)

{
    int a;
    ulong   div;
    char  *ptr, tmp_str[BITS_IN_LONG +1];

    if (num == 0)                                          /* dummy result */
        {
        strcpy(str, "0");
        return;
        }

    for(a = BITS_IN_LONG; a > 0; a--)
        {
        div = (ulong)1 << (a-1);
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



/*
 * Convert hex string to long.
 *
 */

ulong   hextol(char *str)

{
    ulong sum = 0L;
    char chh, val;

    while (isxdigit(*str))
        {
        chh = *str;
        sum *= 0x10;

        if (isdigit(chh))
            val = chh - '0';
        else
            {
            chh = tolower(chh);
            val = chh - 'a' + 10;
            }
        sum += val;
        str++;
        }
    return(sum);
}

/*
 * Convert hex string to long.
 *
 */

ulong   bintol(char *str)

{
    ulong sum = 0L;
    char    chh;

    while ((chh = *str) == '1' || chh == '0')
        {
        sum *= 2;                                   /* make the one higher */

        if(chh == '1')
            sum++;

        str++;
        }
    return(sum);
}

/*
 * Convert octal string to long.
 *
 */

ulong   otol(char *str)

{
    ulong   sum = 0L;
    char    chh;

    while ((chh = *str) >= '0' && chh <= '7')
        {
        sum *= 8;                                   /* make the one higher */
        sum += chh - '0';
        str++;
        }
    return(sum);
}

#endif

/* EOF */
