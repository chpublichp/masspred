#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/vsl-2
cd ${BASE}/source/data/vsl-2
wget -c http://www.dabi.temple.edu/disprot/download/VSL2.tar.gz
