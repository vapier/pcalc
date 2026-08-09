#!/usr/bin/awk
# Check a stdout file against expected output, but with regular expressions.
# The expected output supports comment lines via "dnl" prefixes.

BEGIN {
  if (ARGC != 3) {
    print("USAGE:", ARGV[0], "-f check-output.awk <stdout file> <expected file>")
    exit(1)
  }

  fp_out = ARGV[1]
  fp_exp = ARGV[2]
  ret = 0
}

{
  lineno = 0
  while (1) {
    lineno += 1
    ret_out = getline line_out < fp_out
    # Read the next expected output, but skip "dnl" comment lines.
    while (1) {
      ret_exp = getline line_exp < fp_exp
      if (match(line_exp, "^dnl ") != 0) {
        continue
      }
      break
    }
    if (ret_out == 0 && ret_exp == 0) {
      break
    } else if (ret_out != 1 || ret_exp != 1) {
      print("Line count mismatch between stdout & expected output")
      ret = 1
      break
    }

    # Match the output line with the regex.
    if (match(line_out, "^" line_exp "$") == 0) {
      print("ERROR: line", lineno, "does not match!")
      print("  Output:", line_out)
      print("  Regex :", line_exp)
      ret = 1
    }
  }
}

END {
  exit(ret)
}
