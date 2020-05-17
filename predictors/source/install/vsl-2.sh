#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf vsl-2
tar xzvvf ${BASE}/source/data/vsl-2/VSL2.tar.gz
mv VSL2 vsl-2
