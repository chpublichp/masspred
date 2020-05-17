#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/disembl-1.4
./DisEMBL.py 8 8 4 1.2 1.4 1.2 ${BASE}/source/test/example.faa scores
