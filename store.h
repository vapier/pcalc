#ifndef store_defined
#define store_defined

/* -------- Macros: ------------------------------------------------------ */


/* -------- Protos ------------------------------------------------------- */


int store(const char *file, const char *name, double var);
int restore(const char *file, const char *name, double *var);

#endif
