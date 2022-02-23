#!/usr/bin/env python

"""Quickly generate constants."""

from mpmath import mp


mp.dps = 100
print("PI", mp.pi)
print("E", mp.e)
print("GAMMA", mp.euler(0))
print("DEG", 180 / mp.pi)
print("PHI", mp.phi)
