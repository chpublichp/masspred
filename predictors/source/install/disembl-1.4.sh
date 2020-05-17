#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf disembl-1.4
mkdir -p app/lib
rm -f app/lib64
ln -s lib app/lib64
mkdir -p app/lib/python
rm -f app/lib/python2.6
ln -s python app/lib/python2.6
rm -f app/lib/python2.7
ln -s python app/lib/python2.7
tar xzf ${BASE}/source/data/disembl-1.4/DisEMBL-1.4.tgz
mv DisEMBL-1.4 disembl-1.4
cat ${BASE}/source/patch/disembl-1.4.patch | patch -p0
cd disembl-1.4
tar xzf ${BASE}/source/data/disembl-1.4/TISEAN_3.0.1.tar.gz
cd Tisean_3.0.1
./configure
make clean
make
cp source_c/sav_gol ../
cd ..
make disembl
tar xzvvf ${BASE}/source/data/disembl-1.4/numpy-1.7.1.tar.gz
cd numpy-1.7.1
python setup.py build
python setup.py install --prefix=${BASE}/app
cd ..
tar xzvvf ${BASE}/source/data/disembl-1.4/biopython-1.60.tar.gz
cd biopython-1.60
yes | python setup.py build
yes | python setup.py install --prefix=${BASE}/app
