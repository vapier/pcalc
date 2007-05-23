
/* =====[ convert.h ]=========================================================

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

#ifndef convert_defined
#define convert_defined

#ifdef  EXPORT
#define EXTERN
#else
#define EXTERN extern
#endif

/* -------- Defines: ----------------------------------------------------- */


/* -------- Macros: ------------------------------------------------------ */


//typedef unsigned long ulong   ;
//typedef unsigned int  uint    ;

/* -------- Protos ------------------------------------------------------- */

unsigned long   hextol(char *str);
unsigned long   bintol(char *str);
unsigned long   otol(char *str);
unsigned int    hextoi(char *str, int lim);
unsigned int    dectoi(char *str, int lim);
unsigned int    hexlen(char *str);
unsigned int    declen(char *str);
void    long_to_bin_str(unsigned long num, char *str);

/* -------- Declarations: ------------------------------------------------ */


/* -------- Definitions: ------------------------------------------------- */

#undef  EXTERN
#undef  EXPORT

#endif

/* EOF */
