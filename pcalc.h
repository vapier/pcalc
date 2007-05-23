typedef union {                                           /* stack object type    */
    int     intval ;                               /* actual value         */
    long    lngval ;                               /* actual value         */
    double  val ;                                  /* actual value         */
    Symbol  *sym ;                                 /* symbol table ptr     */
} YYSTYPE;
#define	NUMBER	258
#define	VAR	259
#define	BUILTIN	260
#define	IBUILTIN	261
#define	UNDEF	262
#define	STR	263
#define	TO	264
#define	FROM	265
#define	STORE	266
#define	RESTORE	267
#define	STRVAR	268
#define	UNARYMINUS	269


extern YYSTYPE yylval;
