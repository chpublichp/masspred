#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/disembl-1.4
cd ${BASE}/source/data/disembl-1.4
wget -c http://dis.embl.de/DisEMBL-1.4.tgz
wget -c http://www.mpipks-dresden.mpg.de/~tisean/TISEAN_3.0.1.tar.gz
wget -c http://biopython.org/DIST/biopython-1.60.tar.gz
wget -c http://downloads.sourceforge.net/project/numpy/NumPy/1.7.1/numpy-1.7.1.tar.gz
