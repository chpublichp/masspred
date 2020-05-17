#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/netmhc-3.0c
./netMHC-3.0 -a A0201 -l 8 -s test/testprot.fsa
