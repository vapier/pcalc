#!/bin/bash -e
# The main script for building/testing while under travis ci.
# https://travis-ci.org/libgd/libgd

. "${0%/*}"/lib.sh

main() {
	m distcheck
}
main "$@"
