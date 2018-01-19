#ifndef store_defined
#define store_defined

/* -------- Macros: ------------------------------------------------------ */


/* -------- Protos ------------------------------------------------------- */


int     store(char *file, char *name, double var);
int     restore(char *file, char *name, double *var);

#endif
