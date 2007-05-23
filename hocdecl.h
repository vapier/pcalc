
/*
** HOCDECL.H   definitions for the hoc3.y calculator
**              in K&P p246 ch8.
*/

#define TRUE 1
#define FALSE 0

/*
**      functions in HOC3.C
*/

extern int yylex( void) ;
extern void execerror( char *, char *) ;
extern void fpecatch( int ) ;
extern void yyerror( char *) ;
extern void warning( char *, char *) ;

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
extern  double errcheck( double, char *) ;
extern  double f2c(double d);
extern  double c2f(double d);
extern  double in2mm(double d);
extern  double mm2in(double d);
extern  double po2kg(double d);
extern  double kg2po(double d);

/*
**      functions in FUNC.C
*/

extern  int     print(double);
extern  int     echo(char *str);
extern  int     echo_nl(char *str);
extern  int     ddate(char *str);
