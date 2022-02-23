/*--------------------------------------------------------------------------
**      file:       MATH.C
**      project:    hoc3, "Higher Order Calculator"
*/

#include <math.h>
#include <stdio.h>
#include <errno.h>
#include "hocdecl.h"

static long double errcheck(long double d, const char *s)
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

long double Log(long double x)

{
   return errcheck(logl(x), "log");
}

long double Log10(long double x)
{
   return errcheck(log10l(x), "log10");
}

long double Exp(long double x)
{
   return errcheck(expl(x), "exp");
}

long double Pow(long double x, long double y)
{
   return errcheck(powl(x, y), "exponentiation");
}

long double integer(long double x)
{
   return (long double)(long long)x;
}

long double Sqrt(long double x)
{
   return errcheck(sqrtl(x), "sqrt");
}

/* Fahrenheit to Celsius */
long double f2c(long double d)
{
	return (5 * (d - 32)) / 9;
}

/* Celsius to Fahrenheit */
long double c2f(long double d)
{
	return (d * 9) / 5 + 32;
}

/* Inches to millimeter */
long double in2mm(long double d)
{
	return d * 25.4;
}

/* Millimeter to inches */
long double mm2in(long double d)
{
	return d / 25.4;
}

/* Pounds to kilograms */
long double po2kg(long double d)
{
	return (d * 453.592) / 1000;
}

/* Kilograms to pounds */
long double kg2po(long double d)
{
	return (d * 1000) / 453.592;
}
