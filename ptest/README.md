# pcalc testsuite

This uses [GNU Autotest] that is bundled with [GNU Autoconf].

The Makefile takes care of generating all the required files and then running
the testsuite.

[GNU Autoconf]: https://www.gnu.org/software/autoconf/
[GNU Autotest]: https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/html_node/Using-Autotest.html

## Running Tests

Running `make` in this directory (or `make check` in the top-level directory)
will do everything for you -- generate files & then run them.

Once you have the `testsuite` file generated, you can list all the tests with:

```
$ ./testsuite --list
```

Then run specific tests by their registered number:

```
$ ./testsuite 1
```

Then review the test output in `testsuite.dir/01/testsuite.log`.

## File Structure

* `local.at`: Helper macros used by individual tests.
* `Makefile`: Logic to generate & execute the testsuite.
* `pcalc.<name>`: pcalc script (run with `pcalc @pcalc.<name>`).
* `pcalc.<name>.at`: Individual tests.
* `testsuite.at`: Overall testsuite entry point.

Generally `<name>` is a 3 digit number with no overall meaning or relevance
other than to be unique.

Individual tests need to be manually registered in `testsuite.at`.
They are not dynamically discovered.
