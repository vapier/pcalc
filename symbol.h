#ifndef symbol_defined
#define symbol_defined

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
Symbol *lookup_sym(const char *s);
Symbol *install_sym(const char *s, int t, double d);

#endif
