/*--------------------------------------------------------------------------
**      file:       MATH.C
**      project:    hoc3, "Higher Order Calculator"
*/

#include <math.h>
#include <stdio.h>
#include <errno.h>
#include "hocdecl.h"

double errcheck() ;


double Log( double x)

{
   return errcheck( log(x), "log") ;
}

double Log10( double x)
{
   return errcheck( log10(x), "log10") ;
}

double Exp( double x)
{
   return errcheck( exp(x), "exp") ;
}

double Pow( double x, double y)
{
   return errcheck( pow(x, y), "exponentiation") ;
}

double integer( double x)
{
   return (double)(long) x ;
}

double Sqrt( double x)
{
   return errcheck( sqrt(x), "sqrt") ;
}

double errcheck( double d, char *s)
{
    if (errno == EDOM) {
        errno = 0 ;
        execerror( s, "argument out of domain") ;
    }
    else if (errno == ERANGE) {
        errno = 0 ;
        execerror(s, "result out of range") ;
    }

    return d ;
}

    double ret_val = 0.0;

double f2c(double d)

{
    ret_val = (5 * (d-32)) / 9;
    return ret_val;
}

double c2f(double d)

{
    ret_val = (d * 9)/5 + 32;
    return ret_val;
}

double in2mm(double d)

{
    ret_val = (d * 25.4);
    return ret_val;
}

double mm2in(double d)

{
    ret_val = (d / 25.4);
    return ret_val;
}

double po2kg(double d)

{
    ret_val = ((d * 453.592) / 1000);
    return ret_val;
}

double kg2po(double d)

{
    ret_val = ((d * 1000) / 453.592);
    return ret_val;
}
