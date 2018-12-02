# pcalc syntax & specification

 Number specification:

    0x1234              hexadecimal
    0X1234              hexadecimal
     01234              octal
    0o1234              octal
    0c1234              octal
    0b0101              binary
    0y0101              binary
    123456              decimal

    Numbers may have underscores in them as seprators for visibility.
    0xFFFF_0000   0o777_555   0b1111_0000   12_34_56_78
    Decimal numbers may also have commas in them.
    1,100,234

 Built in functions:

    sin             mathematical sinus
    cos             mathematical cos
    atan            mathematical atan
    log             mathematical log
    log10           mathematical log10
    exp             mathematical exp
    sqrt            mathematical sqrt
    int             mathematical int
    abs             mathematical abs
    f2c             converting temperature-> fahrenheit to celsius
    c2f             converting temperature-> celsius to fahrenheit
    in2mm           converting length-> inches to millimeter
    mm2in           converting length-> millimeter to inches
    po2kg           converting mass-> pounds to kilogram
    kg2po           converting mass-> kilogram to pounds

 Built in controls:

    echo            echo to the screen
   _echo            echo to the screen, no new line
    date            echo to the screen, expanding date variables 
   store            store variable to file
   restore          restore viable from file

 Built in variables:

    DEBUG           for debug 0=off 1=on
    DEC             controlling number display 0=default 1=dec 2=hex 3=bin 4=oct

Operator priorities:

     LOW    '='         assignment
            or          binary or
            and         binary and
            '>' '<'     binary left/right shift
            '+' '-'     addition/subtraction
            '*' '/' '%' multiply/divide/modulus
            '-'         unary minus
     HIGH   '^'         exponentiation

Syntax:

	pcalc  var
	pcalc  expr
	pcalc  number
	pcalc  var = number
	pcalc  builtin expr
	pcalc  builtin ( expr )
	pcalc  date "string"
	pcalc  echo "string"
	pcalc  _echo "string"
	pcalc  store    var
	pcalc  store    var to  "file"
	pcalc  restore  var
	pcalc  restore  var from "file"

The result is output in 3 parts: 

    DEC number	     HEX number	     BIN number

      20              0x14            0y10100

If the number is out of range from the HEX and BIN numbers, the
truncated numbers are displayed.
