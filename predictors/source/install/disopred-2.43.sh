#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf disopred-2.43
tar xzvvf ${BASE}/source/data/disopred-2.43/disopred2.43.tar.gz
mv disopred disopred-2.43
cat ${BASE}/source/patch/disopred-2.43.patch | patch -p0
cd disopred-2.43
tar xzvvf ${BASE}/source/data/disopred-2.43/blast-2.2.26-ia32-linux.tar.gz
cd src
make clean
make
make install
