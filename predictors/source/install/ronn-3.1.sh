#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf ronn-3.1
tar xzvvf ${BASE}/source/data/ronn-3.1/RONNv3_1.tar.gz
mv RONNv3_1 ronn-3.1
cat ${BASE}/source/patch/ronn-3.1.patch | patch -p0
cd ronn-3.1
make
