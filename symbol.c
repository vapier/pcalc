/*
 *  pcalc
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hocdecl.h"
#include "symbol.h"
#include "pcalc.h"

static  Symbol *symlist = (Symbol *) 0 ;

typedef struct
        {
        char *name ;
        double cval;
        }
        CONSTS;

CONSTS consts[] =

{
        {"PI",    3.14159265358979323846},
        {"E",     2.71828182845904523536},
        {"GAMMA", 0.57721566490153286060},
        {"DEG",   57.29577951308322087680},
        {"PHI",   1.61803389974989484820},
        {NULL,    0.0}
} ;

typedef struct
        {
        char     *name ;
        double   (*func)() ;
        }
        BUILTINS;

BUILTINS    builtins[] =

{
        {"sin",      sin},
        {"cos",      cos},
        {"atan",     atan},
        {"log",      Log},
        {"log10",    Log10},
        {"exp",      Exp},
        {"sqrt",     Sqrt},
        {"int",      integer},
        {"abs",      fabs},
        {"f2c",      f2c},
        {"c2f",      c2f},
        {"in2mm",    in2mm},
        {"mm2in",    mm2in},
        {"po2kg",    po2kg},
        {"kg2po",    kg2po},


        {"SIN",      sin},
        {"COS",      cos},
        {"ATAN",     atan},
        {"LOG",      Log},
        {"LOG10",    Log10},
        {"EXP",      Exp},
        {"SQRT",     Sqrt},
        {"INT",      integer},
        {"ABS",      fabs},
        {"F2C",      f2c},
        {"C2F",      c2f},
        {"IN2MM",    in2mm},
        {"MM2IN",    mm2in},
        {"PO2KG",    po2kg},
        {"KG2PO",    kg2po},

        {NULL,       (void *) 0}
} ;

typedef struct
        {
        char     *name ;
        int      (*ifunc)() ;
        }
        IBUILTINS;

IBUILTINS    ibuiltins[] =

{

        {"date",     ddate},
        {"print",    print},
        {"echo",     echo},
        {"_echo",    echo_nl},

        {"DATE",     ddate},
        {"PRINT",    print},
        {"ECHO",     echo},
        {"_ECHO",    echo_nl},

        {NULL,       (void *) 0}
} ;



void    init_sym(void)

{
    int i ;
    Symbol *s ;

    for (i=0 ; consts[i].name ; i++)
      (void) install_sym( consts[i].name, VAR, consts[i].cval) ;

    for (i=0 ; builtins[i].name ; i++)
        {
        s = install_sym( builtins[i].name, BUILTIN, 0.0) ;
        s->u.ptr = builtins[i].func ;
        }

    for (i=0 ; ibuiltins[i].name ; i++)
        {
        s = install_sym( ibuiltins[i].name, IBUILTIN, 0) ;
        s->u.iptr = ibuiltins[i].ifunc ;
        }
}

void    dump_sym(void)

{
    Symbol *sp ;

    for (sp = symlist ; sp != (Symbol *) 0 ; sp = sp->next)
        {
        printf("Symbol: %s\n", sp->name);
        }
}

/*--------------------------------------------------------------------------
**  LOOKUP  -   find symbol in table
*/

/*
 * find s in symbol table
 */

Symbol *lookup_sym(const char *s)

{
    Symbol *sp ;

    for (sp = symlist ; sp != (Symbol *) 0 ; sp = sp->next)
      if (strcmp( sp->name, s) == 0)
         return sp ;                                             /* found  */

   return (Symbol *) 0 ;                               /* symbol not found */
}

/*--------------------------------------------------------------------------
**  INSTALL -   install symbol in table
*/

Symbol *install_sym(const char *s, int t, double d)

{
    Symbol *sp ;

    sp = (Symbol *) malloc(sizeof(Symbol));
    if (!sp)
        execerror("out of memory", NULL);

    sp->name = strdup(s);
    if (!sp->name)
        execerror("out of memory", NULL);

    sp->type = t ;
    sp->u.val = d ;
    sp->next = symlist ;                    /* add symbol to front of list */
    symlist = sp ;

    return sp ;
}
