
/* =====[ symbol.h ]=========================================================

   Description:

   Notes:   To use it there are two metods: as definition   (EXPORT)
                                            as prototyping. (IMPORT)

            If EXPORT is defined, we define and initialize variables,
            otherwise we supply prototypes.

            If we want to initialize, it is done like:

            int this variable
            #ifdef EXPORT
            = FALSE
            #endif
            ;               !!!!  note the semicolon !!!!

            EXPORT is undefined by this process, for the next include file
            it should be stated again.


      REV     DATE     BY           DESCRIPTION
      ----  --------  ----------    --------------------------------------
      0.00  mm/dd/95  Peter Glen    Initial version.

   ======================================================================= */

#ifndef symbol_defined
#define symbol_defined

#ifdef  EXPORT
#define EXTERN
#else
#define EXTERN extern
#endif

/* -------- Defines: ----------------------------------------------------- */


/* -------- Macros: ------------------------------------------------------ */

typedef struct Symbol {    /* symbol table entry */
         char *name ;
         short type ;      /* VAR, BLTIN, UNDEF  */
         union {
               int    len;                /* if str */
               char   *str;               /* if str */
               char   cval;               /* if VAR */
               int    ival;               /* if VAR */
               long   lval;               /* if VAR */
               double val;                /* if VAR */
               double (*ptr)() ;      /* if BUILTIN */
               int    (*iptr)() ;    /* if IBUILTIN */
         } u ;
  struct Symbol *next ;
} Symbol ;

/* -------- Protos ------------------------------------------------------- */

void    init_sym(void);
void    dump_sym(void);
Symbol  *lookup_sym(char *s);
Symbol  *install_sym(char *s, int t, double d);
char    *emalloc(unsigned n);

/* -------- Declarations: ------------------------------------------------ */


/* -------- Definitions: ------------------------------------------------- */

#undef  EXTERN
#undef  EXPORT

#endif

/* EOF */
