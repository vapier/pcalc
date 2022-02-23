
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

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

/* -------- Includes:  --------------------------------------------------- */

#include "convert.h"
#include "debug.h"

/* -------- Implementation: ---------------------------------------------- */

/*
 * Convert hex string to long.
 *
 */

unsigned long long hextoll(const char *str)
{
	unsigned long long sum = 0;

	while (*str) {
		switch (*str) {
		case '0'...'9':
			sum <<= 4;
			sum += (*str - '0');
			break;
		case 'a'...'f':
			sum <<= 4;
			sum += 0xa + (*str - 'a');
			break;
		case 'A'...'F':
			sum <<= 4;
			sum += 0xa + (*str - 'A');
			break;
		case '_':
			break;
		default:
			return sum;
		}

		++str;
	}

	return sum;
}

/*
 * Convert hex string to long.
 *
 */

unsigned long bintol(const char *str)
{
	unsigned long sum = 0L;

	while (*str) {
		switch (*str) {
		case '1':
			sum <<= 1;
			++sum;
			break;
		case '0':
			sum <<= 1;
			break;
		case '_':
			break;
		default:
			return sum;
		}

		++str;
	}

	return sum;
}

/*
 * Convert octal string to long.
 *
 */

unsigned long otol(const char *str)
{
	unsigned long sum = 0L;

	while (*str) {
		switch (*str) {
		case '0'...'7':
			sum <<= 3;
			sum += (*str - '0');
			break;
		case '_':
			break;
		default:
			return sum;
		}

		++str;
	}

	return sum;
}

/*
 * Convert decimal string to long.
 *
 */

unsigned long long dtoll(const char *str)
{
	unsigned long long sum = 0;

	while (*str) {
		switch (*str) {
		case '0'...'9':
			sum *= 10;
			sum += (*str - '0');
			break;
		case ',':
		case '_':
			break;
		default:
			return sum;
		}

		++str;
	}

	return sum;
}

unsigned int hextoi(const char *str, int lim)
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
    debug("SUM: %x\n", sum);
    return(sum);
}

unsigned int dectoi(const char *str, int lim)
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
    debug("DEC SUM: %x\n", sum);
    return(sum);
}

unsigned int hexlen(const char *str)
{
    unsigned int sum = 0;

    while (1)
        {
        char chh = *str;

        if(!isxdigit(chh))
           break;

        str++; sum++;
        }
    debug("LEN: %x\n", sum);
    return(sum);
}

unsigned int declen(const char *str)
{
    unsigned int sum = 0;

    while (1)
        {
        char chh = *str;

        if(!isdigit(chh))
           break;

        str++; sum++;
        }
    debug("LEN: %x\n", sum);
    return(sum);
}


/*
 * Convert an unsigned long to a string representation in binary
 *
 */

extern bool fNibble;

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
