#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf nr
mkdir nr
cd nr
tar xzvvf ${BASE}/source/data/nr/nr.00.tar.gz
tar xzvvf ${BASE}/source/data/nr/nr.01.tar.gz
tar xzvvf ${BASE}/source/data/nr/nr.02.tar.gz
tar xzvvf ${BASE}/source/data/nr/nr.03.tar.gz
tar xzvvf ${BASE}/source/data/nr/nr.04.tar.gz
tar xzvvf ${BASE}/source/data/nr/nr.05.tar.gz
tar xzvvf ${BASE}/source/data/nr/nr.06.tar.gz
tar xzvvf ${BASE}/source/data/nr/nr.07.tar.gz
tar xzvvf ${BASE}/source/data/nr/nr.08.tar.gz
tar xzvvf ${BASE}/source/data/nr/nr.09.tar.gz
tar xzvvf ${BASE}/source/data/nr/nr.10.tar.gz
