
/*
** HOCDECL.H   definitions for the hoc3.y calculator
**              in K&P p246 ch8.
*/

/*
**      functions in HOC3.C
*/

extern int yylex( void) ;
extern void execerror(const char *, const char *);
extern void fpecatch( int ) ;
extern void yyerror(const char *);
extern void warning(const char *, const char *);

/*
**      function in INIT.C
*/

extern void init( void) ;

/*
**      functions in MATH.C
*/

extern  long double Log(long double x);
extern  long double Log10(long double x);
extern  long double Exp(long double x);
extern  long double Pow(long double x, long double y);
extern  long double integer(long double x);
extern  long double Sqrt(long double x);
extern  long double f2c(long double d);
extern  long double c2f(long double d);
extern  long double in2mm(long double d);
extern  long double mm2in(long double d);
extern  long double po2kg(long double d);
extern  long double kg2po(long double d);

/*
**      functions in FUNCT.C
*/

extern  int print(long double);
extern  int echo(const char *str);
extern  int echo_nl(const char *str);
extern  int ddate(const char *str);
