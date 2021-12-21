
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

extern  double Log(double x);
extern  double Log10(double x);
extern  double Exp(double x);
extern  double Pow(double x,double y);
extern  double integer(double x);
extern  double Sqrt(double x);
extern  double f2c(double d);
extern  double c2f(double d);
extern  double in2mm(double d);
extern  double mm2in(double d);
extern  double po2kg(double d);
extern  double kg2po(double d);
extern  double nthroot(double d , double n);
/*
**      functions in FUNCT.C
*/

extern  int print(double);
extern  int echo(const char *str);
extern  int echo_nl(const char *str);
extern  int ddate(const char *str);
