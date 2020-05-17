#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf predisorder-1.1
tar xzvvf ${BASE}/source/data/predisorder-1.1/predisorder1.1.tar.gz
mv predisorder1.1 predisorder-1.1
cd predisorder-1.1
chmod 755 configure.pl
chmod 755 script/predict_diso.pl
chmod 755 server/predict_seq
tar xzvvf ${BASE}/source/data/predisorder-1.1/sspro4.1.tar.gz
cd sspro4.1
rm -rf blast-2.2.17
tar xzvvf ${BASE}/source/data/predisorder-1.1/blast-2.2.17-ia32-linux.tar.gz
cd ../..
cat ${BASE}/source/patch/predisorder-1.1.patch | patch -p0
cd predisorder-1.1
./configure.pl
cd sspro4.1
./configure.pl
