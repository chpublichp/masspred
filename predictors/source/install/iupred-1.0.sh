#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf iupred-1.0
tar xzvvf ${BASE}/source/data/iupred-1.0/iupred.tar.gz
mv iupred iupred-1.0
cd iupred-1.0
make iupred
