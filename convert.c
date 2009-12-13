
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

unsigned long long hextoll(char *str)
{
	unsigned long long ret;

	sscanf(str, "%llx", &ret);

	return ret;
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


/*
 * Convert an unsigned long to a string representation in binary
 *
 */

extern int fNibble;

void long_to_bin_str(unsigned long long num, char *str)
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
        unsigned long long bit = (unsigned long long)1 << i;
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
