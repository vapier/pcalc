
/* =====[ STR.C ]=========================================================

   Description:     Convert stings.

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
#include "hocdecl.h"
#include "str.h"

/* -------- Defines: ----------------------------------------------------- */

//define PG_DEBUG

#define MIN(a,b) ((a>b) ? a : b)

/* -------- Macros: ------------------------------------------------------ */


/* -------- Forward references for procedures: --------------------------- */


/* -------- Declarations: ------------------------------------------------ */


/* -------- Definitions: ------------------------------------------------- */


/* -------- Data: -------------------------------------------------------- */


/* -------- Strings: ----------------------------------------------------- */


/* -------- Implementation: ---------------------------------------------- */

/*
 * int     str_esc(char *str, char *out, int lim)
 *
 * Expand escape sequence like 'C'.
 *
 * Spec:     esc char '\\' (backslash)
 *
 *           special characters:     a   :   alert
 *                                   b   :   backspace
 *                                   f   :   f
 *                                   r   :   return
 *                                   n   :   newline
 *                                   t   :   tab
 *                                   v   :   vertical tab
 *                                   \\  :   backslash
 *                                   xnn :   hex numbered character
 *                                   nnn :   dec numbered character
 *
 *  The dec number overflow is interpretes as 2 dec numbered character +
 *  the following character interpreted normally.
 *
 */

unsigned int    str_esc(char *str, char *out, int lim)

{
    char    *str2 = str;
    int     ret_val = 0;

    *out = '\0';
    if(!str)
      return  0;
        
    while(1)
        {
        *out = '\0';

        if(!*str2)
            break;

        if(!lim)
            {
            ret_val = TRUE;
            break;
            }
        else if(str2-str+1 >= lim)
            {
            fprintf(stderr, "String too large for buffer of %i chars; truncated\n", lim-1);
            ret_val = FALSE;
            *str2 = '\0';
            break;
            }
        switch(*str2)
            {
            int tmp;

            case '\\':
                if(isdigit(*(str2+1)))
                    {
                    int len = 3;

                    tmp  = dectoi(str2+1, len);         // convert number
                    if(tmp > 255)                       // decimal overflow ?
                       len--;

                    tmp  = dectoi(str2+1, len);         // re-convert number
                    len  = MIN(declen(str2+1), len);
                    *out = (char) tmp;
                    str2 += len;
                    }
                else
                    {
                    switch(*(str2+1))
                        {
                        case 'x':
                            tmp = hextoi(str2+2, 2);        // convert number
                            *out = (char) tmp;
                            str2 += MIN(hexlen(str2+2),2);
                            str2++;
                            break;

                        case 'a':
                            *out = 7;
                            str2++;
                            break;

                        case 'b':
                            *out = 8;
                            str2++;
                            break;

                        case 'f':
                            *out = 12;
                            str2++;
                            break;

                        case 'n':
                            *out = 10;
                            str2++;
                            break;

                        case 'r':
                            *out = 13;
                            str2++;
                            break;

                        case 't':
                            *out = 9;
                            str2++;
                            break;

                        case 'v':
                            *out = 11;
                            str2++;
                            break;

                        case '\\':
                            *out = '\\';
                            str2++;
                            break;

                        case '\'':
                            *out = '\'';
                            str2++;
                            break;

                        case '\"':
                            *out = '\"';
                            str2++;
                            break;

                        default:
                            *out = *str2;
                            str2++;
                            break;
                        }
                    }
                break;

            default:
                *out = *str2;
                break;
            }
        str2++;  out++;
        }
    return ret_val;
}

/* EOF */
