#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/netmhc-3.4a
./netMHC -a HLA-A02:01 -l 8 test/test.fsa
