# pcalc: The Programmer's calculator

[![Build Status](https://travis-ci.org/vapier/pcalc.svg?branch=master)](https://travis-ci.org/vapier/pcalc)

There was always a loophole when it came to a need to covert between
hexadecimal / decimal / octal / binary.

Especially if it involved an operation like 0x1234 + 0x20.
It took a lot of hard work, and mostly a good pocket calculator.

## Features

* Full math parser, parentheses, add, sub, mult, div, exponential
* Automatic conversion between HEX DEC OCT BIN numbers
* Mixing different bases in one expression
* Definable variables
* Math constants (E PI ...)
* Built in math functions (sin/cos/sqrt ...)

## Examples

Here are bunch of common examples.

See the [SYNTAX.md] file for the full syntax.
You can also run `pcalc` for a local reference.

```sh
$ pcalc 0x300
        768                     0x300                   0y1100000000

# Note: Shell expansion on the '*' char requires the single quotes.
$ pcalc '0x300 + 3 * 3'
        777                     0x309                   0y1100001001

$ pcalc sqrt 2
        1.414213562373095       0x1                     0y1

# Note: The single quotes are to keep the shell happy with the () characters.
$ pcalc 'sqrt(2)'
        1.414213562373095       0x1                     0y1

$ pcalc 0x12 or 23
        23                      0x17                    0y10111

# To execute a script, use the `@` prefix on the filename.
$ pcalc @pcalc.001
```

## Building & Installing

To compile the project, simply use `make`:
```sh
$ make
```

Note: Some platforms might not provide `flex` or `-lfl`.
You will need to adjust the Makefile accordingly.

To install it, you can do:
```sh
$ sudo make install
```

## Testing

To run the unittests, use:
```sh
$ make check
```

Note: Depending on the precision of floating point math in your system, some
unittests might fail.  It's OK to ignore those specific failures.

## Feedback

Please use the GH issue tracker for any updates/ports/suggestions.
Feedback always welcome!

https://github.com/vapier/pcalc/issues

## License

This project is licensed under GPLv2 (or later).
The full text can be found in the [COPYING] file.


[COPYING]: ./COPYING
[SYNTAX.md]: ./SYNTAX.md
