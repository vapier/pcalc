#!/usr/bin/env python3

"""Quickly generate constants."""

from mpmath import mp


def p(s, n):
    s = f'"{s}",'
    print(f"        {{{s:8} {n}L}},")

mp.dps = 100
p("PI", mp.pi)
p("E", mp.e)
p("GAMMA", mp.euler(0))
p("DEG", 180 / mp.pi)
p("PHI", mp.phi)
