#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf netmhciipan-1.0b
tar xzvvf ${BASE}/source/data/netmhciipan-1.0b/netMHCIIpan-1.0b.Linux.tar.Z
mv netMHCIIpan-1.0 netmhciipan-1.0b
cat ${BASE}/source/patch/netmhciipan-1.0b.patch | patch -p0
cd netmhciipan-1.0b
ln -s Linux_i686 Linux_x86_64
