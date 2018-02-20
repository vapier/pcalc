/*--------------------------------------------------------------------------
**      file:       MATH.C
**      project:    hoc3, "Higher Order Calculator"
*/

#include <math.h>
#include <stdio.h>
#include <errno.h>
#include "hocdecl.h"

static double errcheck(double d, const char *s)
{
	if (errno == EDOM) {
		errno = 0;
		execerror(s, "argument out of domain");
	} else if (errno == ERANGE) {
		errno = 0;
		execerror(s, "result out of range");
	}

	return d;
}

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

/* Fahrenheit to Celsius */
double f2c(double d)
{
	return (5 * (d - 32)) / 9;
}

/* Celsius to Fahrenheit */
double c2f(double d)
{
	return (d * 9) / 5 + 32;
}

/* Inches to millimeter */
double in2mm(double d)
{
	return d * 25.4;
}

/* Millimeter to inches */
double mm2in(double d)
{
	return d / 25.4;
}

/* Pounds to kilograms */
double po2kg(double d)
{
	return (d * 453.592) / 1000;
}

/* Kilograms to pounds */
double kg2po(double d)
{
	return (d * 1000) / 453.592;
}
