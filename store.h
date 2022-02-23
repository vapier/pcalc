#ifndef store_defined
#define store_defined

/* -------- Macros: ------------------------------------------------------ */


/* -------- Protos ------------------------------------------------------- */


int store(const char *file, const char *name, long double var);
int restore(const char *file, const char *name, long double *var);

#endif
