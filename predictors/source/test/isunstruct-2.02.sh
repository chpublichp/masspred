#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/isunstruct-2.02
./IsUnstruct -long-disp 1 -file_save 0 ${BASE}/source/test/example.faa
