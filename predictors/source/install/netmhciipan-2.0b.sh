#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf netmhciipan-2.0b
tar xzvvf ${BASE}/source/data/netmhciipan-2.0b/netMHCIIpan-2.0b.Linux.tar.Z
mv netMHCIIpan-2.0 netmhciipan-2.0b
cat ${BASE}/source/patch/netmhciipan-2.0b.patch | patch -p0
cd netmhciipan-2.0b
tar xzvvf ${BASE}/source/data/netmhciipan-2.0b/data.tar.gz
