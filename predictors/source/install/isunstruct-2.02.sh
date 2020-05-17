#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf isunstruct-2.02
mkdir isunstruct-2.02
cd isunstruct-2.02
tar xzvvf ${BASE}/source/data/isunstruct-2.02/IsUnstruct_2.02.tar.gz
rm -f IsUnstruct *.o
make
