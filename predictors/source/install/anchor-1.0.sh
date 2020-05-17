#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf anchor-1.0
tar xzvvf ${BASE}/source/data/anchor-1.0/ANCHOR.tar.gz
mv ANCHOR anchor-1.0
cd anchor-1.0
make
