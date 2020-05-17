#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf netmhc-3.0c
tar xzvvf ${BASE}/source/data/netmhc-3.0c/netMHC-3.0c.Linux.tar.Z
mv netMHC-3.0 netmhc-3.0c
cat ${BASE}/source/patch/netmhc-3.0c.patch | patch -p0
cd netmhc-3.0c
ln -s Linux_i386 bin/Linux_x86_64
