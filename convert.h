#ifndef convert_defined
#define convert_defined

/* -------- Macros: ------------------------------------------------------ */


/* -------- Protos ------------------------------------------------------- */

unsigned long long hextoll(char *str);
unsigned long   hextol(char *str);
unsigned long   bintol(char *str);
unsigned long   otol(char *str);
unsigned int    hextoi(char *str, int lim);
unsigned int    dectoi(char *str, int lim);
unsigned int    hexlen(char *str);
unsigned int    declen(char *str);
void    long_to_bin_str(unsigned long long num, char *str);

#endif
