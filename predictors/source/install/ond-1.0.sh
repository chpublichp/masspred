#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf ond-1.0
mkdir -p app/lib
rm -f app/lib64
ln -s lib app/lib64
tar xzvvf ${BASE}/source/data/ond-1.0/OnD.tar.gz
mv OnD ond-1.0
cat ${BASE}/source/patch/ond-1.0.patch | patch -p0
chmod 755 ond-1.0/OnD-CRF.sh
cd ond-1.0/CRF
./configure --prefix=${BASE}/app
make clean
make
make install
cd ../sspro4
./configure.pl
